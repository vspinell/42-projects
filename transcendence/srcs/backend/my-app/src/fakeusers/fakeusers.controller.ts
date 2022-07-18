import { Controller, Get, Logger, Req, Res } from '@nestjs/common';
import { Request, Response } from 'express';
import { FakeUsersService } from './fakeusers.service';

@Controller('fakeusers')
export class FakeUsersController {
	private readonly logger = new Logger(FakeUsersController.name);
	constructor(private fakeUsersService: FakeUsersService) {}

	@Get()
	async createFakeUser(@Req() req: Request) {
		this.logger.log('createFakeUser called');
		return this.fakeUsersService.createFakeUser(req);
	}
}
