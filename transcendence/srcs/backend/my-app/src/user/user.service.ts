import { Injectable, Logger } from '@nestjs/common';
import { ChatGateway } from 'src/chat/chat.gateway';
import { PrismaService } from 'src/prisma/prisma.service';
import { User } from './dto/user.dto';

@Injectable()
export class UserService {
	constructor(private prisma: PrismaService, private chatGateway: ChatGateway) {}
	private readonly logger = new Logger(UserService.name);

	// INFO
	async getUserInfo(data: { url: string }): Promise<User | boolean> {
		this.logger.log('getUserInfo called');
		const user = await this.prisma.user.findFirst({
			where: {
				login: data.url,
			},
		});
		if (user == null) return false;
		return user;
	}

	// ACTIONS
	async setImage(userId: number, file: any): Promise<boolean> {
		if (
			file == undefined ||
			(file.mimetype != 'image/jpeg' &&
				file.mimetype != 'image/jpg' &&
				file.mimetype != 'image/bmp' &&
				file.mimetype != 'image/png') ||
			file.size > 1000000
		)
			return false;
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				image: `data:${file.mimetype};base64,${Buffer.from(file.buffer).toString(
					'base64',
				)}`,
			},
		});
		await this.chatGateway.syncFriends(userId);
		return true;
	}

	async setName(userId: number, name: string): Promise<boolean> {
		if (
			(await this.prisma.user.findFirst({
				where: {
					login: name,
				},
			})) != null
		)
			return false;
		await this.prisma.user.update({
			where: {
				id: userId,
			},
			data: {
				login: name,
			},
		});
		await this.chatGateway.syncFriends(userId);
		return true;
	}
}
