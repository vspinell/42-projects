import { Injectable } from '@nestjs/common';
import {
	FrameToRender,
	Player,
	PowerUp,
	PowerUpType,
	Room,
	Rooms,
} from './interfaces/game.interfaces';

const CANVAS_WIDTH = 1056;
const CANVAS_HEIGHT = 576;
export const SCORING_LIMIT = 5;
const paddleHeight = CANVAS_HEIGHT * 0.15;
const MAX_PADDLE_HIGHT = paddleHeight * 1.5;
const MIN_PADDLE_HIGHT = 50;
const SPAWNING_TIME = 3000;
const MAX_BLIND_TIME = 11000;

const MAXBOUNCEANGLE = Math.PI / 4;

@Injectable()
export class GameService {
	initGame(special: boolean): FrameToRender {
		const ret: FrameToRender = {
			players: [
				{
					x: CANVAS_WIDTH / 20,
					y: (CANVAS_HEIGHT - paddleHeight) / 2,
					width: 15,
					height: paddleHeight,
					score: 0,
					paddleSpeed: 8,
					isBlind: false,
				},
				{
					x: CANVAS_WIDTH - CANVAS_WIDTH / 20 - 15,
					y: (CANVAS_HEIGHT - paddleHeight) / 2,
					width: 15,
					height: paddleHeight,
					score: 0,
					paddleSpeed: 8,
					isBlind: false,
				},
			],
			ball: {
				x: CANVAS_WIDTH / 2,
				y: CANVAS_HEIGHT / 2,
				radius: paddleHeight * 0.1,
				velocityX: 7,
				velocityY: 7,
				speed: 10,
			},
			audioTriggered: {
				paddle: false,
				score: false,
			},
			canvasWidth: CANVAS_WIDTH,
			canvasHeight: CANVAS_HEIGHT,
		};
		if (special) {
			ret.players[1].inverted = false;
			ret.powerUp = {
				x: 0,
				y: 0,
				width: 0,
				height: 0,
				type: PowerUpType.None,
				duration: 0,
			};
		}
		return ret;
	}

	updatePaddles(update: Room): FrameToRender {
		const players = update.frame.players;
		const frame = update.frame;
		const moves = update.moves;
		let buff: boolean;
		if (moves[0].arrowUp == true && moves[0].arrowDown == false) {
			if (players[0].y - players[0].paddleSpeed >= 13)
				players[0].y -= players[0].paddleSpeed;
			else players[0].y = 14;
		} else if (moves[0].arrowDown == true && moves[0].arrowUp == false) {
			if (
				players[0].y + players[0].height + players[0].paddleSpeed <=
				frame.canvasHeight - 13
			)
				players[0].y += players[0].paddleSpeed;
			else players[0].y = frame.canvasHeight - 14 - players[0].height;
		}
		if (moves[1].arrowUp == true && moves[1].arrowDown == false) {
			if (players[1].y - players[1].paddleSpeed >= 13)
				players[1].y -= players[1].paddleSpeed;
			else players[1].y = 14;
		} else if (moves[1].arrowDown == true && moves[1].arrowUp == false) {
			if (
				players[1].y + players[1].height + players[1].paddleSpeed <=
				frame.canvasHeight - 13
			)
				players[1].y += players[1].paddleSpeed;
			else players[1].y = frame.canvasHeight - 14 - players[1].height;
		}
		return frame;
	}

	detectCollision(object: Player | PowerUp, ball: FrameToRender['ball']): boolean {
		const ballLeft = ball.x - ball.radius;
		const ballRight = ball.x + ball.radius;
		const ballBottom = ball.y + ball.radius;
		const ballTop = ball.y - ball.radius;

		const objectTop = object.y;
		const objectBottom = object.y + object.height;
		const objectLeft = object.x;
		const objectRight = object.x + object.width;

		return (
			ballRight >= objectLeft &&
			ballLeft <= objectRight &&
			ballBottom >= objectTop &&
			ballTop <= objectBottom
		);
	}

