import { Injectable, Logger } from '@nestjs/common';
import { ChatGateway } from 'src/chat/chat.gateway';
import { PrismaService } from 'src/prisma/prisma.service';
import { User, UserWithRelations } from 'src/user/dto/user.dto';

@Injectable()
export class FriendsService {
	private readonly logger = new Logger(FriendsService.name);
	constructor(private prisma: PrismaService, private chatGateway: ChatGateway) {}

	//INFO
	async friends(userId: number): Promise<User[]> {
		this.logger.log('friends called');
		let friendsWithMess = await this.prisma.privateMessage.findMany({
			orderBy: {
				createdAt: 'asc',
			},
			where: {
				OR: [
					{
						senderId: userId,
					},
					{
						receiverId: userId,
					},
				],
			},
			select: {
				sender: true,
				receiver: true,
				createdAt: true,
			},
		});
		const reverseMap = new Map(
			friendsWithMess.map((object) => {
				if (object.sender.id == userId)
					return [
						object.receiver.id,
						{ friend: object.receiver, createdAt: object.createdAt },
					];
				else
					return [
						object.sender.id,
						{ friend: object.sender, createdAt: object.createdAt },
					];
			}),
		);
		const sortedAsc = new Map(
			[...reverseMap].sort((a, b) => (a[1].createdAt < b[1].createdAt ? 1 : -1)),
		);
		var sortedArray = Array.from(sortedAsc.values());
		let mess: any;
		for (let el of sortedArray as any) {
			mess = await this.prisma.privateMessage.findMany({
				orderBy: {
					createdAt: 'asc',
				},
				where: {
					OR: [
						{
							senderId: userId,
							receiverId: el.friend.id,
						},
						{
							receiverId: userId,
							senderId: el.friend.id,
						},
					],
				},
			});
			for (let [i, value] of (mess as any).entries()) {
				mess[i] = {
					sender: value.senderId,
					receiver: value.receiverId,
					text: value.text,
				};
			}

			const notifications = await this.prisma.privateMessage.count({
				where: {
					receiverId: userId,
					senderId: el.friend.id,
					read: false,
				},
			});
			el.friend = { ...el.friend, messages: mess, notifications };
		}
		let friendsNoMess = await this.prisma.user.findUnique({
			where: {
				id: userId,
			},
			select: {
				friends: {
					where: {
						NOT: [
							{
								sentMessages: {
									some: {
										receiverId: userId,
									},
								},
							},
							{
								receivedMessages: {
									some: {
										senderId: userId,
									},
								},
							},
						],
					},
				},
			},
		});
		let finalArray: any = friendsNoMess.friends.map(function (obj) {
			return obj;
		});
		sortedArray.forEach(function (v) {
			delete v.createdAt;
		});
		for (const [i, value] of (finalArray as any).entries()) {
			finalArray[i] = { ...value, messages: [], notifications: 0 };
		}
		for (const [i, value] of (sortedArray as any).entries()) {
			sortedArray[i] = { ...value.friend };
		}
		finalArray = [...sortedArray, ...finalArray];
		return finalArray;
	}

	async noFriends(userId: number): Promise<User[]> {
		this.logger.log('noFriends called');
		const noFriendsNoReq: { id: number }[] = await this.prisma.user.findMany({
			where: {
				NOT: [
					{
						id: userId,
					},
				],
				AND: [
					{
						NOT: [
							{
								friends: {
									some: {
										id: userId,
									},
								},
							},
							{
								blockFriendSent: {
									some: {
										id: userId,
									},
								},
							},
							{
								blockFriendReceived: {
									some: {
										id: userId,
									},
								},
							},
						],
					},
					{
						AND: [
							{
								NOT: [
									{
										friendRequestsReceived: {
											some: {
												id: userId,
											},
										},
									},
								],
							},
							{
								NOT: [
									{
										friendRequestsSent: {
											some: {
												id: userId,
											},
										},
									},
								],
							},
						],
					},
				],
			},
		});
		for (const [i, value] of (noFriendsNoReq as any).entries()) {
			noFriendsNoReq[i] = { ...value, request: 'false' };
		}
		const noFriendsReq = await this.prisma.user.findMany({
			where: {
				NOT: [
					{
						id: userId,
					},
				],
				AND: [
					{
						NOT: [
							{
								friends: {
									some: {
										id: userId,
									},
								},
							},
						],
					},
					{
						friendRequestsReceived: {
							some: {
								id: userId,
							},
						},
					},
				],
			},
		});
		for (const [i, value] of (noFriendsReq as any).entries())
			noFriendsReq[i] = { ...value, request: 'true' };
		const blockedFriends = await this.prisma.user.findMany({
			where: {
				NOT: [
					{
						id: userId,
					},
				],
				AND: [
					{
						blockFriendReceived: {
							some: {
								id: userId,
							},
						},
					},
					{
						AND: [
							{
								NOT: [
									{
										friendRequestsReceived: {
											some: {
												id: userId,
											},
										},
									},
								],
							},
							{
								NOT: [
									{
										friendRequestsSent: {
											some: {
												id: userId,
											},
										},
									},
								],
							},
						],
					},
				],
			},
		});
		for (const [i, value] of (blockedFriends as any).entries()) {
			blockedFriends[i] = { ...value, request: 'blocked' };
		}
		const result = noFriendsNoReq.concat(noFriendsReq, blockedFriends);
		return result;
	}

