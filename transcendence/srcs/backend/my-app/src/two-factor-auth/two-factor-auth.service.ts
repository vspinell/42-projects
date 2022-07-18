import { Injectable, Logger } from '@nestjs/common';
import { Request, Response } from 'express';
import { authenticator } from 'otplib';
import { toFileStream } from 'qrcode';
import { PrismaService } from 'src/prisma/prisma.service';
import { User } from 'src/user/dto/user.dto';

@Injectable()
export class TwoFactorAuthService {
	constructor(private prisma: PrismaService) {}
	private readonly logger = new Logger(TwoFactorAuthService.name);

	// INFO
	async isCodeValid(twoFactorAuthCode: string, user: User): Promise<boolean> {
		this.logger.log('isCodeValid called');
		const privateInfo = await this.prisma.privateInfo.findFirst({
			where: {
				userId: user.id,
			},
		});
		return authenticator.verify({
			token: twoFactorAuthCode,
			secret: privateInfo.twoFactorAuthSecret,
		});
	}

	// ACTIONS
	async generateSecret(user: User): Promise<{ secret: string; otpAuthUrl: string }> {
		this.logger.log('generate called');
		const secret = authenticator.generateSecret();
		const otpAuthUrl = authenticator.keyuri(user.email, 'transcendenceWebApp', secret);
		await this.prisma.privateInfo.update({
			where: {
				userId: user.id,
			},
			data: {
				twoFactorAuthSecret: secret,
				twoFactorAuthUrl: otpAuthUrl,
			},
		});
		return { secret, otpAuthUrl };
	}

	async pipeQrCodeStream(stream: Response, otpauthUrl: string): Promise<any> {
		return toFileStream(stream, otpauthUrl);
	}

	async turnOn(userId: number): Promise<boolean> {
		this.logger.log('turnOn called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				isTwoFactorAuthEnabled: true,
			},
		});
		return true;
	}

	async turnOff(userId: number): Promise<boolean> {
		this.logger.log('turnOff called');
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				isTwoFactorAuthEnabled: false,
			},
		});
		await this.prisma.privateInfo.update({
			where: {
				userId,
			},
			data: {
				twoFactorAuthSecret: null,
				twoFactorAuthUrl: null,
			},
		});
		return true;
	}

	async getQrcode(userId: number) {
		return await this.prisma.privateInfo
			.findFirst({
				where: {
					userId,
				},
			})
			.then((pInfo) => pInfo.twoFactorAuthUrl);
	}
}
