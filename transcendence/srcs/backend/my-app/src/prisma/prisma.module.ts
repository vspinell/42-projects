import { Global, Module } from '@nestjs/common';
import { PrismaService } from './prisma.service';

@Global() //in this way the prisma module will be available in all the other modules
@Module({
	providers: [PrismaService],
	exports: [PrismaService],
})
export class PrismaModule {}
