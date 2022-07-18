import {  Injectable, Logger } from '@nestjs/common';
import { ChatGateway } from 'src/chat/chat.gateway';
import { PrismaService } from 'src/prisma/prisma.service';
import { SCORING_LIMIT } from './game.service';
import { MatchUsers } from './interfaces/game.interfaces';

@Injectable()
export class MatchService {
	constructor(private prisma: PrismaService, private chatGateway: ChatGateway) {}
	private readonly logger = new Logger(MatchService.name);
	async createMatch(data: MatchUsers) {
		const match = await this.prisma.match.create({
			data: {
				winningScore: SCORING_LIMIT,
				winnerId: data.winnerID,
				losingScore: data.losingScore,
				loserId: data.loserID,
				special: data.special,
			},
		});
		const roomPlayers: Array<{
			matchId: number;
			statisticId: number;
		}> = [
			{
				matchId: match.id,
				statisticId: await this.prisma.statistic
					.findFirst({
						where: {
							userId: data.winnerID,
						},
					})
					.then((statistic) => statistic.id),
			},
			{
				matchId: match.id,
				statisticId: await this.prisma.statistic
					.findFirst({
						where: {
							userId: data.loserID,
						},
					})
					.then((statistic) => statistic.id),
			},
		];

		await this.prisma.matchOnStatistic.createMany({
			data: roomPlayers,
		});
		if (data.special) {
			await this.prisma.statistic.update({
				where: {
					userId: data.winnerID,
				},
				data: {
					winsSpecial: {
						increment: 1,
					},
					ladderLevelSpecial: {
						increment: 20,
					},
				},
			});
			await this.prisma.statistic.update({
				where: {
					userId: data.loserID,
				},
				data: {
					lossesSpecial: {
						increment: 1,
					},
				},
			});
		} else {
			await this.prisma.statistic.update({
				where: {
					userId: data.winnerID,
				},
				data: {
					wins: {
						increment: 1,
					},
					ladderLevel: {
						increment: 20,
					},
				},
			});
			await this.prisma.statistic.update({
				where: {
					userId: data.loserID,
				},
				data: {
					losses: {
						increment: 1,
					},
				},
			});
			await this.updateAchievements(data.winnerID, data.loserID);
		}
	}

	async updateInGameState(userId: number) {
		let status = await this.prisma.user
			.findFirst({
				where: {
					id: userId,
				},
				select: {
					status: true,
				},
			})
			.then((obj) => obj.status);
		status = status === 'online' ? 'in game' : 'online';
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				status,
			},
		});
		await this.chatGateway.syncFriends(userId);
	}

	async updateAchievements(winnerId: number, loserId: number) {
		const max = await this.prisma.statistic
			.findFirst({
				where: {
					userId: {
						not: winnerId,
					},
				},
				orderBy: {
					ladderLevel: 'desc',
				},
			})
			.then((stat) => stat.ladderLevel);
		const winner = await this.prisma.user.findUnique({
			where: {
				id: winnerId,
			},
			include: {
				statistics: true,
			},
		});
		if (winner.statistics.ladderLevel >= max) {
			if (winner.statistics.ladderLevel > max) {
				try {
					await this.prisma.achievementOnStatistic.deleteMany({
						where: {
							achievementId: await this.getAchievementId('KOP'),
						},
					});
				} catch (e) {}
			}
			if (!(await this.hasAchievement(winner.statistics.id, 'KOP'))) {
				try {
					await this.prisma.achievementOnStatistic.create({
						data: {
							statisticId: winner.statistics.id,
							achievementId: await this.getAchievementId('KOP'),
						},
					});
				} catch (e) {}
			}
			if (await this.hasAchievement(winner.statistics.id, 'WPP')) {
				try {
					await this.prisma.achievementOnStatistic.delete({
						where: {
							achievementId_statisticId: {
								achievementId: await this.getAchievementId('WPP'),
								statisticId: winner.statistics.id,
							},
						},
					});
				} catch (e) {}
			}
		}
		let min = await this.prisma.statistic
			.findFirst({
				where: {
					userId: {
						not: winnerId,
					},
				},
				orderBy: {
					ladderLevel: 'asc',
				},
			})
			.then((stat) => stat.ladderLevel);
		if (
			winner.statistics.ladderLevel > min &&
			this.hasAchievement(winner.statistics.id, 'WPP')
		) {
			try {
				await this.prisma.achievementOnStatistic.delete({
					where: {
						achievementId_statisticId: {
							achievementId: await this.getAchievementId('WPP'),
							statisticId: winner.statistics.id,
						},
					},
				});
			} catch (e) {}
		}

		const loser = await this.prisma.user.findUnique({
			where: {
				id: loserId,
			},
			include: {
				statistics: true,
			},
		});
		min = await this.prisma.statistic
			.findFirst({
				orderBy: {
					ladderLevel: 'asc',
				},
			})
			.then((stat) => stat.ladderLevel);
		if (
			loser.statistics.ladderLevel == min &&
			!this.hasAchievement(loser.statistics.id, 'WPP')
		) {
			try {
				await this.prisma.achievementOnStatistic.create({
					data: {
						achievementId: await this.getAchievementId('WPP'),
						statisticId: loser.statistics.id,
					},
				});
			} catch (e) {}
		}
	}

	async getAchievementId(name: string) {
		return await this.prisma.achievement
			.findUnique({
				where: {
					name,
				},
			})
			.then((ach) => ach.id);
	}

	async hasAchievement(statisticId: number, name: string) {
		if (
			(await this.prisma.achievementOnStatistic.findUnique({
				where: {
					achievementId_statisticId: {
						achievementId: await this.getAchievementId(name),
						statisticId,
					},
				},
			})) == null
		)
			return false;
		return true;
	}
}
