import {
	Body,
	Controller,
	Get,
	Logger,
	Post,
	Query,
	Req,
	ConflictException,
	NotFoundException,
	UseGuards,
} from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { Request, Response } from 'express';
import { AuthService } from './auth.service';
import { SingInData, SingUpData } from './dto';
import { JwtGuard } from './guard';

@Controller('auth')
export class AuthController {
	private readonly logger = new Logger(AuthController.name);
	constructor(private authService: AuthService, private jwtService: JwtService) {}

	@Get()
	async login42(@Query('code') code: string, @Req() req: Request): Promise<void> {
		this.logger.log('login42 called');
		const obj = await this.authService.login42(code, req.res);
		if (obj != undefined && obj.twoFaStep) {
			this.jwtService.decode(req.cookies[process.env.JWT_COOKIE_NAME]);
			req.res.redirect(
				`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}/twoFactorAuth`,
			);
		} else if (obj != undefined && obj.isNewUser) {
			req.res.redirect(
				`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}/settings`,
			);
		} else
			req.res.redirect(
				`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}/home`,
			);
	}

	@UseGuards(JwtGuard)
	@Get('logout')
	logout(@Req() req: Request): boolean {
		req.res.clearCookie(`${process.env.JWT_COOKIE_NAME}`);
		return true;
	}

	@Post('signUp')
	async signUp(
		@Req() req: Request,
		@Body() data: SingUpData,
	): Promise<boolean | { userId: number; twoFaStep: boolean }> {
		this.logger.log('signUp called');
		try {
			// return await this.authService.signUp(email, password);
			return await this.authService.signUp(req.res, data);
		} catch (error) {
			if (error instanceof ConflictException) {
				throw new ConflictException('User already exists');
			}
			throw error;
		}
	}

	@Post('signIn')
	async signIn(
		@Req() req: Request,
		@Body() data: SingInData,
	): Promise<boolean | { userId: number; twoFaStep: boolean }> {
		try {
			this.logger.log('signIn called');
			this.logger.log(data);
			const obj = await this.authService.signIn(req.res, data);
			this.logger.debug(obj);
			return obj;
		} catch (error) {
			if (error instanceof NotFoundException) throw new NotFoundException(data.login);
		}
	}
}
