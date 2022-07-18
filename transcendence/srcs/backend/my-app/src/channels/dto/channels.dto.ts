import {
	AdminOnChannel,
	BannedOnChannel,
	MutedOnChannel,
	User,
	UserOnChannel,
} from 'src/user/dto/user.dto';

export interface Channel {
	id?: number;
	createdAt?: Date;
	updatedAt?: Date;

	name?: string;
	description?: string;
	type?: string;
	key?: string;
}

export interface ChannelWithRelations extends Channel {
	owner?: User;
	ownerId?: number;
	channelMessage?: ChannelMessage[];
	users?: UserOnChannel[];
	admins?: AdminOnChannel[];
	muted?: MutedOnChannel[];
	banned?: BannedOnChannel[];
}

export interface ChannelMessage {
	id?: number;
	text?: string;
	sender?: User;
	senderId?: number;
	channel?: Channel;
	channelId?: number;
	createdAt?: Date;
	toRead?: ChannelMessageRead[];
}

export interface ChannelMessageRead {
	user: User;
	userId: number;
	channelMessage: ChannelMessage;
	channelMessageId: number;
	assignedAt: Date;
}
