export enum PowerUpType {
	None,
	Shrink,
	Inverted,
	Largen,
	Blind,
}

export enum GameConstants {
	CANVAS_WIDTH = 1056,
	CANVAS_HEIGHT = 576,
	SCORING_LIMIT = 5,
	paddleHeight = CANVAS_HEIGHT * 0.15,
	MAX_PADDLE_HIGHT = paddleHeight * 1.5,
	MIN_PADDLE_HIGHT = 50,
	SPAWNING_TIME = 3000,
	MAX_BLIND_TIME = 12000,
	MAXBOUNCEANGLE = Math.PI / 4,
}

export interface Time {
	startTime: number;
	lastUpdate: number;
	blindTimer?: number;
}

export interface PowerUp {
	x: number;
	y: number;
	width: number;
	height: number;
	type: number;
	duration: number;
}

export interface Player {
	x: number;
	y: number;
	width: number;
	height: number;
	score: number;
	paddleSpeed: number;
	inverted?: boolean;
	isBlind: boolean;
}

export interface Ball {
	x: number;
	y: number;
	radius: number;
	velocityX: number;
	velocityY: number;
	speed: number;
}

export interface FrameToRender {
	players: [Player, Player];
	ball: Ball;
	canvasHeight: number;
	canvasWidth: number;
	audioTriggered: Audio;
	powerUp?: PowerUp;
}

export interface Room {
	frame: FrameToRender;
	moves: [
		{
			arrowUp: boolean;
			arrowDown: boolean;
		},
		{
			arrowUp: boolean;
			arrowDown: boolean;
		},
	];
	users: [User, User | undefined];
	intervalID: NodeJS.Timer;
	winner: number;
	time: Time;
	powerUpHit?: boolean; //controlla se il powerUp esiste || se é esiste ed stato colpito
	firstSpawn?: boolean;

	// special: boolean;
}

export interface MatchUsers {
	winnerID: number;
	loserID: number;
	losingScore: number;
	special: boolean;
}

export interface User {
	id: number;
	login: string;
	image: string;
	special: boolean;
	friendlyMatch: boolean;
	idFriend?: number;
}

export interface Rooms {
	[roomId: string]: Room;
}

export interface RoomFromClient {
	[socketId: string]: string;
}

export interface Audio {
	paddle: boolean;
	score: boolean;
}
