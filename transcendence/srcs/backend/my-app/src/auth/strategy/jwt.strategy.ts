import { Injectable, Logger } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PassportStrategy } from '@nestjs/passport';
import { Request, request } from 'express';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { PrismaService } from 'src/prisma/prisma.service';
import { User } from 'src/user/dto/user.dto';

export const cookieExtractor = (req: Request) => {
	//https://github.com/mikenicholson/passport-jwt#extracting-the-jwt-from-the-request
	const logger = new Logger(cookieExtractor.name);
	logger.log('cookieExtractor called');
	let token = null;
	if (req && req.cookies) {
		//https://expressjs.com/en/api.html#req.cookies
		token = req.cookies[process.env.JWT_COOKIE_NAME];
	}
	return token;
};

@Injectable()
export class JwtStrategy extends PassportStrategy(
	//https://docs.nestjs.com/security/authentication#implementing-passport-jwt
	Strategy, //https://github.com/mikenicholson/passport-jwt
	// 'jwt',
) {
	private readonly logger = new Logger(JwtStrategy.name);
	constructor(config: ConfigService, private prisma: PrismaService) {
		super({
			//https://github.com/mikenicholson/passport-jwt#configure-strategy
			jwtFromRequest: ExtractJwt.fromExtractors([
				cookieExtractor,
				// (request : Request) => {  ///FUNZIONA
				//     return request?.cookies?.trascendence
				// }

				// ExtractJwt.fromAuthHeaderAsBearerToken(),
			]),
			secretOrKey: config.get('JWT_SECRET'),
		});
	}

	async validate(payload: { sub: number }): Promise<User> {
		const user = await this.prisma.user.findUnique({
			where: {
				id: payload.sub,
			},
		});
		return user;
	}
}
