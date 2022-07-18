import {
	Channel,
	ChannelMessage,
	ChannelMessageRead,
} from 'src/channels/dto/channels.dto';
import { Match, Statistic } from 'src/statistics/dto/statistics.dto';

export interface User {
	id?: number;
	createdAt?: Date;
	updatedAt?: Date;

	login?: string;
	email?: string;
	image?: string;

	status?: string;
	isTwoFactorAuthEnabled?: boolean;
}

export interface UserWithRelations extends User {
	statistics?: Statistic;
	privateInfo?: PrivateInfo;

	friendRequestsSent?: User[];
	friendRequestsReceived?: User[];
	friends?: User[];
	friendsRelation?: User[];
	blockFriendSent?: User[];
	blockFriendReceived?: User[];

	receivedMessage?: PrivateMessage[];
	sentMessage?: PrivateMessage[];

	channels?: UserOnChannel[];
	channelMessage?: ChannelMessage[];
	channelMessageRead?: ChannelMessageRead[];

	ownerOnChannel?: Channel[];
	adminOnChannel?: AdminOnChannel[];
	mutedOnChannel?: MutedOnChannel[];
	bannedOnChannel?: BannedOnChannel[];

	wins?: Match[];
	losses?: Match[];
}

export interface PrivateInfo {
	id?: number;
	createdAt?: Date;
	updatedAt?: Date;

	user?: User;
	userId?: number;

	password?: string;
	socketIdChat?: string;
	twoFactorAuthSecret?: string;
	twoFactorAuthUrl?: string;
}

export interface UserOnChannel {
	user?: User;
	userId?: number;
	channel?: Channel;
	channelId?: number;
	assignedAt?: Date;
}

export interface AdminOnChannel {
	user?: User;
	userId?: number;
	channel?: Channel;
	channelId?: number;
	assignedAt?: Date;
}

export interface MutedOnChannel {
	user?: User;
	userId?: number;
	channel?: Channel;
	channelId?: number;
	assignedAt?: Date;
}

export interface BannedOnChannel {
	user?: User;
	userId?: number;
	channel?: Channel;
	channelId?: number;
	assignedAt?: Date;
}

export interface PrivateMessage {
	id?: number;
	text?: string;
	sender?: User;
	senderId?: number;
	receiver?: User;
	receiverId?: number;
	createdAt?: Date;
	read?: boolean;
}

export interface InviteObj {
	idSender: number;
	idRecever: number;
	gameMode: 'classic' | 'special';
	accepted: boolean;
}
