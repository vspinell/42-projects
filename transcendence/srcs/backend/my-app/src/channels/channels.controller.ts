import {
	Body,
	Controller,
	Get,
	Logger,
	Post,
	Req,
	Res,
	UploadedFile,
	UseFilters,
	UseGuards,
	UseInterceptors,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { Request, Response } from 'express';
import { JwtGuard } from 'src/auth/guard';
import { ChatGateway } from 'src/chat/chat.gateway';
import { HttpExceptionFilter } from 'src/filters/http-exception.filter';
import { ChannelsService } from './channels.service';
import { Channel, ChannelWithRelations } from './dto/channels.dto';

@UseFilters(HttpExceptionFilter)
@UseGuards(JwtGuard)
@Controller('channel')
export class ChannelsController {
	constructor(
		private channelsService: ChannelsService,
		private chatGateway: ChatGateway,
	) {}
	private readonly logger = new Logger(ChannelsService.name);

	// INFO
	@Get()
	async channels(@Req() req: Request): Promise<ChannelWithRelations[]> {
		this.logger.log('channels called');
		return await this.channelsService.channels(Object(req.user).id);
	}

	@Get('noChannels')
	async noChannels(@Req() req: Request): Promise<ChannelWithRelations[]> {
		this.logger.log('noChannels called');
		return await this.channelsService.noChannels(Object(req.user).id);
	}

	@Post('startWith')
	async allChannelsStartWith(@Body() obj: { name: string }): Promise<Channel[]> {
		this.logger.log('startWith called');
		return await this.channelsService.allChannelsStartWith(obj);
	}

	@Post('channelExist')
	async channelExist(@Body() obj: { name: string }): Promise<boolean> {
		this.logger.log('channelExist called');
		return await this.channelsService.channelExist(obj);
	}

	// USER ACTIONS
	@UseInterceptors(FileInterceptor('file'))
	@Post('create')
	async create(
		@Req() req: Request,
		@Body() data: any,
		@UploadedFile() file: Express.Multer.File,
	): Promise<boolean> {
		this.logger.log('create called');
		return await this.channelsService.create(
			Object(req.user).id,
			JSON.parse(data.channel),
			file,
		);
	}

	@Post('join')
	async join(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('join called');
		return await this.channelsService.join(Object(req.user).id, data);
	}

	@Post('leave')
	async leave(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('leave called');
		return await this.channelsService.leave(Object(req.user).id, data);
	}

	// ADMIN ACTIONS
	@Post('addUser')
	async addUser(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('addUser called');
		return await this.channelsService.addUser(Object(req.user).id, data);
	}

	@Post('removeUser')
	async removeUser(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('removeUser called');
		const user = Object(req.user);
		if (!this.channelsService.checkPermissions(user.id, data.user.id, data.channelName))
			return false;
		await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'userOnChannel',
		);
		await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'adminOnChannel',
		);
		await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'mutedOnChannel',
		);
		await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'bannedOnChannel',
		);
		await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.syncRemoveUser(data.channelName, data.user.id);
		this.chatGateway.leaveRoom(data.channelName, data.user.id);
		await this.chatGateway.sendAndRec(
			data.channelName,
			data.user.id,
			'userOnChannel',
			'unset',
		);
		return true;
	}

	@Post('setAdmin')
	async setAdmin(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('setAdmin called');
		const user = Object(req.user);
		if (!this.channelsService.checkPermissions(user.id, data.user.id, data.channelName))
			return false;
		const ret = await this.channelsService.setSomeone(
			data.user.id,
			data.channelName,
			'adminOnChannel',
		);
		await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.sendAndRec(
			data.channelName,
			data.user.id,
			'adminOnChannel',
			'set',
		);
		return ret;
	}

	@Post('unsetAdmin')
	async unsetAdmin(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('unsetAdmin called');
		const user = Object(req.user);
		if (!this.channelsService.checkPermissions(user.id, data.user.id, data.channelName))
			return false;
		const ret = await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'adminOnChannel',
		);
		await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.sendAndRec(
			data.channelName,
			data.user.id,
			'adminOnChannel',
			'unset',
		);
		return ret;
	}

	@Post('setMuted')
	async setMuted(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('setMuted called');
		const user = Object(req.user);
		if (!this.channelsService.checkPermissions(user.id, data.user.id, data.channelName))
			return false;
		const ret = await this.channelsService.setSomeone(
			data.user.id,
			data.channelName,
			'mutedOnChannel',
		);
		await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.sendAndRec(
			data.channelName,
			data.user.id,
			'mutedOnChannel',
			'set',
		);
		return ret;
	}

	@Post('unsetMuted')
	async unsetMuted(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('unsetMuted called');
		const user = Object(req.user);
		if (!this.channelsService.checkPermissions(user.id, data.user.id, data.channelName))
			return false;
		const ret = await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'mutedOnChannel',
		);
		await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.sendAndRec(
			data.channelName,
			data.user.id,
			'mutedOnChannel',
			'unset',
		);
		return ret;
	}

	@Post('setBanned')
	async setBanned(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('setBanned called');
		const user = Object(req.user);
		if (!this.channelsService.checkPermissions(user.id, data.user.id, data.channelName))
			return false;
		await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'userOnChannel',
		);
		await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'adminOnChannel',
		);
		await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'mutedOnChannel',
		);
		const ret = await this.channelsService.setSomeone(
			data.user.id,
			data.channelName,
			'bannedOnChannel',
		);
		// await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.sendAndRec(
			data.channelName,
			data.user.id,
			'bannedOnChannel',
			'set',
		);
		await this.chatGateway.syncRemoveUser(data.channelName, data.user.id);
		this.chatGateway.leaveRoom(data.channelName, data.user.id);
		return ret;
	}

	@Post('unsetBanned')
	async unsetBanned(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('unsetBanned called');
		const user = Object(req.user);
		if (!this.channelsService.checkPermissions(user.id, data.user.id, data.channelName))
			return false;
		const ret = await this.channelsService.unsetSomeone(
			data.user.id,
			data.channelName,
			'bannedOnchannel',
		);
		await this.chatGateway.syncChannel(data.channelName);
		await this.chatGateway.sendAndRec(
			data.channelName,
			data.user.id,
			'bannedOnChannel',
			'unset',
		);

		await this.channelsService.setSomeone(
			data.user.id,
			data.channelName,
			'userOnChannel',
		);
		await this.chatGateway.syncChannel(data.channelName);
		this.chatGateway.joinRoom(data.channelName, data.user.id);

		return ret;
	}

	@Post('changePassword')
	async changeKey(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('changeKey called');
		if (!this.channelsService.isOwner(Object(req.user).id, data.channelName))
			return false;
		return await this.channelsService.changeKey(
			Object(req.user).id,
			data.channelName,
			data.newPassword,
		);
	}

	@Post('removePassword')
	async removeKey(@Req() req: Request, @Body() data: any): Promise<boolean> {
		this.logger.log('removeKey called');
		if (!this.channelsService.isOwner(Object(req.user).id, data.channelName))
			return false;
		return await this.channelsService.removeKey(Object(req.user).id, data.channelName);
	}
}
