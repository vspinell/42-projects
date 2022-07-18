import { Injectable, Logger } from '@nestjs/common';
import { PrismaService } from 'src/prisma/prisma.service';

@Injectable()
export class ColorsService {
	private readonly logger = new Logger(ColorsService.name);
	constructor(private prisma: PrismaService) {
		this.init();
	}

	private async init() {
		await this.prisma.color
			.createMany({
				data: [
					{ code: '#035397', name: 'blue' },
					{ code: '#F94C66', name: 'red' },
					{ code: '#541690', name: 'violet' },
					{ code: '#E8630A', name: 'orange' },
					{ code: '#3EC70B', name: 'green' },
				],
			})
			.catch(() => {});
	}
}
