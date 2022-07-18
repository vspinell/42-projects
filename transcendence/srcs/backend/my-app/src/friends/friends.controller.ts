import {
	Body,
	Controller,
	Delete,
	Get,
	Logger,
	Post,
	Req,
	Res,
	UseFilters,
	UseGuards,
} from '@nestjs/common';
import { Request, Response } from 'express';
import { JwtGuard } from 'src/auth/guard';
import { HttpExceptionFilter } from 'src/filters/http-exception.filter';
import { User } from 'src/user/dto/user.dto';
import { FriendsService } from './friends.service';

@UseFilters(HttpExceptionFilter)
@UseGuards(JwtGuard)
@Controller('friends')
export class FriendsController {
	private readonly logger = new Logger(FriendsController.name);
	constructor(private friendsService: FriendsService) {}

	//INFO
	@Get()
	async friends(@Req() req: Request): Promise<User[]> {
		this.logger.log('all called');
		return await this.friendsService.friends(Object(req.user).id);
	}

	@Get('noFriends')
	async noFriends(@Req() req: Request): Promise<User[]> {
		this.logger.log('all no Friends called');
		return await this.friendsService.noFriends(Object(req.user).id);
	}

	@Post('search')
	async searchFriend(@Req() req: Request, @Body() data: any): Promise<User[]> {
		this.logger.log('search called');
		return await this.friendsService.searchFriend(Object(req.user).id, data);
	}

	@Post('searchNo')
	async searchNoFriend(@Req() req: Request, @Body() data: any): Promise<User[]> {
		this.logger.log('searchNo called');
		return await this.friendsService.searchNoFriend(Object(req.user).id, data);
	}

	@Post('userFriends')
	async userFriends(@Body() data: { userId: number }): Promise<User[]> {
		this.logger.log('searchNo called');
		return await this.friendsService.userFriends(data.userId);
	}

	//ACTIONS
	@Post('add')
	async askFriendship(
		@Req() req: Request,
		@Body() data: { userId: number },
	): Promise<boolean> {
		this.logger.log('add called');
		return this.friendsService.askFriendship(Object(req.user).id, data);
	}

	@Post('accept')
	async acceptFriendship(
		@Req() req: Request,
		@Body() data: { userId: number },
	): Promise<boolean> {
		this.logger.log('accept called');
		return this.friendsService.acceptFriendship(Object(req.user).id, data);
	}

	@Post('declineSent')
	async declineSentFriendship(
		@Req() req: Request,
		@Body() data: { userId: number },
	): Promise<boolean> {
		this.logger.log('decline Sent called');
		return await this.friendsService.declineSentFriendship(Object(req.user).id, data);
	}

	@Post('declineReceived')
	async declineReceivedFriendship(
		@Req() req: Request,
		@Body() data: { userId: number },
	): Promise<boolean> {
		this.logger.log('decline Received called');
		return await this.friendsService.declineReceivedFriendship(Object(req.user).id, data);
	}

	@Get('requests')
	async requestsFriendship(@Req() req: Request): Promise<User[]> {
		this.logger.log('requests called');
		return await this.friendsService.requestsFriendship(Object(req.user).id);
	}

	@Delete('remove')
	async removeFriendship(
		@Req() req: Request,
		@Body() data: { userId: number },
	): Promise<boolean> {
		this.logger.log('remove called');
		return await this.friendsService.removeFriendship(Object(req.user).id, data);
	}

	@Post('block')
	async blockFriend(
		@Req() req: Request,
		@Body() data: { userId: number },
	): Promise<boolean> {
		this.logger.log('accept called');
		return await this.friendsService.blockFriend(Object(req.user).id, data);
	}

	@Post('unblock')
	async unblockFriend(
		@Req() req: Request,
		@Body() data: { userId: number },
	): Promise<boolean> {
		this.logger.log('accept called');
		return await this.friendsService.unblockFriend(Object(req.user).id, data);
	}
}
