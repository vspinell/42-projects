import { useContext, useEffect, useState } from "react";
import UserContext from "../context/User";
import LoggedContext from "../context/Logged";
import Header from "./header/Header";
import AppBody from "./AppBody";
import Footer from "./Footer";
import { io, Socket } from "socket.io-client";
import SocketContext from "../context/Socket";
import "../style/App.css";
import { Route, Routes, useLocation } from "react-router-dom";
import ProtectedRoute from "./auth/ProtectedRoute";
import Login from "./Login";
import NotFound from "./NotFound";
import { ChatEngine } from "./chat/ChatEngine";
import Game from "./game";
import CheckUrl from "./CheckUrl";
import useAudio from "../hooks/useAudio";
import { SnackbarProvider } from "notistack";
import Settings from "./settings/Settings";
import TwoFaAuth from "./TwoFaAuth";
import { Audio } from "../types/type";
import ChatContext from "../context/Chat";
import WatchGame from "./game/WatchGame";
import WatchModeProtected from "./auth/WatchModeProtected";
import ErrorPage from "./ErrorPage";
import ProtectedTwoFa from "./auth/ProtectedTwoFa";

export let audio: Audio;

export default function App() {
  const { User, setUser } = useContext(UserContext);
  const { logged, setLogged } = useContext(LoggedContext);
  const { setSocket } = useContext(SocketContext);
  const [loadedAudio, setLoadedAudio] = useState<boolean>(false);
  const { useChat, setChat } = useContext(ChatContext);
  audio = useAudio(setLoadedAudio);
  let location = useLocation();

  useEffect(() => {
    if (location.pathname === "/home/game")
      setChat((prevState) => {
        if (prevState) return !prevState;
      });
  }, [location.pathname]);

  useEffect(() => {
    if (!logged)
      fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/users/me`,
        {
          credentials: "include",
        }
      )
        .then((resp) => resp.json())
        .then((me) => {
          if (!me) return false;
          setUser(me);
          return true;
        })
        .then((res) => {
          if (res) setLogged((prevState: boolean) => !prevState);
        });
  }, []);

  useEffect(() => {
    if (logged) {
      const client = io(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/chat`,
        {
          query: {
            id: User.id,
          },
        }
      );
      setSocket(client);
    }
  }, [logged]);

  return (
    <div>
      <div className="page">
        <div className="cont">
          {logged && location.pathname !== "/home/game" && <Header />}
          <div className="real-body">
            <SnackbarProvider
              autoHideDuration={15000}
              anchorOrigin={{
                vertical: "top",
                horizontal: "left",
              }}
            >
              <Routes>
                <Route path="/" element={!logged ? <Login /> : <AppBody />} />
                <Route path="ErrorPage" element={<ErrorPage />} />
                <Route path=":url" element={<CheckUrl />} />
                <Route
                  path="/twoFactorAuth"
                  element={
                    <ProtectedTwoFa>
                      <TwoFaAuth />
                    </ProtectedTwoFa>
                  }
                />
                <Route
                  path="Settings"
                  element={
                    <ProtectedRoute>
                      <Settings />
                    </ProtectedRoute>
                  }
                />
                <Route
                  path="Home"
                  element={
                    <ProtectedRoute>
                      <AppBody />
                    </ProtectedRoute>
                  }
                />
                <Route
                  path="Home/Game"
                  element={
                    <ProtectedRoute>
                      <Game />
                    </ProtectedRoute>
                  }
                />
                <Route
                  path="Home/WatchGame"
                  element={
                    // <ProtectedRoute>
                    <WatchModeProtected>
                      <WatchGame />
                    </WatchModeProtected>
                    // </ProtectedRoute>
                  }
                />
                <Route path="*" element={<NotFound />} />
              </Routes>
              <div className="chat--sidebar">
                <ChatEngine loadedAudio={loadedAudio} />
              </div>
            </SnackbarProvider>
          </div>
        </div>
        <Footer />
      </div>
    </div>
  );
}
