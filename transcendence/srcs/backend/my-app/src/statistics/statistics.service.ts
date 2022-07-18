import { Injectable, Logger } from '@nestjs/common';
import { PrismaService } from 'src/prisma/prisma.service';

@Injectable()
export class StatisticsService {
	private readonly logger = new Logger(StatisticsService.name);
	constructor(private prisma: PrismaService) {
		this.init();
	}

	private async init() {
		await this.prisma.achievement
			.createMany({
				data: [
					{ name: 'KOP', description: 'King Of Pong' },
					{ name: 'WPP', description: 'Worst Pong Player' },
				],
			})
			.catch(() => {});
	}

	async statistics(userId: number) {
		this.logger.log('userStatistics called');
		const statistics = await this.prisma.statistic.findFirst({
			where: {
				userId,
			},
		});
		const achievements = await this.prisma.achievement.findMany({
			where: {
				statistics: {
					some: {
						statisticId: statistics.id,
					},
				},
			},
		});
		const matchHistory = await this.prisma.match.findMany({
			orderBy : {
				createdAt : "desc"
			},
			where: {
				statistic: {
					some: {
						statisticId: statistics.id,
					},
				},
			},
			include: {
				loser: true,
				winner: true,
			},
		});
		const ladderLevels = await this.prisma.statistic.findMany({
			orderBy: {
				ladderLevel: 'desc',
			},
		});
		const rank =
			ladderLevels.findIndex((ladderLevel) => (ladderLevel as any).userId == userId) + 1;
		const ladderLevelsSpecial = await this.prisma.statistic.findMany({
			orderBy: {
				ladderLevelSpecial: 'desc',
			},
		});
		const rankSpecial =
			ladderLevelsSpecial.findIndex(
				(ladderLevel) => (ladderLevel as any).userId == userId,
			) + 1;

		for (const [i, value] of (achievements as any).entries()) {
			const achOnStat = await this.prisma.achievementOnStatistic.findUnique({
				where: {
					achievementId_statisticId: {
						achievementId: value.id,
						statisticId: statistics.id,
					},
				},
			});
			achievements[i] = { ...value, assignedAt: achOnStat.assignedAt };
		}

		return { ...statistics, rank, rankSpecial, achievements, matchHistory };
	}
}