	handleCollision(frame: FrameToRender) {
		const ball = frame.ball;
		const player = frame.players[ball.x < frame.canvasWidth / 2 ? 0 : 1];

		const ballTop = ball.y - ball.radius;
		const ballBottom = ball.y + ball.radius;
		const border = 14;
		if (ballBottom >= frame.canvasHeight - border) {
			ball.y = frame.canvasHeight - border - ball.radius;
			ball.velocityY = -ball.velocityY;
		} else if (ballTop <= border) {
			ball.y = border + ball.radius;
			ball.velocityY = -ball.velocityY;
		}

		if (this.detectCollision(player, frame.ball)) {
			frame.audioTriggered.paddle = true;
			//delta generato dalla sottrazione fra centro del paddle e punto di collisione (centro della palla)
			//sarà positivo se il punto di collisione è prima del centro e negativo viceversa
			const intersectionPoint = player.y + player.height / 2 - ball.y;
			// range -1 a 1
			const nomalizedPoint = intersectionPoint / (player.height / 2);
			//MAXBOUNCEANGLE === angolo massimmo  in radianti
			//bounceAngle === angolo che è una porzione dell'angolo massimo
			const bounceAngle = nomalizedPoint * MAXBOUNCEANGLE;
			//se ti trovi nella parte dx == -1
			const direction = ball.x < frame.canvasWidth / 2 ? 1 : -1;
			ball.velocityX = direction * ball.speed * Math.cos(bounceAngle);
			//-sin perchè vogliamo la collisione produca un rimbalzo opposto. Ricorda che il piano cartesiano qui è capovolto per le y.
			//Quindi parte superiore paddle == delta > 0 => -y;  parte inferiore paddle == delta < 0 => +y
			ball.velocityY = ball.speed * -Math.sin(bounceAngle);
			if (ball.speed < 20) ball.speed++;
		}
	}

	resetBall(frame: FrameToRender) {
		const ball = frame.ball;

		ball.x = CANVAS_WIDTH / 2;
		ball.y = CANVAS_HEIGHT / 2;

		ball.velocityX = ball.velocityX > 0 ? -7 : 7;
		ball.velocityY = 7;
		ball.speed = 10;
	}

	randomSpawn(update: Room) {
		const powerUp = update.frame.powerUp;
		powerUp.width = 60;
		powerUp.height = 60;
		powerUp.type = 0;

		const spawningArea = {
			MinX: CANVAS_WIDTH / 2 - CANVAS_WIDTH / 4,
			MaxX: CANVAS_WIDTH / 2 + CANVAS_WIDTH / 4,
			MinY: 14,
			MaxY: CANVAS_HEIGHT - 14 - powerUp.height,
		};

		powerUp.x = Math.floor(
			Math.random() * (spawningArea.MaxX - spawningArea.MinX) + spawningArea.MinX,
		);
		powerUp.y = Math.floor(
			Math.random() * (spawningArea.MaxY - spawningArea.MinY) + spawningArea.MinY,
		);

		powerUp.type = Math.floor(Math.random() * 4 + 1);
	}

	resetEffects(update: Room) {
		update.powerUpHit = false;
		update.frame.powerUp.duration = 0;
		const players = update.frame.players;
		if (
			players[0].height < paddleHeight &&
			players[0].y + paddleHeight > update.frame.canvasHeight - 14
		)
			players[0].y = update.frame.canvasHeight - 14 - paddleHeight;
		players[0].height = paddleHeight;
		players[0].inverted = false;
		if (
			players[1].height < paddleHeight &&
			players[1].y + paddleHeight > update.frame.canvasHeight - 14
		)
			players[1].y = update.frame.canvasHeight - 14 - paddleHeight;
		players[1].height = paddleHeight;
		players[1].inverted = false;
	}

