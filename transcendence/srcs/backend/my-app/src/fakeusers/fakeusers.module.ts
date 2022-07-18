import { Module } from '@nestjs/common';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { JwtModule } from '@nestjs/jwt';
import { JwtStrategy } from 'src/auth/strategy';
import { FakeUsersController } from './fakeusers.controller';
import { FakeUsersService } from './fakeusers.service';

@Module({
	controllers: [FakeUsersController],
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
	providers: [JwtStrategy, FakeUsersService],
})
export class FakeUsersModule {}
