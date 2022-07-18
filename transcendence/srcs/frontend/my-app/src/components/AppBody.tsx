import { useEffect, useContext, useState } from "react";
import Button from "@mui/material/Button";
import { styled } from "@mui/material/styles";
import ChatContext from "../context/Chat";
import UserContext from "../context/User";
import LoggedContext from "../context/Logged";
import "../style/AppBody.css";
import { Link } from "react-router-dom";

export default function AppBody() {
  const { setChat } = useContext(ChatContext);
  const { logged } = useContext(LoggedContext);

  useEffect(() => {
    let set: string | null;
    if ((set = localStorage.getItem("useChat")) != null) {
      setChat(() => {
        if (logged) return set == "true" ? true : false;
        else false;
      });
    }
  }, [logged]);

  return (
    <div className="app-body">
      {logged && (
        <div className="container-app-body">
          <div className="pong-descr">
            <img className="pong-img" src="./Pong.jpeg" alt="pong-game" />
              <p className="pong-text">
                Pong is a two-dimensional sports game that simulates table tennis.
                The player controls an in-game paddle by moving it vertically
                across the left or right side of the screen. They can compete
                against another player controlling a second paddle on the opposing
                side. Players use the paddles to hit a ball back and forth. The
                goal is for each player to reach five points before the
                opponent; points are earned when one fails to return the ball to
                the other.
              </p>
          </div>
                <Link to="/home/game">
                  <button className="home--button"> START GAME </button>
                </Link>
          <img src="./wave.svg" alt="waves" />
        </div>
      )}
    </div>
  );
}
