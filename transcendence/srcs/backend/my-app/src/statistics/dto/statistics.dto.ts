import { User } from 'src/user/dto/user.dto';

export interface Statistic {
	id: number;
	createdAt: Date;
	updatedAt: Date;

	time?: number;

	wins?: number;
	losses?: number;
	ladderLevel?: number;

	winsSpecial?: number;
	lossesSpecial?: number;
	ladderLevelSpecial?: number;
}

export interface StatisticWithRelations extends Statistic {
	user: User;
	userId: number;
	achievements: AchievementOnStatistic[];
	matchHistory: MatchOnStatistic[];
}

export interface Match {
	id: number;
	winningScore: number;
	losingScore: number;
	createdAt: Date;
	special: boolean;
}

export interface MatchWithRelations extends Match {
	winner: User;
	winnerId: number;
	loser: User;
	loserId: number;
	statistic: MatchOnStatistic[];
}

export interface MatchOnStatistic {
	match: Match;
	matchId: number;
	statistic: Statistic;
	statisticId: number;
	assignedAt: Date;
}

export interface Achievement {
	id: number;
	createdAt: Date;
	updatedAt: Date;
	name: string;
	description: string;
	statistics: AchievementOnStatistic[];
}

export interface AchievementOnStatistic {
	achievement: Achievement;
	achievementId: number;
	statistic: Statistic;
	statisticId: number;
	assignedAt: string;
}
