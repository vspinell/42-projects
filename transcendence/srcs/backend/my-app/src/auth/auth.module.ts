import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthController } from './auth.controller';
import { JwtModule } from '@nestjs/jwt';
import { JwtStrategy } from './strategy';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { UserService } from 'src/user/user.service';

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
	providers: [AuthService, JwtStrategy, UserService], //, ChatGateway],
	controllers: [AuthController],
})
export class AuthModule {}
