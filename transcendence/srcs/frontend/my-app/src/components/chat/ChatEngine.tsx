import { useContext, useEffect, useRef, useState } from "react";
import UserContext from "../../context/User"; // setto l'oggetto in questo file
import ChatContext from "../../context/Chat";
import LoggedContext from "../../context/Logged";
import SocketContext from "../../context/Socket";
import * as types from "../../types/type";
import "../../style/chat/Chat.css";
import DestinationContext from "../../context/Destination";
import ChatMenu from "./ChatMenu";
import ChatFeed from "./ChatFeed";
import FriendsContext from "../../context/Friends";
import ChatToggleContext from "../../context/ChatToggle";
import ChannelsContext from "../../context/Channels";
import { audio } from "../App";
import { useNavigate } from "react-router-dom";
import GameInviteContext from "../../context/GameInvite";
import { useSnackbar } from "notistack";
import { Button, createTheme, ThemeProvider } from "@mui/material";

//looks for index of a specific channel in channels array, return -1 if not exists
export function channelIndex(
  channelName: string,
  myChannels: types.channel_type[]
): number {
  let found: number;

  if (
    (found = myChannels.findIndex((ch) => ch.name == channelName)) !=
    -1
  )
    return found;
  return -1;
}

//looks for index of a specific friend in friends array, return -1 if not exists
export function friendIndex(
  userId: number,
  myFriends: types.User_type[]
): number {
  let found: number;

  if (
    (found = myFriends.findIndex((friend) => friend.id == userId)) !=
    -1
  )
    return found;
  return -1;
}

