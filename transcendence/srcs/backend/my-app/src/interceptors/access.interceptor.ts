import {
	CallHandler,
	ExecutionContext,
	Injectable,
	Logger,
	NestInterceptor,
} from '@nestjs/common';
import { Request, Response } from 'express';
import { Observable } from 'rxjs';

@Injectable()
export class AccessInterceptor implements NestInterceptor {
	private readonly logger = new Logger(AccessInterceptor.name);

	intercept(
		context: ExecutionContext,
		next: CallHandler<any>,
	): Observable<any> | Promise<Observable<any>> {
		const ctxType = context.getType();
		this.logger.debug('CTX TYPE:', ctxType);
		if (ctxType === 'ws') {
			const ctx = context.switchToWs();
			// this.logger.debug('GET CLIENT:', ctx.getClient());
			// this.logger.debug('GET DATA:', ctx.getData());
		} else if (ctxType === 'http') {
			const ctx = context.switchToHttp();
			const req: Request = ctx.getRequest();
			const resp: Response = ctx.getResponse();
			resp.header(
				'Access-Control-Allow-Origin',
				`http://${process.env.IP_SERVER}:${process.env.FRONTEND_PORT}`,
			);
			// resp.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
			// resp.header('Access-Control-Allow-Headers', 'Content-Type, Accept, API-Key');
			resp.header('Access-Control-Allow-Credentials', 'true');
		}
		return next.handle().pipe();
	}
}
