import { Module } from '@nestjs/common';
import { TwoFactorAuthService } from './two-factor-auth.service';
import { TwoFactorAuthController } from './two-factor-auth.controller';
import { UserService } from 'src/user/user.service';
import { JwtModule, JwtService } from '@nestjs/jwt';
import { ConfigModule, ConfigService } from '@nestjs/config';

@Module({
	imports: [
		JwtModule.registerAsync({
			//https://stackoverflow.com/questions/54308318/how-to-get-the-configurations-from-within-a-module-import-in-nestjs
			imports: [ConfigModule], //https://github.com/nestjs/jwt/blob/master/README.md
			useFactory: async (configService: ConfigService) => ({
				secret: configService.get('JWT_SECRET'),
				signOptions: {
					expiresIn: configService.get('JWT_EXPIRATION_TIME'),
				},
			}),
			inject: [ConfigService],
		}),
	],
	providers: [TwoFactorAuthService, UserService],
	controllers: [TwoFactorAuthController],
})
export class TwoFactorAuthModule {}
