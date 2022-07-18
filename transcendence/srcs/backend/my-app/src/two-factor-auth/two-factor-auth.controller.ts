import {
	Controller,
	Get,
	Logger,
	Post,
	Query,
	Req,
	Res,
	UseGuards,
} from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { Request, Response } from 'express';
import { JwtGuard } from 'src/auth/guard';
import { TwoFactorAuthService } from './two-factor-auth.service';

//GUIDA: https://wanago.io/2021/03/08/api-nestjs-two-factor-authentication/
@Controller('2fa')
export class TwoFactorAuthController {
	constructor(
		private readonly twoFactorAuthService: TwoFactorAuthService,
		private jwt: JwtService,
	) {}
	private readonly logger = new Logger(TwoFactorAuthController.name);

	// INFO
	@Get('me')
	async getMe(@Req() req: Request): Promise<boolean> {
		this.logger.log('getMe called');
		const decodedJwt: any = this.jwt.decode(req.cookies[process.env.JWT_COOKIE_NAME]);
		if (decodedJwt != null && decodedJwt.twoFaStep) return true;
		return false;
	}

	@UseGuards(JwtGuard)
	@Get('qrcode')
	async getQrcode(@Req() req: Request, @Res() res: Response): Promise<any> {
		return await this.twoFactorAuthService.pipeQrCodeStream(
			res,
			await this.twoFactorAuthService.getQrcode(Object(req.user).id),
		);
	}

	@UseGuards(JwtGuard)
	@Get('validate')
	async validate(
		@Req() req: Request,
		@Res() res: Response,
		@Query('code') code: string,
	): Promise<void> {
		this.logger.log('validate called');
		res.clearCookie(`${process.env.JWT_COOKIE_NAME}`);
		if (await this.twoFactorAuthService.isCodeValid(code, req.user)) {
			res.cookie(
				`${process.env.JWT_COOKIE_NAME}`,
				await this.jwt.signAsync({ sub: Object(req.user).id, twoFaStep: false }),
				{ httpOnly: true },
			);
			res.redirect(`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}/home`);
		} else
			res.redirect(
				`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}/ErrorPage`,
			);
	}

	// ACTIONS
	@UseGuards(JwtGuard)
	@Post('generate')
	async generateSecret(@Req() req: Request, @Res() res: Response): Promise<any> {
		this.logger.log('generate called');
		const { otpAuthUrl } = await this.twoFactorAuthService.generateSecret(req.user);
		return await this.twoFactorAuthService.pipeQrCodeStream(res, otpAuthUrl);
	}

	@UseGuards(JwtGuard)
	@Get('turnOn')
	async turnOn(
		@Req() req: Request,
		@Res() res: Response,
		@Query('code') code: string,
	): Promise<void> {
		this.logger.log('turnOn called');
		if (await this.twoFactorAuthService.isCodeValid(code, req.user)) {
			await this.twoFactorAuthService.turnOn(Object(req.user).id);
			res.redirect(`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}/home`);
		} else
			res.redirect(
				`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}/ErrorPage`,
			);
	}

	@UseGuards(JwtGuard)
	@Post('turnOff')
	async turnOff(@Req() req: Request): Promise<boolean> {
		this.logger.log('turnOff called');
		return await this.twoFactorAuthService.turnOff(Object(req.user).id);
	}
}
