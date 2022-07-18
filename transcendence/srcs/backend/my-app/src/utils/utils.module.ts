import { Module } from '@nestjs/common';
import { ColorsService } from './colors.service';

@Module({
	providers: [ColorsService],
	controllers: [],
	imports: [],
})
export class ColorsModule {}
