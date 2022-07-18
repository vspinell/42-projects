import { Module } from '@nestjs/common';
import { UserService } from './user.service';
import { UserController } from './user.controller';
import { PrismaModule } from 'src/prisma/prisma.module';
import { JwtModule, JwtService } from '@nestjs/jwt';
import { ConfigModule, ConfigService } from '@nestjs/config';

@Module({
	providers: [UserService],
	controllers: [UserController],
	imports: [
		PrismaModule,
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
})
export class UserModule {}