	handleEffects(hittingPlayer: number, update: Room) {
		const frame = update.frame;
		const opponent = hittingPlayer === 0 ? 1 : 0;
		let paddleIncrementY: number;
		let paddleIncrementHeight: number;
		switch (frame.powerUp.type) {
			case PowerUpType.Shrink:
				frame.players[opponent].y +=
					frame.players[opponent].height <= MIN_PADDLE_HIGHT ? 0 : paddleHeight * 0.2;
				frame.players[opponent].height -=
					frame.players[opponent].height <= MIN_PADDLE_HIGHT ? 0 : paddleHeight * 0.4;
				break;
			case PowerUpType.Inverted:
				update.frame.players[hittingPlayer].inverted = true;
				break;
			case PowerUpType.Largen:
				if (
					frame.players[hittingPlayer].y ===
					frame.canvasHeight - 14 - frame.players[hittingPlayer].height
				) {
					paddleIncrementY = paddleHeight / 2;
					paddleIncrementHeight = paddleHeight / 2;
				} else if (frame.players[hittingPlayer].y === 14) {
					paddleIncrementY = 0;
					paddleIncrementHeight = paddleHeight / 2;
				} else {
					paddleIncrementY = paddleHeight / 4;
					paddleIncrementHeight = paddleHeight / 2;
				}
				frame.players[hittingPlayer].y -=
					frame.players[hittingPlayer].height >= MAX_PADDLE_HIGHT ? 0 : paddleIncrementY;
				frame.players[hittingPlayer].height +=
					frame.players[hittingPlayer].height >= MAX_PADDLE_HIGHT
						? 0
						: paddleIncrementHeight;
				break;
			case PowerUpType.Blind:
				update.time.blindTimer = Date.now();
				frame.players[hittingPlayer].isBlind = true;
				frame.powerUp.duration = MAX_BLIND_TIME / frame.ball.speed;
				break;
		}
	}

	handlePowerUpCollision(update: Room) {
		const ball = update.frame.ball;
		const hittingPlayer = ball.velocityX > 0 ? 0 : 1;
		if (this.detectCollision(update.frame.powerUp, ball)) {
			this.handleEffects(hittingPlayer, update);

			update.powerUpHit = true;
			update.frame.powerUp.type = PowerUpType.None;
		}
	}

	gameLoopSpecial(update: Room): FrameToRender {
		const ball = update.frame.ball;
		const playerNum = ball.x < update.frame.canvasWidth / 2 ? 1 : 0;
		const scoringPlayer = update.frame.players[playerNum];
		update.frame.audioTriggered = {
			paddle: false,
			score: false,
		};
		const currentTime = Date.now();
		if (currentTime - update.time.lastUpdate >= 10000) {
			//tempo di spawning
			update.time.lastUpdate = currentTime;
			update.powerUpHit = false;
		} else if (currentTime - update.time.lastUpdate >= 7000 && !update.powerUpHit) {
			//tempo entro quando farli sparire
			update.powerUpHit = true;
			update.frame.powerUp.type = PowerUpType.None;
		}

		if (
			update.time.blindTimer &&
			currentTime - update.time.blindTimer >= update.frame.powerUp.duration
		) {
			update.frame.players[0].isBlind = false;
			update.frame.players[1].isBlind = false;
		}

		if (
			!update.powerUpHit &&
			(update.time.lastUpdate === currentTime ||
				(currentTime - update.time.startTime >= SPAWNING_TIME && update.firstSpawn))
		) {
			if (update.firstSpawn) update.firstSpawn = false;
			this.randomSpawn(update);
		}

		if (!update.powerUpHit) this.handlePowerUpCollision(update);

		this.updatePaddles(update);
		this.handleCollision(update.frame);

		if (ball.x - ball.radius < 0 || ball.x + ball.radius > update.frame.canvasWidth) {
			++scoringPlayer.score;
			if (scoringPlayer.score === SCORING_LIMIT) update.winner = playerNum;
			this.resetBall(update.frame);
			this.resetEffects(update);
		}

		ball.x += ball.velocityX;
		ball.y += ball.velocityY;

		return update.frame;
	}

	gameLoop(update: Room): FrameToRender {
		const ball = update.frame.ball;
		const playerNum = ball.x < update.frame.canvasWidth / 2 ? 1 : 0;
		const scoringPlayer = update.frame.players[playerNum];
		update.frame.audioTriggered = {
			paddle: false,
			score: false,
		};
		this.updatePaddles(update);

		this.handleCollision(update.frame);
		if (ball.x - ball.radius < 0 || ball.x + ball.radius > update.frame.canvasWidth) {
			++scoringPlayer.score;
			update.frame.audioTriggered.score = true;
			if (scoringPlayer.score === SCORING_LIMIT) update.winner = playerNum;
			this.resetBall(update.frame);
		}

		ball.x += ball.velocityX;
		ball.y += ball.velocityY;

		return update.frame;
	}
}
