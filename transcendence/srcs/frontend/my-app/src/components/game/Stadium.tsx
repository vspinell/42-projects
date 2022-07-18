import * as sprites from "./sprites/images";
import {
  FrameToRender,
  Player,
  PlayerType,
  PowerUpType,
} from "../../types/Game.Interfaces";
import { audio } from "../App";

export const drawRect = (
  ctx: CanvasRenderingContext2D,
  x: number,
  y: number,
  width: number,
  height: number,
  style: string
) => {
  ctx.beginPath();
  ctx.fillStyle = style;
  ctx.fillRect(x, y, width, height);
  ctx.closePath();
};

export const drawPaddles = (
  ctx: CanvasRenderingContext2D,
  frame: FrameToRender,
  playerNum: number,
  style: string
) => {
  const players = frame.players;
  playerNum = playerNum === PlayerType.Spectator ? 0 : playerNum;
  ctx.beginPath();
  ctx.lineWidth = 2;
  ctx.fillStyle = style;
  ctx.fillRect(
    players[0].x,
    players[playerNum].y,
    players[0].width,
    players[playerNum].height
  );
  playerNum = playerNum === 0 ? 1 : 0;
  ctx.fillRect(
    players[1].x,
    players[playerNum].y,
    players[1].width,
    players[playerNum].height
  );
  ctx.closePath();
};

export const drawBall = (
  ctx: CanvasRenderingContext2D,
  status: FrameToRender,
  playerNum: number,
  style: string
) => {
  status.ball.x =
    playerNum === PlayerType.SecondPlayer
      ? status.canvasWidth - status.ball.x
      : status.ball.x;
  ctx.beginPath();
  ctx.fillStyle = style;
  if (status.powerUp !== undefined) {
    ctx.arc(
      status.ball.x,
      status.ball.y,
      status.ball.radius,
      0,
      2 * Math.PI
    );
    ctx.fill();
  } else
    ctx.fillRect(
      status.ball.x - status.ball.radius,
      status.ball.y - status.ball.radius,
      status.ball.radius * 2,
      status.ball.radius * 2
    );
  ctx.closePath();
};

export const drawMargins = (
  ctx: CanvasRenderingContext2D,
  status: FrameToRender,
  style: string
) => {
  const middle = status.canvasHeight / 2;
  ctx.beginPath();
  ctx.lineWidth = 26;
  ctx.strokeStyle = "style";
  ctx.moveTo(0, 0);
  ctx.lineTo(status.canvasWidth, 0);
  ctx.moveTo(0, status.canvasHeight);
  ctx.lineTo(status.canvasWidth, status.canvasHeight);

  ctx.stroke();
  ctx.closePath();
};

const drawHalfCourt = (
  ctx: CanvasRenderingContext2D,
  status: FrameToRender,
  style: string
) => {
  ctx.setLineDash([13, 19]);

  ctx.beginPath();
  ctx.lineWidth = 15;
  ctx.strokeStyle = style;
  ctx.moveTo(status.canvasWidth / 2, 0);
  ctx.lineTo(status.canvasWidth / 2, status.canvasHeight);
  ctx.stroke();
  ctx.setLineDash([]);
  ctx.closePath();
};

const drawScore = (
  ctx: CanvasRenderingContext2D,
  frame: FrameToRender,
  playerNum: number,
  style: string
): void => {
  playerNum = playerNum === PlayerType.Spectator ? 0 : playerNum;
  ctx.beginPath();
  ctx.fillStyle = style;
  ctx.font = "42px gameFont";
  ctx.fillText(
    frame.players[playerNum].score.toString(),
    frame.canvasWidth / 2 - 100,
    80
  );
  playerNum = playerNum === 0 ? 1 : 0;
  ctx.fillText(
    frame.players[playerNum].score.toString(),
    frame.canvasWidth / 2 + 70,
    80
  );
  ctx.closePath();
};

const drawPowerUp = (
  ctx: CanvasRenderingContext2D,
  status: FrameToRender,
  playerNum: number
): void => {
  const powerUp = status.powerUp!;
  const styles = ["green", "yellow", "red"];
  const styles2 = [
    sprites.shorten1,
    sprites.inverted1,
    sprites.largen1,
    sprites.blind1,
  ];
  const image = new Image(powerUp.width, powerUp.height);
  image.src = styles2[powerUp.type - 1];

  powerUp.x =
    playerNum === 1
      ? status.canvasWidth - powerUp.x - powerUp.width
      : powerUp.x;
  ctx.beginPath();
  ctx.drawImage(
    image,
    powerUp.x,
    powerUp.y,
    powerUp.width,
    powerUp.height
  );
  ctx.closePath();
};



export const render = (
  ctx: CanvasRenderingContext2D,
  status: FrameToRender,
  playerNum: number
): void => {
  if (status) {
    if (status.audioTriggered.paddle) audio.bounce.play();
    if (status.audioTriggered.score) audio.score.play();
    const Itemstyle =
      status.powerUp !== undefined ? "black" : "lightgray";
    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
    drawRect(
      ctx,
      0,
      0,
      ctx.canvas.width,
      ctx.canvas.height,
      status.powerUp !== undefined ? "white" : "black"
    );
    if (playerNum === PlayerType.Spectator || !status.players[playerNum].isBlind) {
      drawHalfCourt(
        ctx,
        status,
        status.powerUp !== undefined
          ? `rgb(105,105,105)`
          : "lightgray"
      );
      drawMargins(ctx, status, Itemstyle);
      drawScore(ctx, status, playerNum, Itemstyle);
      drawPaddles(ctx, status, playerNum, Itemstyle);
      drawBall(ctx, status, playerNum, Itemstyle);
      if (
        status.powerUp !== undefined &&
        status.powerUp.type !== PowerUpType.None
      )
        drawPowerUp(ctx, status, playerNum);
    }
  }

};
