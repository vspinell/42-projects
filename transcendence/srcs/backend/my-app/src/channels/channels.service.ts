import { Injectable, Logger } from '@nestjs/common';
import { AdminOnChannel } from '@prisma/client';
import { Blob } from 'buffer';
import { Request, Response } from 'express';
import { BlockList } from 'net';
import { ChatGateway } from 'src/chat/chat.gateway';
import { PrismaService } from 'src/prisma/prisma.service';
import { TwoFactorAuthService } from 'src/two-factor-auth/two-factor-auth.service';
import { User, UserOnChannel, UserWithRelations } from 'src/user/dto/user.dto';
import { checkPasswords, encodePassword } from 'src/utils/bcrypt';
import { Readable } from 'stream';
import { Channel, ChannelMessage, ChannelWithRelations } from './dto/channels.dto';

@Injectable()
export class ChannelsService {
	private readonly logger = new Logger(ChannelsService.name);
	constructor(private prisma: PrismaService, private chatGateway: ChatGateway) {}

	// INFO
	async channels(userId: number): Promise<ChannelWithRelations[]> {
		this.logger.log('channels called');
		const channels: ChannelWithRelations[] = await this.prisma.channel.findMany({
			where: {
				users: {
					some: {
						userId: userId,
					},
				},
			},
			orderBy: {
				updatedAt: 'desc',
			},
			include: {
				owner: true,
				messages: {
					include: {
						sender: true,
					},
				},
				admins: {
					select: {
						user: true,
					},
				},
				users: {
					select: {
						user: true,
						color: {
							select: {
								code: true,
							},
						},
					},
				},
				banned: {
					select: {
						userId: true,
					},
				},
				muted: {
					select: {
						userId: true,
					},
				},
			},
		});
		for (const [i, value] of channels.entries()) {
			channels[i] = await this.cleanArrayInChannel(value, userId);
		}
		return channels;
	}

	async noChannels(userId: number): Promise<ChannelWithRelations[]> {
		this.logger.log('noChannels called');
		const noChannels: ChannelWithRelations[] = await this.prisma.channel.findMany({
			where: {
				users: {
					none: {
						userId,
					},
				},
				banned: {
					none: {
						userId,
					},
				},
				type: {
					not: 'private',
				},
			},
			include: {
				owner: true,
				admins: {
					select: {
						user: true,
					},
				},
				users: {
					select: {
						user: true,
					},
				},
			},
		});
		for (let noChannel of noChannels) {
			for (const [i, value] of (noChannel.users as any).entries())
				noChannel.users[i] = { ...value.user };
			for (const [i, value] of (noChannel.admins as any).entries())
				noChannel.admins[i] = { ...value.user };
		}
		return noChannels;
	}

	async allChannelsStartWith(obj: { name: string }): Promise<Channel[]> {
		this.logger.log('startWith called');
		return await this.prisma.channel.findMany({
			where: {
				name: {
					startsWith: obj.name,
					mode: 'insensitive',
				},
			},
		});
	}

	async channelExist(obj: { name: string }): Promise<boolean> {
		this.logger.log('channelExist called');
		if (
			(await this.prisma.channel.findUnique({
				where: {
					name: obj.name,
				},
			})) === null
		)
			return true;
		return false;
	}

	// USER ACTIONS
	async create(userId: number, obj: any, file: any): Promise<boolean> {
		this.logger.log('create called');
		if (
			(await this.prisma.channel.findUnique({
				where: {
					name: obj.name,
				},
			})) !== null
		)
			return false;
		const image =
			file == undefined ||
			(file.mimetype != 'image/jpeg' &&
				file.mimetype != 'image/jpg' &&
				file.mimetype != 'image/bmp' &&
				file.mimetype != 'image/png') ||
			file.size > 1000000
				? 'https://cdn.pixabay.com/photo/2017/11/10/05/46/group-2935521_960_720.png'
				: `data:${file.mimetype};base64,${Buffer.from(file.buffer).toString('base64')}`;
		const channel: Channel = await this.prisma.channel.create({
			data: {
				name: obj.name,
				type: obj.type,
				description: obj.description,
				key: obj.type == 'protected' ? await encodePassword(obj.key) : null,
				ownerId: userId,
				image,
			},
		});
		const data: Array<{ userId: number; channelId: number; colorId?: number }> =
			obj.users.map((user) => {
				return {
					userId: user.id,
					channelId: channel.id,
					colorId: Math.floor(Math.random() * (6 - 1) + 1),
				};
			});
		if (data.length == 0) {
			data.push({ userId: userId, channelId: channel.id, colorId: 1 }); ///////
			const ownerTemp = await this.prisma.user.findUnique({
				where: {
					id: userId,
				},
			});
			obj.users.push(ownerTemp);
		}
		await this.prisma.userOnChannel.createMany({
			data: data,
		});
		await this.prisma.adminOnChannel.create({
			data: {
				userId: userId,
				channelId: channel.id,
			},
		});
		await this.chatGateway.syncChannel(obj.name);

		const usersId = obj.users.map((user) => user.id);
		this.chatGateway.joinRoom(obj.name, usersId);
		for (userId of usersId)
			await this.chatGateway.sendAndRec(obj.name, userId, 'userOnChannel', 'set');
		return true;
	}