	async searchFriend(userId: number, obj: { name: string }): Promise<User[]> {
		this.logger.log('search called');
		return await this.prisma.user.findMany({
			where: {
				login: {
					startsWith: obj.name,
					mode: 'insensitive',
				},
				friends: {
					some: {
						id: userId,
					},
				},
			},
		});
	}

	async searchNoFriend(userId: number, obj: { name: string }): Promise<User[]> {
		this.logger.log('searchNo called');
		return await this.prisma.user.findMany({
			where: {
				login: {
					startsWith: obj.name,
					mode: 'insensitive',
				},
				NOT: [
					{
						friends: {
							some: {
								id: userId,
							},
						},
					},
				],
			},
		});
	}

	async userFriends(userId: number): Promise<User[]> {
		this.logger.log('userFriends called');
		return await this.prisma.user
			.findUnique({
				where: {
					id: userId,
				},
				select: {
					friends: true,
				},
			})
			.then((user) => user.friends);
	}

	//ACTIONS
	async askFriendship(userId: number, obj: { userId: number }): Promise<boolean> {
		this.logger.log('add called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				friendRequestsSent: {
					connect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});
		await this.chatGateway.syncRequests(userId);
		await this.chatGateway.syncRequests(obj.userId);
		return true;
	}

	async acceptFriendship(userId: number, obj: { userId: number }): Promise<boolean> {
		this.logger.log('accept called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				friends: {
					connect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});

		await this.prisma.user.update({
			where: {
				id: obj.userId,
			},
			data: {
				friends: {
					connect: [
						{
							id: userId,
						},
					],
				},
			},
		});

		await this.prisma.user.update({
			//TODOAR
			where: {
				id: userId,
			},
			data: {
				friendRequestsReceived: {
					disconnect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});

		await this.chatGateway.syncRequests(obj.userId);
		this.chatGateway.syncFriends(userId);
		this.chatGateway.syncFriends(obj.userId);
		return true;
	}

	async declineSentFriendship(userId: number, obj: { userId: number }): Promise<boolean> {
		this.logger.log('decline Sent called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				friendRequestsSent: {
					disconnect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});
		await this.chatGateway.syncRequests(userId);
		await this.chatGateway.syncRequests(obj.userId);
		return true;
	}

	async declineReceivedFriendship(
		userId: number,
		obj: { userId: number },
	): Promise<boolean> {
		this.logger.log('decline Received called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				friendRequestsReceived: {
					disconnect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});
		await this.chatGateway.syncRequests(obj.userId);
		await this.chatGateway.syncRequests(userId);
		return true;
	}

	async requestsFriendship(userId: number): Promise<User[]> {
		this.logger.log('requests called');
		return await this.prisma.user
			.findUnique({
				where: {
					id: userId,
				},
				select: {
					friendRequestsReceived: true,
				},
			})
			.then((user) => user.friendRequestsReceived);
	}

	async removeFriendship(userId: number, obj: { userId: number }): Promise<boolean> {
		this.logger.log('remove called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				friends: {
					disconnect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});

		await this.prisma.user.update({
			where: {
				id: obj.userId,
			},
			data: {
				friends: {
					disconnect: [
						{
							id: userId,
						},
					],
				},
			},
		});

		await this.prisma.privateMessage.deleteMany({
			where: {
				OR: [
					{
						senderId: userId,
						receiverId: obj.userId,
					},
					{
						senderId: obj.userId,
						receiverId: userId,
					},
				],
			},
		});
		await this.chatGateway.syncRemove(userId, obj.userId);
		await this.chatGateway.syncRemove(obj.userId, userId);
		return true;
	}

	async blockFriend(userId: number, obj: { userId: number }): Promise<boolean> {
		this.logger.log('block called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},

			data: {
				friends: {
					disconnect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});

		await this.prisma.user.update({
			where: {
				id: obj.userId,
			},
			data: {
				friends: {
					disconnect: [
						{
							id: userId,
						},
					],
				},
			},
		});

		await this.prisma.privateMessage.deleteMany({
			where: {
				OR: [
					{
						senderId: userId,
						receiverId: obj.userId,
					},
					{
						senderId: obj.userId,
						receiverId: userId,
					},
				],
			},
		});

		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				blockFriendSent: {
					connect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});
		this.chatGateway.syncRemove(userId, obj.userId);
		this.chatGateway.syncRemove(obj.userId, userId);
		return true;
	}

	async unblockFriend(userId: number, obj: { userId: number }): Promise<boolean> {
		this.logger.log('unblock called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				blockFriendSent: {
					disconnect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});

		await this.prisma.user.update({
			where: {
				id: userId,
			},

			data: {
				friends: {
					connect: [
						{
							id: obj.userId,
						},
					],
				},
			},
		});

		await this.prisma.user.update({
			where: {
				id: obj.userId,
			},
			data: {
				friends: {
					connect: [
						{
							id: userId,
						},
					],
				},
			},
		});
		await this.chatGateway.syncRequests(obj.userId);
		await this.chatGateway.syncRequests(userId);
		this.chatGateway.syncFriends(userId);
		this.chatGateway.syncFriends(obj.userId);
		return true;
	}
}
