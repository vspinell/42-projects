import {
	ArgumentsHost,
	Catch,
	ExceptionFilter,
	HttpException,
	HttpStatus,
	Logger,
} from '@nestjs/common';
import { Request, response, Response } from 'express';
import { resolve } from 'path';

@Catch(HttpException)
export class HttpExceptionFilter implements ExceptionFilter {
	private readonly logger = new Logger(HttpExceptionFilter.name);
	catch(exception: HttpException, host: ArgumentsHost) {
		this.logger.log('Not authorized');
		const ctx = host.switchToHttp();
		const response = ctx.getResponse<Response>();
		const request = ctx.getRequest<Request>();

		const status =
			exception instanceof HttpException
				? exception.getStatus()
				: HttpStatus.INTERNAL_SERVER_ERROR;

		const message =
			exception instanceof HttpException
				? exception.getResponse()
				: 'Internal server error';

		response.status(200);
		response.json(false);

		// response.status(200).json({
		// 	statusCode: status,
		// 	timestamp: new Date().toISOString(),
		// 	path: request.url,
		// 	kind: 'exception',
		// 	message,
		// });
	}
}
