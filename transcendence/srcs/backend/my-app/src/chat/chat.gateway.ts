import { Injectable, Logger } from '@nestjs/common';
import {
	WebSocketGateway,
	SubscribeMessage,
	MessageBody,
	WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { Channel, ChannelMessage } from 'src/channels/dto/channels.dto';
import { PrismaService } from 'src/prisma/prisma.service';
import { UserWithRelations } from 'src/user/dto/user.dto';

export let mapUsers = new Map<number, Socket>();

export interface InviteObj {
	idSender: number;
	idRecever: number;
	gameMode: 'classic' | 'special';
	accepted: boolean;
}
const port =
	Number(process.env.FRONTEND_PORT) == 80
		? [
				`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}`,
				`http://${process.env.IP_SERVER}`,
		  ]
		: [`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}`];
@WebSocketGateway({
	cors: {
		origin: port,
	},
	namespace: 'chat',
})
@Injectable()
export class ChatGateway {
	constructor(private prisma: PrismaService) {}
	private readonly logger = new Logger(ChatGateway.name);
	date = new Date().toISOString();

	//SERVER
	@WebSocketServer() server: Server;

	async handleConnection(socket: Socket): Promise<void> {
		const socketId: string = socket.id;
		const userId: number = Number(socket.handshake.query.id);
		try {
			const user = await this.prisma.user.update({
				where: { id: userId },
				data: {
					status: 'online',
				},
				include: {
					privateInfo: true,
				},
			});
			await this.prisma.privateInfo.update({
				where: {
					id: user.privateInfo.id,
				},
				data: {
					socketIdChat: socketId,
				},
			});
			this.server
				.to(await this.getSocketId(userId))
				.emit('private', { type: 'sync', message: 'start' });
			await this.syncFriends(userId);
			mapUsers.set(userId, socket);
			await this.addUserInRooms(userId);
		} catch (e) {}
	}

	async handleDisconnect(socket: Socket): Promise<void> {
		const socketId: string = socket.id;
		const userId: number = await this.getUserId(socketId);
		try {
			const user = await this.prisma.user.update({
				where: {
					id: userId,
				},
				data: {
					status: 'offline',
				},
				include: {
					friends: true,
					privateInfo: true,
				},
			});
			await this.prisma.privateInfo.update({
				where: {
					id: user.privateInfo.id,
				},
				data: {
					socketIdChat: null,
				},
			});
			await this.syncFriends(user.id);
			mapUsers.delete(user.id);
		} catch (e) {}
	}

	@SubscribeMessage('iRead')
	async iRead(client: Socket, chat: number | string): Promise<void> {
		this.logger.log('iRead called');
		switch (typeof chat) {
			case 'string': {
				await this.readChannelMessage(chat as string, await this.getUserId(client.id));
				break;
			}
			case 'number': {
				await this.readPrivateMessage(chat as number, await this.getUserId(client.id));
				break;
			}
		}
	}

	async readChannelMessage(channelName: string, userId: number): Promise<void> {
		this.logger.log('read Channel message');
		let messages = await this.prisma.channelMessage.findMany({
			where: {
				channelId: await this.getChannelId(channelName),
				usersReadMessages: {
					none: {
						userId,
					},
				},
			},
			include: {
				usersReadMessages: true,
			},
		});
		const data = messages.map((mess) => {
			return { channelMessageId: mess.id, userId };
		});
		try {
			await this.prisma.channelMessagesRead.createMany({
				data,
			});
		} catch (e) {}
	}

	async readPrivateMessage(senderId: number, receiverId: number): Promise<void> {
		this.logger.log('read Private message');
		await this.prisma.privateMessage.updateMany({
			where: {
				senderId,
				receiverId,
				read: false,
			},
			data: {
				read: true,
			},
		});
	}

	//GAME
	@SubscribeMessage('game')
	async handleInvitationGame(client: Socket, invite: InviteObj): Promise<void> {
		if (invite.accepted)
		{
			let status = await this.prisma.user
			.findFirst({
				where: {
					id: invite.idRecever,
				},
				select: {
					status: true,
				},
			})
			.then((obj) => obj.status);
			if (status === 'in game')
			{
				let clientId = await this.getSocketId(invite.idSender)
				this.server.to(clientId).emit('game', {
					type: 'invitation',
					message: 'error',
					origin: 'Player already in game',
				});
				return;
			}
		}
		const receiver = !invite.accepted ? invite.idRecever : invite.idSender;
		let socketReceiver = await this.getSocketId(receiver);
		let status2;
		let status = await this.prisma.user
			.findFirst({
				where: {
					id: receiver,
				},
				select: {
					status: true,
				},
			})
			.then((obj) => obj.status);
		if (!invite.accepted) {
			const idReceiver = await this.prisma.user
				.findFirst({
					where: {
						id: invite.idSender,
					},
					select: {
						login: true,
					},
				})
				.then((obj) => obj.login);
			status2 = {
				status,
				login: idReceiver,
			};
		}

		// .then((obj) => obj.status);
		let message = !invite.accepted ? 'invite' : 'accepted';
		status2 = !invite.accepted ? status2 : { status, login: '' };
		this.invitationGameResponse(status2, client.id, socketReceiver, invite, message);
	}

	invitationGameResponse(
		status: { status: 'in game' | 'online' | 'offline'; login: string },
		clientID: string,
		socketReceiver: string,
		invite: InviteObj,
		message: string,
	) {
		switch (status.status) {
			case 'in game':
				this.server.to(clientID).emit('game', {
					type: 'invitation',
					message: 'error',
					origin: 'Player already in game',
				});
				break;
			case 'offline':
				this.server.to(clientID).emit('game', {
					type: 'invitation',
					message: 'error',
					origin: 'Player not online',
				});
				break;
			case 'online':
				if (message === 'accepted')
					this.server.to(clientID).emit('game', {
						type: 'invitation',
						message,
						origin: { ...invite },
					});
				this.server.to(socketReceiver).emit('game', {
					type: 'invitation',
					message,
					origin: { ...invite },
					login: status.login,
				});
				break;
		}
	}

	//PRIVATE CHAT
	@SubscribeMessage('private')
	async handlePrivateMessage(
		@MessageBody() obj: { sender: number; receiver: number; text: string },
	): Promise<void> {
		this.logger.log('handlePrivateMessage');
		this.server
			.to(await this.getSocketId(obj.receiver))
			.emit('private', { type: 'chat', message: 'newMessage', origin: obj });
		this.server
			.to(await this.getSocketId(obj.sender))
			.emit('private', { type: 'chat', message: 'newMessage', origin: obj });
		await this.prisma.privateMessage.create({
			data: {
				text: obj.text,
				senderId: obj.sender,
				receiverId: obj.receiver,
				read: false,
			},
		});
	}

	async syncRemove(friendId: number, userId: number): Promise<void> {
		this.server
			.to(await this.getSocketId(userId))
			.emit('private', { type: 'sync', message: 'remove', origin: friendId });
	}

	async syncFriends(userId: number): Promise<void> {
		let user: any = await this.prisma.user.findUnique({
			where: {
				id: userId,
			},
			include: {
				friends: {
					include: {
						privateInfo: true,
					},
				},
			},
		});
		let messages;
		for (let friend of user.friends) {
			messages = await this.prisma.privateMessage.findMany({
				orderBy: {
					createdAt: 'asc',
				},
				where: {
					OR: [
						{
							senderId: friend.id,
							receiverId: userId,
						},
						{
							receiverId: friend.id,
							senderId: userId,
						},
					],
				},
			});
			for (let [i, value] of (messages as any).entries()) {
				messages[i] = {
					sender: value.senderId,
					receiver: value.receiverId,
					text: value.text,
				};
			}
			const notifications = await this.prisma.privateMessage.count({
				where: {
					receiverId: friend.id,
					senderId: userId,
					read: false,
				},
			});

			this.server.to(friend.privateInfo.socketIdChat).emit('private', {
				type: 'sync',
				message: 'add',
				origin: { ...user, messages, notifications },
			});
		}
	}

	async syncRequests(userId: number): Promise<void> {
		this.server
			.to(await this.getSocketId(userId))
			.emit('private', { type: 'sync', message: 'requests' });
	}

	//CHANNELS' CHAT
	@SubscribeMessage('channel')
	async handleChannelMessage(@MessageBody() obj: any): Promise<void> {
		this.logger.log('handleChannelMessage');
		obj = {
			sender: {
				...(await this.prisma.user.findUnique({
					where: {
						id: obj.sender,
					},
				})),
				color: await this.getColorCode(obj.receiver, obj.sender),
			},
			receiver: obj.receiver,
			text: obj.text,
		};
		if (
			(await this.prisma.mutedOnChannel.findUnique({
				where: {
					userId_channelId: {
						userId: obj.sender.id,
						channelId: await this.getChannelId(obj.receiver),
					},
				},
			})) != null
		)
			return;
		let data = {
			text: obj.text,
			senderId: obj.sender.id,
			channelId: await this.getChannelId(obj.receiver),
			isServerMessage: false,
		};
		const message = await this.prisma.channelMessage.create({
			data,
		});
		await this.prisma.channel.update({
			where: {
				id: data.channelId,
			},
			data: {
				updatedAt: new Date(),
			},
		});
		try {
			await this.prisma.channelMessagesRead.create({
				data: {
					channelMessageId: message.id,
					userId: obj.sender.id,
				},
			});
		} catch (e) {}
		this.server
			.to(obj.receiver)
			.emit('channel', { type: 'chat', message: 'newMessage', origin: obj });
	}

	async syncChannel(channelName: string): Promise<void> {
		let channel: any = await this.prisma.channel.findUnique({
			where: {
				name: channelName,
			},
			include: {
				messages: {
					include: {
						sender: true,
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
				admins: {
					select: {
						user: true,
					},
				},
				owner: true,
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
		delete channel.key;
		const colors = channel.users.map((user) => {
			return { userId: user.user.id, color: user.color.code };
		});
		for (const [i, value] of (channel.users as any).entries()) {
			channel.users[i] = { ...value.user };
		}
		for (const [i, value] of (channel.admins as any).entries()) {
			channel.admins[i] = { ...value.user };
		}
		for (const [i, value] of (channel.banned as any).entries()) {
			channel.banned[i] = value.userId;
		}
		for (const [i, value] of (channel.muted as any).entries()) {
			channel.muted[i] = value.userId;
		}
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
		channel = { ...channel, messages: messages };
		for (const user of channel.users) {
			let notifications = await this.prisma.channelMessage.count({
				where: {
					channelId: channel.id,
					usersReadMessages: {
						none: {
							userId: user.id,
						},
					},
				},
			});
			this.server
				.to(
					await this.prisma.privateInfo
						.findFirst({
							where: {
								userId: user.id,
							},
						})
						.then((pInfo) => pInfo.socketIdChat),
				)
				.emit('channel', {
					type: 'sync',
					message: 'add',
					origin: { ...channel, notifications },
				});
		}
	}

	async syncRemoveUser(channelName: string, userId: number): Promise<void> {
		this.server
			.to(await this.getSocketId(userId))
			.emit('channel', { type: 'sync', message: 'remove', origin: channelName });
	}

	//https://stackoverflow.com/questions/69857000/prisma-how-can-i-find-all-elements-that-match-an-id-list
	joinRoom(channelName: string, usersId: number[]): void {
		usersId.forEach((userId) => {
			mapUsers.get(userId).join(channelName);
		});
	}

	leaveRoom(channelName: string, userId: number): void {
		mapUsers.get(userId).leave(channelName);
	}

	async addUserInRooms(userId: number): Promise<void> {
		const channels: Channel[] = await this.prisma.channel.findMany({
			where: {
				users: {
					some: {
						userId,
					},
				},
			},
		});
		channels.forEach((channel) => {
			this.joinRoom(channel.name, [userId]);
		});
	}

	async sendAndRec(
		channelName: string,
		userId: number,
		table: string,
		action: string,
	): Promise<void> {
		this.logger.log('send and rec called');
		const user = await this.prisma.user.findUnique({
			where: {
				id: userId,
			},
		});
		let text: string;
		switch (table) {
			case 'userOnChannel':
				text =
					action == 'set'
						? `${user.login} joins ${channelName}`
						: `${user.login} exit ${channelName}`;
				break;
			case 'adminOnChannel':
				text = action == 'set' ? `${user.login} is admin` : `${user.login} is not admin`;
				break;
			case 'mutedOnChannel':
				text = action == 'set' ? `${user.login} is muted` : `${user.login} is not muted`;
				break;
			case 'bannedOnChannel':
				text =
					action == 'set' ? `${user.login} is banned` : `${user.login} is not banned`;
				break;
		}
		let obj = {
			sender: user,
			receiver: channelName,
			text,
			serverMessage: true,
		};
		this.server
			.to(channelName)
			.emit('channel', { type: 'chat', message: 'newMessage', origin: obj });
		const data = {
			text,
			senderId: userId,
			channelId: await this.getChannelId(channelName),
			isServerMessage: true,
		};
		await this.prisma.channelMessage.create({
			data,
		});
		await this.prisma.channel.updateMany({
			where: {
				name: channelName,
			},
			data: {
				updatedAt: new Date(),
			},
		});
	}

	//UTILS
	async getSocketId(userId: number): Promise<string> {
		const privateInfo = await this.prisma.privateInfo.findFirst({
			where: { userId },
			select: {
				socketIdChat: true,
			},
		});
		if (privateInfo != null) return privateInfo.socketIdChat;
		return null;
	}

	async getUserId(socketId: string): Promise<number> {
		const privateInfo = await this.prisma.privateInfo.findFirst({
			where: { socketIdChat: socketId },
		});
		if (privateInfo != null) return privateInfo.userId;
		return -1;
	}

	async getChannelId(channelName: string): Promise<number> {
		const chan = await this.prisma.channel.findFirst({
			where: { name: channelName },
		});
		if (chan != null) return chan.id;
		return -1;
	}

	async getColorCode(channelName: string, userId: number): Promise<string> {
		const colorCode = await this.prisma.userOnChannel
			.findFirst({
				where: {
					userId: userId,
					channel: {
						name: channelName,
					},
				},
				select: {
					color: {
						select: {
							code: true,
						},
					},
				},
			})
			.then((userOnChan) => userOnChan.color.code);
		return colorCode;
	}
}