export function ChatEngine({ loadedAudio }) {
  const { setGameInvite } = useContext(GameInviteContext);
  const { User } = useContext(UserContext);
  const { destination, setDestination } = useContext(DestinationContext);
  const { logged } = useContext(LoggedContext);
  const { useChat } = useContext(ChatContext);
  const { friends, setFriends } = useContext(FriendsContext);
  const { channels, setChannels } = useContext(ChannelsContext);
  const { socket } = useContext(SocketContext);
  const { setChatToggle } = useContext(ChatToggleContext);
  const [updateChatFeed, setUpdateChatFeed] = useState<boolean>(false);
  const [updateRequest, setUpdateRequest] = useState<boolean>(false);
  const [loading, setLoading] = useState<string>("start");
  const [channelFunction, setChannelFunction] =
    useState<string>("chat");
  const navigate = useNavigate();
  const { enqueueSnackbar, closeSnackbar } = useSnackbar();

  function syncStart(response: types.server_response_type): void {
    setLoading("fetch");
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends`,
      {
        credentials: "include",
      }
    )
      .then((resp) => resp.json())
      .then((res) => {
        addNotificationsFriend(res);
        setFriends(res);
      });
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel`,
      {
        credentials: "include",
      }
    )
      .then((resp) => resp.json())
      .then((res) => {
        addNotificationsChannel(res);
        setChannels(res);
      });
    syncRequest();
    setLoading("idle");
  }

  function addNotificationsFriend(res: types.friend_type[]): void {
    let privateNot: number = 0;
    res.map((friend: types.friend_type) => {
      privateNot += friend.notifications;
    });
    setChatToggle((prev: types.chatToggle) => {
      return {
        ...prev,
        privateChatNot: privateNot,
      };
    });
  }

  function addNotificationsChannel(res: types.channel_type[]): void {
    let channelNot: number = 0;
    res.map((channel: types.channel_type) => {
      channelNot += channel.notifications;
    });
    setChatToggle((prev: types.chatToggle) => {
      return {
        ...prev,
        channelChatNot: channelNot,
      };
    });
  }

  //updates friend if exists otherwise adds it
  function addFriends(response: types.server_response_type): void {
    setFriends((prevFriends: types.friend_type[]) => {
      let position: number;
      let newFriends: types.friend_type[] = [...prevFriends];

      if (
        (position = friendIndex(response.origin.id, newFriends)) != -1
      )
        newFriends[position] = response.origin;
      else newFriends = [...newFriends, response.origin];
      return newFriends;
    });
    syncRequest();
  }

  function closeChatIfOpen(response: types.server_response_type): void {
    setDestination((prevDestination: number | string) => {
      if (prevDestination == response.origin) return 0;
      return prevDestination;
    });
  }

  //updates channel if exists otherwise adds it
  function addChannels(response: types.server_response_type): void {
    setChannels((prevChannels) => {
      let position: number;
      let newChannels: types.channel_type[] = [...prevChannels];
      if ((position = channelIndex(response.origin.name, newChannels)) != -1)
        newChannels[position] = response.origin;
      else newChannels = [...newChannels, response.origin];
      return newChannels;
    });
  }

  function removeChannels(
    response: types.server_response_type
  ): void {
    let index: number;
    let notification: number;
    setChannels((prevChannels: types.channel_type[]) => {
      let newChannels: types.channel_type[] = [...prevChannels];
      index = channelIndex(response.origin, newChannels);
      notification = newChannels[index].notifications;
      newChannels.splice(index, 1);
      return newChannels;
    });
    setChatToggle((prev: types.chatToggle) => {
      return {
        ...prev,
        channelChatNot: prev.channelChatNot - notification,
      };
    });
    closeChatIfOpen(response);
  }

  //remove specific friend
  function removeFriends(response: types.server_response_type): void {
    let index: number;
    let notification: number;

    setFriends((prevFriends: types.friend_type[]) => {
      let newFriends: types.friend_type[] = [...prevFriends];
      index = friendIndex(response.origin, newFriends);
      notification = newFriends[index].notifications;
      newFriends.splice(index, 1);
      return newFriends;
    });
    setChatToggle((prev) => {
      return {
        ...prev,
        privateChatNot: prev.privateChatNot - notification,
      };
    });
    syncRequest();
    closeChatIfOpen(response);
  }

  function syncRequest(): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/requests`,
      { credentials: "include" }
    )
      .then((resp) => resp.json())
      .then((res) => {
        setChatToggle((prev) => {
          return {
            ...prev,
            friendshipNotific: res.length,
          };
        });
      });
    setUpdateRequest((prev) => !prev);
  }

  function newChannelMessage(response: types.server_response_type): void {
    setChannels((prevChannels: types.channel_type[]) => {
      let newChannels: types.channel_type[] = [...prevChannels];
      const found: number = channelIndex(response.origin.receiver, newChannels);
      if (
        response.origin.sender.id != User.id ||
        (response.origin.sender.id == User.id &&
          response.origin.serverMessage == true)
      ) {
        newChannels[found].notifications += 1;
        setChatToggle((prev: types.chatToggle) => {
          return {
            ...prev,
            channelChatNot: ++prev.channelChatNot,
          };
        });
      }
      newChannels[found].messages = [
        ...newChannels[found].messages,
        response.origin,
      ];
      setDestination((prevDest: number | string) => {
        if (
          prevDest != response.origin.receiver &&
          response.origin.sender.id != User.id &&
          audio != undefined
        )
          audio.notification.play();
        return prevDest;
      });
      if (found != 0)
        newChannels.unshift(newChannels.splice(found, 1)[0]);
      return newChannels;
    });
    setUpdateChatFeed((prev) => !prev);
  }

  function newPrivateMessage(response: types.server_response_type): void {
    setFriends((prevFriends: types.friend_type[]) => {
      let found: number;
      let newFriends: types.friend_type[] = [...prevFriends];
      if (response.origin.sender != User.id) {
        found = friendIndex(response.origin.sender, newFriends);
        newFriends[found].notifications += 1;
        setChatToggle((prev) => {
          return {
            ...prev,
            privateChatNot: ++prev.privateChatNot,
          };
        });
        setDestination((prevDest) => {
          if (
            prevDest != response.origin.sender &&
            audio != undefined
          )
            audio.notification.play();
          return prevDest;
        });
      } else
        found = friendIndex(response.origin.receiver, newFriends);
      newFriends[found].messages = [
        ...newFriends[found].messages,
        response.origin,
      ];
      if (found != 0)
        newFriends.unshift(newFriends.splice(found, 1)[0]);
      return newFriends;
    });
    setUpdateChatFeed((prev) => !prev);
  }

  function acceptInvitation(invitation: types.gameInviteType, login: string) {
    const theme = createTheme({
      palette: {
        primary: {
          main: "#f5c71a",
        },
      },
    });
    
    const action = (key) => (
      <>
        <ThemeProvider theme={theme}>
          <Button
            onClick={() => {
              socket.emit("game", { ...invitation, accepted: true });
              closeSnackbar(key);
            }}
          >
            Accept
          </Button>
          <Button
            onClick={() => {
              closeSnackbar(key);
            }}
          >
            Dismiss
          </Button>
        </ThemeProvider>
      </>
    );
      enqueueSnackbar(
        `You have been invited to play by ${login}`,
        { action }
      );
  }

  function playGame(invitation: types.gameInviteType): void {
    setGameInvite((prev: types.gameInviteType) => {
      return invitation;
    });
    navigate("/home/game", { replace: true });
  }

  function errorGame(invitation: string): void {
    enqueueSnackbar(invitation, {
      variant: "error",
      autoHideDuration: 3000,
    });
  }

  useEffect(() => {
    if (logged) {
      socket.on("private", (response: types.server_response_type) => {
        if (response.type == "sync") {
          if (response.message == "start") syncStart(response);
          else if (response.message == "add") addFriends(response);
          else if (response.message == "remove")
            removeFriends(response);
          else if (response.message == "requests") syncRequest();
        }
        if (response.type == "chat")
          if (response.message == "newMessage")
            newPrivateMessage(response);
      });
      socket.on("channel", (response: types.server_response_type) => {
        if (response.type == "sync") {
          if (response.message == "add") addChannels(response);
          else if (response.message == "remove")
            removeChannels(response);
        }
        if (response.type == "chat")
          if (response.message == "newMessage")
            newChannelMessage(response);
      });
      socket.on("game", (response: types.server_response_type) => {
        if (response.type == "invitation") {
          if (response.message == "invite")
            acceptInvitation(response.origin, response.login);
          else if (response.message == "accepted")
            playGame(response.origin);
          else if (response.message == "error")
            errorGame(response.origin);
        }
      });
    }
  }, [socket]);

  useEffect(() => {}, [destination, friends, channels, loadedAudio]);

  return (
    <div>
      {useChat && (
        <div className="chat-app">
          <ChatMenu
            loading={loading}
            updateRequest={updateRequest}
            setChannelFunction={setChannelFunction}
            navigate={navigate}
          />
          {destination != 0 && (
            <ChatFeed
              updateChatFeed={updateChatFeed}
              channelFunction={channelFunction}
              setChannelFunction={setChannelFunction}
              navigate={navigate}
            />
          )}
        </div>
      )}
    </div>
  );
}
