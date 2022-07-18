import {
	Body,
	Controller,
	Get,
	Logger,
	Post,
	Req,
	Res,
	UseFilters,
	UseGuards,
} from '@nestjs/common';
import { Request, Response } from 'express';
import { JwtGuard } from 'src/auth/guard';
import { HttpExceptionFilter } from 'src/filters/http-exception.filter';
import { User } from 'src/user/dto/user.dto';
import { StatisticsService } from './statistics.service';

@UseFilters(HttpExceptionFilter)
@UseGuards(JwtGuard)
@Controller('statistics')
export class StatisticsController {
	private readonly logger = new Logger(StatisticsController.name);
	constructor(private statisticsService: StatisticsService) {}

	@Post()
	async userStatistics(@Body() data: { userId: number }) {
		this.logger.log('userStatistics called');
		return await this.statisticsService.statistics(data.userId);
	}
}
