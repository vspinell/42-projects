export enum PlayerType {
  FirstPlayer,
  SecondPlayer,
  Spectator,
}

export enum PowerUpType {
  None,
  Shrink,
  Inverted,
  Largen,
}

export interface PowerUp {
  x: number;
  y: number;
  width: number;
  height: number;
  type: number;
}
export interface Player {
  x: number;
  y: number;
  width: number;
  height: number;
  score: number;
  paddleSpeed: number;
  isBlind: boolean;
}

export interface FrameToRender {
  players: [Player, Player];
  ball: Ball;
  // speed: number;
  canvasHeight: number;
  canvasWidth: number;
  audioTriggered: Audio;
  powerUp?: PowerUp;
}

export interface Ball {
  x: number;
  y: number;
  radius: number;
  velocityX: number;
  velocityY: number;
  speed: number;
}
export interface Audio {
	paddle: boolean;
	score: boolean;
}

// export interface Ball extends Player {}
