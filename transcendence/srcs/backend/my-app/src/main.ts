import { ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as cookieParser from 'cookie-parser';
import { ExpressAdapter } from '@nestjs/platform-express';
import * as bodyParser from 'body-parser';

async function bootstrap() {
	const app = await NestFactory.create(AppModule);

	const port =
		Number(process.env.FRONTEND_PORT) == 80
			? [
					`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}`,
					`http://${process.env.IP_SERVER}`,
			  ]
			: [`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}`];
	app.enableCors({
		credentials: true,
		origin: port,
	});

	app.setGlobalPrefix('api');
	app.use(cookieParser()); //https://docs.nestjs.com/techniques/cookies#use-with-express-default	//https://www.npmjs.com/package/cookie-parser
	app.useGlobalPipes(
		new ValidationPipe({
			whitelist: true,
		}),
	);
	app.use(bodyParser.json({ limit: '50mb' }));
	app.use(bodyParser.urlencoded({ limit: '50mb', extended: true }));
	await app.listen(Number(process.env.BACKEND_PORT));
}
bootstrap();
