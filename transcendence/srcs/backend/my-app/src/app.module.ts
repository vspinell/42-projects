import { Module } from '@nestjs/common';
import { AuthModule } from './auth/auth.module';
import { PrismaModule } from './prisma/prisma.module';
import { ConfigModule } from '@nestjs/config';
import { UserModule } from './user/user.module';
import { ChatModule } from './chat/chat.module';
import { FakeUsersModule } from './fakeusers/fakeusers.module';
import { FriendsModule } from './friends/friends.module';
import { ChatGateway } from './chat/chat.gateway';
import { ChannelsModule } from './channels/channels.module';
import { StatisticsModule } from './statistics/statistics.module';
import { GameModule } from './game/game.module';
import { TwoFactorAuthModule } from './two-factor-auth/two-factor-auth.module';
import { ColorsModule } from './utils/utils.module';

@Module({
	imports: [
		ChatModule,
		AuthModule,
		UserModule,
		PrismaModule,
		ConfigModule.forRoot({ isGlobal: true }),
		FakeUsersModule,
		FriendsModule,
		ChannelsModule,
		StatisticsModule,
		GameModule,
		TwoFactorAuthModule,
		ColorsModule,
	],
})
export class AppModule {}
