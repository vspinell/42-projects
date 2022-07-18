import {
	ArgumentsHost,
	Catch,
	ExceptionFilter,
	HttpException,
	Logger,
} from '@nestjs/common';
import { Request, response, Response } from 'express';

@Catch(HttpException)
export class HttpWsExceptionFilter implements ExceptionFilter {
	private readonly logger = new Logger(HttpWsExceptionFilter.name);
	catch(exception: HttpException, host: ArgumentsHost) {
		this.logger.error('HttpWsExceptionFilter called');
		const ctx = host.switchToHttp();
		const res = ctx.getResponse<Response>();
		const req = ctx.getRequest<Request>();
		const status = exception.getStatus();

		// res.status(200);
	}
}