	async join(userId: number, obj: any): Promise<boolean> {
		this.logger.log('join called');
		const channel: Channel | null = await this.prisma.channel.findUnique({
			where: {
				name: obj.name,
			},
		});
		if (
			channel === null ||
			(channel.type == 'protected' && !checkPasswords(obj.key, channel.key))
		)
			return false;
		if (await this.isSomeone(userId, obj.name, 'userOnChannel')) return false;
		await this.prisma.userOnChannel.create({
			data: {
				userId,
				channelId: await this.channelId(obj.name),
				colorId: Math.floor(Math.random() * (6 - 1) + 1),
			},
		});
		await this.chatGateway.readChannelMessage(obj.name, userId);
		await this.chatGateway.syncChannel(obj.name);
		this.chatGateway.joinRoom(obj.name, [userId]);
		await this.chatGateway.sendAndRec(obj.name, userId, 'userOnChannel', 'set');
		return true;
	}

	async leave(userId: number, obj: any): Promise<boolean> {
		this.logger.log('leave called');
		await this.unsetSomeone(userId, obj.channelName, 'userOnChannel');
		await this.unsetSomeone(userId, obj.channelName, 'adminOnChannel');
		await this.unsetSomeone(userId, obj.channelName, 'mutedOnChannel');
		await this.unsetSomeone(userId, obj.channelName, 'bannedOnChannel');

		if (await this.isOwner(userId, obj.channelName)) {
			let newOwner: AdminOnChannel | UserOnChannel | null =
				await this.prisma.adminOnChannel.findFirst({
					where: {
						channel: {
							name: obj.channelName,
						},
					},
				});
			if (newOwner == null) {
				//NON CI SONO ADMINS CHE POSSONO DIVENTARE OWNER
				newOwner = await this.prisma.userOnChannel.findFirst({
					where: {
						channel: {
							name: obj.channelName,
						},
					},
				});
				if (newOwner == null) {
					//NON CI SONO USERS CHE POSSONO DIVENTARE OWNER
					// IL CANALE CHIUDE
					await this.deleteChannel(obj.channelName);
					await this.chatGateway.syncRemoveUser(obj.channelName, userId);
					this.chatGateway.leaveRoom(obj.channelName, userId);
					return true;
				}
				await this.setSomeone(newOwner.userId, obj.channelName, 'adminOnChannel');
			}
			await this.prisma.channel.update({
				where: {
					name: obj.channelName,
				},
				data: {
					owner: {
						connect: {
							id: newOwner.userId,
						},
					},
				},
			});
		}
		await this.chatGateway.syncChannel(obj.channelName);
		await this.chatGateway.syncRemoveUser(obj.channelName, userId);
		this.chatGateway.leaveRoom(obj.channelName, userId);
		await this.chatGateway.sendAndRec(obj.channelName, userId, 'userOnChannel', 'unset');
		return true;
	}

	async deleteChannel(channelName: string): Promise<boolean> {
		this.logger.log('deleteChannel called');
		try {
			await this.prisma.bannedOnChannel.deleteMany({
				where: {
					channel: {
						name: channelName,
					},
				},
			});

			const messagesId = await this.prisma.channelMessage
				.findMany({
					where: {
						channel: { name: channelName },
					},
				})
				.then((mess) => mess.map((el) => el.id));

			await this.prisma.channelMessagesRead.deleteMany({
				where: {
					channelMessageId: {
						in: messagesId,
					},
				},
			});
			await this.prisma.channelMessage.deleteMany({
				where: {
					channel: {
						name: channelName,
					},
				},
			});
			await this.prisma.channel.delete({
				where: {
					name: channelName,
				},
			});
			return true;
		} catch (e) {}
	}

