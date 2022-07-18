import {
	Body,
	Controller,
	Get,
	HttpException,
	HttpStatus,
	Logger,
	Post,
	Req,
	UploadedFile,
	UseFilters,
	UseGuards,
	UseInterceptors,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { Request } from 'express';
import { JwtGuard } from 'src/auth/guard';
import { HttpExceptionFilter } from 'src/filters/http-exception.filter';
import { UserService } from './user.service';
import { JwtService } from '@nestjs/jwt';
import { User } from './dto/user.dto';

@UseFilters(HttpExceptionFilter)
@UseGuards(JwtGuard)
@Controller('users')
export class UserController {
	constructor(
		private readonly userService: UserService,
		private jwtService: JwtService,
	) {}
	private readonly logger = new Logger(UserController.name);

	// INFO
	@Get('me')
	async getMe(@Req() req: Request): Promise<User> {
		this.logger.log('getMe called');
		const decodedJwt: any = this.jwtService.decode(
			req.cookies[process.env.JWT_COOKIE_NAME],
		);
		if (decodedJwt.twoFaStep) throw new HttpException('', HttpStatus.NOT_FOUND);
		return req.user;
	}

	@Post('userInfo')
	async getUser(@Body() data: { url: string }): Promise<User | boolean> {
		this.logger.log('getUserInfo called');
		return await this.userService.getUserInfo(data);
	}

	// ACTIONS
	@UseInterceptors(FileInterceptor('file'))
	@Post('image')
	async setImage(
		@Body() data: { userId: number },
		@UploadedFile() file: Express.Multer.File,
	): Promise<boolean> {
		this.logger.log('setImage called');
		return await this.userService.setImage(Number(data.userId), file);
	}

	@Post('name')
	async setName(@Body() data: { userId: number; name: string }): Promise<boolean> {
		this.logger.log('name called');
		return await this.userService.setName(data.userId, data.name);
	}
}
