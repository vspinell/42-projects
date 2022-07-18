import { Injectable } from '@nestjs/common';
import { Controller, Get, Logger, Res } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { Request, Response } from 'express';
import { PrismaService } from 'src/prisma/prisma.service';
import { User } from 'src/user/dto/user.dto';

export const fakeUsers: {
	id: number;
	login: string;
	image: string;
	email: string;
	logged: boolean;
}[] = [
	{
		id: 1000,
		login: 'tom',
		image:
			'https://mystickermania.com/cdn/stickers/tom-and-jerry/tom-is-small-and-in-love-512x512.png',
		email: 'tom@tomandjerry.com',
		logged: false,
	},
	{
		id: 2000,
		login: 'jerry',
		image: 'https://upload.wikimedia.org/wikipedia/en/2/2f/Jerry_Mouse.png',
		email: 'jerry@tomandjerry.com',
		logged: false,
	},
	{
		id: 3000,
		login: 'pikachu',
		image: 'https://assets.puzzlefactory.com/puzzle/254/191/original.webp',
		email: 'info@pikachu.com',
		logged: false,
	},
	{
		id: 4000,
		login: 'squirtle',
		image: 'https://cdn.goodvinilos.com/4613-large_default/pokemon-squirtle.jpg',
		email: 'squirtle@pokemon.com',
		logged: false,
	},
];

@Injectable()
export class FakeUsersService {
	private readonly logger = new Logger(FakeUsersService.name);
	constructor(private prisma: PrismaService, private jwt: JwtService) {
		// this.init();
	}

	public async init() {
		for (let user in fakeUsers) {
			try {
				await this.prisma.user.create({
					data: {
						id: fakeUsers[user].id,
						login: fakeUsers[user].login,
						image: fakeUsers[user].image,
						email: fakeUsers[user].email,
					},
				});
				const privateInfo = await this.prisma.privateInfo.create({
					data: {
						userId: fakeUsers[user].id,
					},
				});
				const statistics = await this.prisma.statistic.create({
					data: {
						wins: 0,
						losses: 0,
						ladderLevel: 0,
						userId: fakeUsers[user].id,
					},
				});
				await this.prisma.achievementOnStatistic.create({
					data: {
						statisticId: statistics.id,
						achievementId: await this.prisma.achievement
							.findUnique({
								where: {
									name: 'WPP',
								},
							})
							.then((ach) => ach.id),
					},
				});
			} catch (e) {}
		}
	}

	async createFakeUser(req: Request) {
		this.logger.log('createFakeUser called');
		for (let user of fakeUsers) {
			const userSocketId = await this.prisma.user
				.findUnique({
					where: {
						id: user.id,
					},
					select: {
						privateInfo: true,
					},
				})
				.then((user) => user.privateInfo.socketIdChat);
			if (!userSocketId) {
				const jwtToken = await this.jwt.signAsync({ sub: user.id });
				req.res.cookie(`${process.env.JWT_COOKIE_NAME}`, jwtToken, { httpOnly: true }); //https://expressjs.com/en/api.html#res.cookie
				return true;
			}
		}
		return false;
	}
}
