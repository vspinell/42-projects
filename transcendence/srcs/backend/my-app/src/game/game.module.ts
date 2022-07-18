import { Module } from '@nestjs/common';
import { GameGateway } from './game.gateway';
import { GameService } from './game.service';
import { MatchService } from './match.service';

@Module({ providers: [GameGateway, GameService, MatchService] })
export class GameModule {}
