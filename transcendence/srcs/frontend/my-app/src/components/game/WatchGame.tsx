import { useContext, useEffect, useRef, useState } from "react";
import WatchContext from "../../context/WatchGame";
import { Socket, io } from "socket.io-client";
import { useNavigate } from "react-router-dom";
import { FrameToRender } from "../../types/Game.Interfaces";
import { render } from "./Stadium";
import { gameUser } from ".";
import Matchmaking from "./Matchmaking";
import { Avatar } from "@mui/material";

export default function WatchGame() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  let canvas: HTMLCanvasElement;
  let ctx: CanvasRenderingContext2D;
  let socket;
  const { watchMode, setWatchMode } = useContext(WatchContext);
  const navigate = useNavigate();
  const [opponentInfo, setOpponentInfo] = useState({
    isSet: false,
    login: "",
    img: "",
  });
  const [watchGameUser, setWatchGameUser] = useState<gameUser>({
    id: 0,
    login: "",
    image: "",
    special: false,
    friendlyMatch: false,
  });

  const handleGameStatus = (frame: FrameToRender) => {
    if (!ctx) return;
    requestAnimationFrame(() => render(ctx, frame, 2));
  };

  const setPlayerNum = (playerInfos: [gameUser, gameUser]) => {
    if (!playerInfos[0] || !playerInfos[1]) return;
    watchMode.idToWatch === playerInfos[0].id
      ? setWatchGameUser({ ...playerInfos[0] })
      : setWatchGameUser({ ...playerInfos[1] });
    watchMode.idToWatch === playerInfos[0].id
      ? setOpponentInfo({
          isSet: true,
          login: playerInfos[1].login,
          img: playerInfos[1].image,
        })
      : setOpponentInfo({
          isSet: true,
          login: playerInfos[0].login,
          img: playerInfos[0].image,
        });
  };
  function handleGameOver() {
    navigate("/home", { replace: true });
  }

  const initSocket = () => {
    socket = io(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/game`,
      {
        forceNew: true,
      }
    );
    socket.emit("watchGame", watchMode.idToWatch);
    socket.on("updateGame", handleGameStatus);
    socket.on("playerNum", setPlayerNum);
    socket.on("gameOver", handleGameOver);
  };

  useEffect(() => {
    canvas = canvasRef.current!;
    ctx = canvas.getContext("2d")!;
    canvas.width = 1056;
    canvas.height = 576;
    initSocket();
    return () => {
      socket.removeListener("updateGame", handleGameStatus);
      socket.removeListener("playerNum", setPlayerNum);
      socket.removeListener("gameOver", handleGameOver);
      if (socket) socket.close();
      setWatchMode({
        mode: false,
        idToWatch: "",
      });
    };
  }, []);

  function backHome() {
    navigate("/home");
  }

  return (
    <div className="game--canvas--watch">
      {!opponentInfo.isSet ? (
        <Matchmaking changeMode={backHome} />
      ) : (
        <div className="player--infos--wrapper">
          <div className="player--info">
            <Avatar
              src={watchGameUser.image}
              alt="Player1"
            />
            <h3 className="user--login">{watchGameUser.login}</h3>
          </div>
          {opponentInfo.isSet && (
            <div className="player--info">
              <h3 className="user--login">{opponentInfo.login}</h3>
              <Avatar
                src={opponentInfo.img}
                alt="Player2"
              />
            </div>
          )}
        </div>
      )}
      <canvas ref={canvasRef} />
    </div>
  );
}
