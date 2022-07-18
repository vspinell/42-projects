import { useContext, useEffect, useRef, useState } from "react";
import "../../style/Game.css";
import { render } from "./Stadium";
import { Socket, io } from "socket.io-client";
import { FrameToRender } from "../../types/Game.Interfaces";
import { User_me_type } from "../../types/type";
import Matchmaking from "./Matchmaking";
import GameInviteContext from "../../context/GameInvite";
import GameOverButtons from "./GameOverButtons";
import { audio } from "../App";

import GameMode from "./GameMode";
import { Avatar } from "@mui/material";

export interface gameUser {
  id: number;
  login: string;
  image: string;
  special: boolean;
  friendlyMatch: boolean;
  idFriend?: number;
}
const CANVAS_WIDTH = 1056;
const CANVAS_HEIGHT = 576;
const CLASSIC_MODE = "classic";
const SPECIAL_MODE = "special";

export default function Game() {
  let socket: Socket;
  let canvas: HTMLCanvasElement;
  let ctx: CanvasRenderingContext2D;
  let errorOccurred = false;
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [User, setUser] = useState<any>();
  const [isEnded, setisEnded] = useState({
    state: false,
    message: "",
  });
  const { gameInvite, setGameInvite } = useContext(GameInviteContext);
  const [isStarted, setIsStarted] = useState(false);
  const [sockett, setSockett] = useState<Socket | undefined>();
  let dto: gameUser = {
    id: 0,
    login: "",
    image: "",
    special: false,
    friendlyMatch: false,
  };
  const [modeIsSet, setModeIsSet] = useState(false);
  const [opponentInfo, setOpponentInfo] = useState({
    isSet: false,
    login: "",
    img: "",
  });
  let playerNum: number;
  let started = false;

  function idFriendOpponent(userID) {
    if (gameInvite.accepted === true) {
      if (userID === gameInvite.idSender) return gameInvite.idRecever;
      return gameInvite.idSender;
    }
    return undefined;
  }

  useEffect(() => {
    async function getUser() {
      try {
        const res = await fetch(
          `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/users/me`,
          {
            credentials: "include",
          }
        );
        const data: User_me_type = await res.json();
        setUser({
          id: data.id,
          login: data.login,
          image: data.image,
          special: false,
        });
      } catch (error) {
        errorOccurred = true;
      }
    }
    getUser();
  }, []);


  const initSocket = () => {
    socket = io(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/game`,
      {
        forceNew: true,
      }
    );
    dto = {
      ...User,
      special:
        (gameInvite.accepted && gameInvite.gameMode === "special") ||
        User?.special
          ? true
          : false,
      friendlyMatch: gameInvite.accepted === true ? true : false,
      idFriend: idFriendOpponent(User?.id),
    };
    socket.emit("joinGame", dto);
    socket.on("updateGame", handleGameStatus);
    socket.on("playerNum", setPlayerNum);
    socket.on("gameOver", handleGameOver);
    setSockett(socket);
  };

  useEffect(() => {
    if (gameInvite.accepted) {
      setisEnded({
        state: false,
        message: "",
      });
      setModeIsSet((prev) => true);
    }
  }, [gameInvite]);

  useEffect(() => {
    if (modeIsSet && !isEnded.state) {
      canvas = canvasRef.current!;
      ctx = canvas.getContext("2d")!;
      canvas.width = CANVAS_WIDTH;
      canvas.height = CANVAS_HEIGHT;
      if (User && !errorOccurred) {
        initSocket();
        document.addEventListener("keyup", keyRelease);
        document.addEventListener("keydown", keyPress);

        return () => {
          document.removeEventListener("keyup", keyRelease);
          document.removeEventListener("keydown", keyPress);
          socket.removeListener("updateGame", handleGameStatus);
          socket.removeListener("playerNum", setPlayerNum);
          socket.removeListener("gameOver", handleGameOver);
          if (socket) {
            socket.close();
            setGameInvite((prevState) => {
              return {
                idSender: "",
                idRecever: "",
                gameMode: "classic",
                accepted: false,
              };
            });
            if (dto.special) {
              audio.gameSong.off("stop");
              audio.gameSong.stop();
            }
            audio.bounce.stop();
            audio.score.stop();
            dto = {
              id: 0,
              login: "",
              image: "",
              special: false,
              friendlyMatch: false,
            };
          }
        };
      }
    }
  }, [User, modeIsSet]);

  const handleGameStatus = (frame: FrameToRender) => {
    if (!ctx) return;
    if (!started) {
      started = true;
      audio.gameSong.on("stop", function () {
        audio.gameOver.play();
      });
      if (dto.special) {
        audio.gameSong.play();
      }
    }
    requestAnimationFrame(() => render(ctx, frame, playerNum));
  };

  const handleGameOver = (winner: number) => {
    started = false;
    setModeIsSet((prev) => false);
    socket.close();
    setGameInvite((prevState) => {
      return {
        idSender: "",
        idRecever: "",
        gameMode: "classic",
        accepted: false,
      };
    });
    if (dto.special) {
      audio.gameSong.stop();
      audio.gameSong.off("stop");
    }
    audio.bounce.stop();
    audio.score.stop();
   
    setisEnded((prevState) => {
      return {
        state: true,
        message: playerNum === winner ? "YOU WON" : "YOU LOST",
      };
    });

  };
  const setPlayerNum = (playerInfos: number | [gameUser, gameUser]) => {
    if (typeof playerInfos === "number") playerNum = playerInfos;
    else {
      User?.id === playerInfos[0].id
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
    }
  };

  const keyPress = (e: KeyboardEvent) => {
    if (e.key === "ArrowUp" || e.key === "ArrowDown")
      socket.emit("keyPress", e.key);
  };

  const keyRelease = (e: KeyboardEvent) => {
    if (e.key === "ArrowUp" || e.key === "ArrowDown")
      socket.emit("keyRelease", e.key);
  };

  function handleSelectedMode(selectedMode: "classic" | "special") {
    if (selectedMode === SPECIAL_MODE) {
      setUser((prevUser: gameUser | undefined): gameUser | undefined => {
        if (!prevUser) return;
        return {
          ...prevUser,
          special: true,
        };
      });
    }
    setModeIsSet(true);
  }

  function changeMode() {
    setModeIsSet((prev) => false);
  }

  return (
    <div className="game--body">
      {!isEnded.state ? (
        modeIsSet || gameInvite.accepted ? (
          <div className="game--canvas">
            {!opponentInfo.isSet
              ? User && <Matchmaking changeMode={changeMode} />
              : !isEnded.state && (
                  <div className="player--infos--wrapper">
                    <div className="player--info">
                      <Avatar
                        src={User?.image}
                        alt="Player1"
                      />
                      <h3 className="user--login">{User?.login}</h3>
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
            {!isEnded.state && <canvas ref={canvasRef} />}
          </div>
        ) : (
          <GameMode handleSelectedMode={handleSelectedMode} />
        )
      ) : (
        <GameOverButtons socketId={sockett} message={isEnded.message} />
      )}
    </div>
  );
}