	async addUser(userId: number, obj: any): Promise<boolean> {
		this.logger.log('addUser called');
		if (!(await this.isSomeone(userId, obj.channelName, 'adminOnChannel'))) return false;
		for (let _user of obj.newUsers) {
			if (
				!(await this.isSomeone(_user.id, obj.channelName, 'userOnChannel')) &&
				!(await this.isOwner(_user.id, obj.channelName))
			) {
				await this.prisma.userOnChannel.create({
					data: {
						userId: _user.id,
						channelId: await this.channelId(obj.channelName),
						colorId: Math.floor(Math.random() * (6 - 1) + 1),
					},
				});
				await this.chatGateway.readChannelMessage(obj.channelName, _user.id);
			}
		}
		await this.chatGateway.syncChannel(obj.channelName);
		const newUsersId = obj.newUsers.map((newUser) => newUser.id);
		this.chatGateway.joinRoom(obj.channelName, newUsersId);
		for (let newUserId of newUsersId)
			await this.chatGateway.sendAndRec(
				obj.channelName,
				newUserId,
				'userOnChannel',
				'set',
			);
		return true;
	}

	async setSomeone(userId: number, channelName: string, table: string): Promise<boolean> {
		this.logger.log(`set ${table} called`);
		if (await this.isSomeone(userId, channelName, table)) return false;
		await this.prisma[table].create({
			data: {
				userId: userId,
				channelId: await this.channelId(channelName),
			},
		});
		return true;
	}

	async unsetSomeone(
		userId: number,
		channelName: string,
		table: string,
	): Promise<boolean> {
		this.logger.log(`unset ${table} called`);
		if (!(await this.isSomeone(userId, channelName, table))) return false;
		await this.prisma[table].delete({
			where: {
				userId_channelId: {
					userId: userId,
					channelId: await this.channelId(channelName),
				},
			},
		});
		return true;
	}

	async changeKey(userId: number, channelName: string, key: string): Promise<boolean> {
		this.logger.log('changeKey called');
		await this.prisma.channel.update({
			where: {
				name: channelName,
			},
			data: {
				key: await encodePassword(key),
				type: 'protected',
			},
		});
		await this.chatGateway.syncChannel(channelName);
		return true;
	}

	async removeKey(userId: number, channelName: string): Promise<boolean> {
		this.logger.log('removeKey called');
		await this.prisma.channel.update({
			where: {
				name: channelName,
			},
			data: {
				key: null,
				type: 'public',
			},
		});
		await this.chatGateway.syncChannel(channelName);
		return true;
	}

	// UTILS
	async isSomeone(userId: number, channelName: string, table: string): Promise<boolean> {
		let ret: boolean = false;
		try {
			if (
				(await this.prisma[table].findUnique({
					where: {
						userId_channelId: {
							userId: userId,
							channelId: await this.channelId(channelName),
						},
					},
				})) !== null
			)
				ret = true;
		} catch (error) {}
		this.logger.log(`isSomeone ${userId},${channelName},${table} called, ret: ${ret}`);
		return ret;
	}

	async isOwner(userId: number, channelName: string): Promise<boolean> {
		if (
			(await this.prisma.user.findFirst({
				where: {
					AND: [
						{
							id: userId,
						},
						{
							ownerOnChannel: {
								some: {
									name: channelName,
								},
							},
						},
					],
				},
			})) !== null
		) {
			return true;
		}
		return false;
	}

	async checkPermissions(
		srcId: number,
		destId: number,
		channelName: string,
	): Promise<boolean> {
		if (
			!(await this.isSomeone(srcId, channelName, 'adminOnChannel')) ||
			!(await this.isSomeone(destId, channelName, 'userOnChannel')) ||
			(await this.isOwner(destId, channelName))
		)
			return false;
		return true;
	}

	async channelId(channelName: string): Promise<number> {
		return await this.prisma.channel
			.findUnique({
				where: {
					name: channelName,
				},
				select: {
					id: true,
				},
			})
			.then((chan) => chan.id);
	}

	async cleanArrayInChannel(channel: any, userId: number) {
		delete channel['key'];
		const colors = channel.users.map((user) => {
			return { userId: user.user.id, color: user.color.code };
		});
		for (const [i, value] of (channel.users as any).entries())
			channel.users[i] = { ...value.user };
		for (const [i, value] of (channel.admins as any).entries())
			channel.admins[i] = { ...value.user };
		for (const [i, value] of (channel.banned as any).entries())
			channel.banned[i] = value.userId;
		for (const [i, value] of (channel.muted as any).entries())
			channel.muted[i] = value.userId;
		let messages: any[] = [];
		for (const [i, value] of (channel.messages as any).entries()) {
			const colorCode = colors.find(({ userId }) => userId === value.sender.id);
			messages.push({
				sender: {
					...value.sender,
					color: colorCode == undefined ? 'black' : colorCode.color,
				},
				receiver: channel.name,
				text: value.text,
				serverMessage: value.isServerMessage,
			});
		}
		let notifications = await this.prisma.channelMessage.count({
			where: {
				channelId: channel.id,
				usersReadMessages: {
					none: {
						userId,
					},
				},
			},
		});
		channel = { ...channel, messages, notifications };
		return channel;
	}
}
