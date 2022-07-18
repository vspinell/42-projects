import { HttpException, HttpStatus, Injectable, Logger } from '@nestjs/common';
import fetch from 'node-fetch';
import { PrismaService } from 'src/prisma/prisma.service';
import { JwtService } from '@nestjs/jwt';
import { ReqObj, SingInData, SingUpData, Token } from './dto';
import { Response, Request } from 'express';
import { User } from 'src/user/dto/user.dto';
import { checkPasswords, encodePassword } from 'src/utils/bcrypt';

@Injectable()
export class AuthService {
	private readonly logger = new Logger(AuthService.name);
	constructor(private prisma: PrismaService, private jwt: JwtService) {}

	async login42(
		code: string,
		response: Response,
	): Promise<{
		userId: number;
		twoFaStep: boolean;
		isNewUser: boolean;
	}> {
		this.logger.log('login42 called');
		try {
			const reqObj: ReqObj = {
				grant_type: 'authorization_code',
				client_id: process.env.UID,
				client_secret: process.env.SECRET,
				code,
				redirect_uri: process.env.REDIRECT_URI,
			};
			const tokens: Token = await fetch('https://api.intra.42.fr/oauth/token', {
				method: 'POST',
				headers: {
					'Content-Type': 'application/json',
				},
				body: JSON.stringify(reqObj),
			}).then((resp) => {
				if (!resp.ok) {
					throw new Error('Network response was not OK');
				}
				return resp.json();
			});
			const usrData: User = await fetch('https://api.intra.42.fr/v2/me', {
				method: 'get',
				headers: {
					'Authorization': 'Bearer ' + tokens.access_token,
				},
			})
				.then((res) => {
					if (!res.ok) {
						throw new Error('Network response was not OK');
					}
					return res.json();
				})
				.then((res) => {
					return {
						id: res.id,
						login: res.login,
						image: res.image_url,
						email: res.email,
					};
				});
			let user: any = await this.prisma.user.findUnique({
				where: {
					id: usrData.id,
				},
				include: {
					privateInfo: true,
				},
			});
			let isNewUser = false;
			if (user === null) {
				user = await this.prisma.user.create({
					data: {
						id: usrData.id,
						login: usrData.login,
						image: usrData.image,
						email: usrData.email,
					},
				});
				const statistic = await this.prisma.statistic.create({
					data: {
						userId: usrData.id,
					},
				});
				const privateInfo = await this.prisma.privateInfo.create({
					data: {
						userId: usrData.id,
					},
				});
				await this.prisma.achievementOnStatistic.create({
					data: {
						statisticId: statistic.id,
						achievementId: await this.prisma.achievement
							.findUnique({
								where: {
									name: 'WPP',
								},
							})
							.then((ach) => ach.id),
					},
				});
				isNewUser = true;
			} else if (user.privateInfo.socketIdChat != null) {
				this.logger.log('user already online');
				throw new HttpException('', HttpStatus.CONFLICT);
			}
			await this.signToken(user.id, user.isTwoFactorAuthEnabled).then((ret) => {
				response.cookie(`${process.env.JWT_COOKIE_NAME}`, ret.access_token, {
					httpOnly: true,
				}); //https://expressjs.com/en/api.html#res.cookie
			});
			return {
				userId: user.id,
				twoFaStep: user.isTwoFactorAuthEnabled,
				isNewUser,
			};
		} catch (e) {}
	}

	async signToken(id: number, twoFaStep: boolean): Promise<Token> {
		return {
			access_token: await this.jwt.signAsync({ sub: id, twoFaStep }),
			refresh_token: '',
		};
	}

	/* TO CALL: function signUp() {
		fetch(
		  `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/auth/signUp`,
		  {
			method: "POST",
			headers: {
			  "Content-Type": "application/json",
			},
			body: JSON.stringify({
			  login: "koffing",
			  password: "qwe",
			  email: "koffing@email.it",
			}), // body data type must match "Content-Type" header
		  }
		).then((resp) => {});
	  }
	  */
	async signUp(obj: SingUpData): Promise<boolean> {
		this.logger.log('signUp called');
		if (
			(await this.prisma.user.findFirst({
				where: {
					login: obj.login,
					email: obj.email,
				},
			})) !== null
		)
			return false;
		const user = await this.prisma.user.create({
			data: {
				login: obj.login,
				email: obj.email,
				image:
					'https://www.hotelbooqi.com/wp-content/uploads/2021/12/128-1280406_view-user-icon-png-user-circle-icon-png.png',
			},
		});
		const statistic = await this.prisma.statistic.create({
			data: {
				userId: user.id,
			},
		});
		const privateInfo = await this.prisma.privateInfo.create({
			data: {
				userId: user.id,
				password: await encodePassword(obj.password),
			},
		});
		await this.prisma.achievementOnStatistic.create({
			data: {
				statisticId: statistic.id,
				achievementId: await this.prisma.achievement
					.findUnique({
						where: {
							name: 'WPP',
						},
					})
					.then((ach) => ach.id),
			},
		});
		return true;
	}

	/* TO CALL
	  function signIn() {
		window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/auth/signIn?login=koffing&password=qwe`;
	  }
	  */
	async signIn(
		response: Response,
		obj: SingInData,
	): Promise<boolean | { userId: number; twoFaStep: boolean }> {
		this.logger.log('signIn called');
		const user = await this.prisma.user.findUnique({
			where: {
				login: obj.login,
			},
			include: {
				privateInfo: true,
			},
		});
		if (user === null) return false;
		if (user.privateInfo.socketIdChat != null) {
			this.logger.log('user already online');
			throw new HttpException('', HttpStatus.CONFLICT);
		}
		if (!checkPasswords(obj.password, user.privateInfo.password)) return false;
		await this.signToken(user.id, user.isTwoFactorAuthEnabled).then((ret) => {
			response.cookie(`${process.env.JWT_COOKIE_NAME}`, ret.access_token, {
				httpOnly: true,
			});
		});
		return {
			userId: user.id,
			twoFaStep: user.isTwoFactorAuthEnabled,
		};
	}
}
