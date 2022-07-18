import { useContext, useEffect, useState } from "react";
import ChatHeader from "./ChatHeader";
import ChatHistory from "./ChatHistory";
import DestinationContext from "../../context/Destination";
import UserContext from "../../context/User";
import SocketContext from "../../context/Socket";
import {
  channel_type,
  chatToggle,
  friend_type,
  message_type,
} from "../../types/type";
import ChannelSettings from "./ChannelSettings";
import { channelIndex, friendIndex } from "./ChatEngine";
import FriendsContext from "../../context/Friends";
import ChannelsContext from "../../context/Channels";
import ChatToggleContext from "../../context/ChatToggle";

export function leaveChannel(channel_name: string): void {
  fetch(
    `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/leave`,
    {
      method: "POST",
      credentials: "include",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ channelName: channel_name }),
    }
  );
}

export default function ChatFeed({
  updateChatFeed,
  channelFunction,
  setChannelFunction,
  navigate,
}) {
  const { friends, setFriends } = useContext(FriendsContext);
  const { channels, setChannels } = useContext(ChannelsContext);
  const { destination } = useContext(DestinationContext);
  const { socket } = useContext(SocketContext);
  const { User } = useContext(UserContext);
  const { setChatToggle } = useContext(ChatToggleContext);
  const [message, setMessage] = useState<message_type>({
    sender: User.id,
    receiver: 0,
    text: "",
    serverMessage: false,
  });
  const [chatHistory, setChatHistory] = useState<message_type[]>([]);

  useEffect(() => {
    if (destination != 0) {
      let index: number;
      if (typeof destination == "string") {
        index = channelIndex(destination, channels);
        let notification: number = channels[index].notifications;
        setChatToggle((prev: chatToggle) => {
          return {
            ...prev,
            channelChatNot: prev.channelChatNot - notification,
          };
        });
        setChannels((prev: channel_type[]) => {
          let newChannel: channel_type[] = [...prev];
          newChannel[index].notifications = 0;
          return newChannel;
        });
        setChatHistory(channels[index].messages);
      } else {
        index = friendIndex(destination, friends);
        let notification: number = friends[index].notifications;
        setChatToggle((prev: chatToggle) => {
          return {
            ...prev,
            privateChatNot: prev.privateChatNot - notification,
          };
        });
        setFriends((prev: friend_type[]) => {
          let newFriends: friend_type[] = [...prev];
          newFriends[index].notifications = 0;
          return newFriends;
        });
        setChatHistory(friends[index].messages);
      }
      socket.emit("iRead", destination);
    }
  }, [destination, updateChatFeed]);

  function findDestination(destination: number | string): number {
    let found: number;
    if (typeof destination == "number")
      found = friends.find((friend) => friend.id == destination);
    else found = channels.find((channel) => channel.name == destination);
    return found == undefined ? 0 : found;
  }

  function writeMessage(e: any) {
    setMessage((prevState) => {
      return {
        ...prevState,
        sender: User.id,
        receiver: destination,
        text: e.target.value,
      };
    });
  }

  async function Send(): Promise<void> {
    if (message.text == "") return;
    if (typeof destination == "string") socket.emit("channel", message);
    else socket.emit("private", message);
    setMessage((prevState) => {
      return {
        ...prevState,
        text: "",
      };
    });
  }

  function muted(): boolean {
    if (typeof destination == "string")
      if (
        channels[channelIndex(destination, channels)].muted.findIndex(
          (user) => user == User.id
        ) != -1
      )
        return true;
    return false;
  }

  function feedDisplay(): JSX.Element {
    switch (channelFunction) {
      case "chat":
        return (
          <>
            <ChatHeader
              friend={findDestination(destination)}
              setChannelFunction={setChannelFunction}
              navigate={navigate}
            />
            <ChatHistory chatHistory={chatHistory} />
            <div className="input-group">
              <input
                type="text"
                className="form-control"
                placeholder="Message"
                onChange={(e) => writeMessage(e)}
                value={message.text}
                onKeyDown={(e) => {
                  if (e.key === "Enter") Send();
                }}
                autoFocus
                disabled={muted()}
              />
              <span className="input-group-text">
                <i
                  onClick={() => Send()}
                  className="fa fa-send"
                  style={{ cursor: "pointer" }}
                ></i>
              </span>
            </div>
          </>
        );
      case "info":
        return (
          <ChannelSettings
            channel={findDestination(destination)}
            setChannelFunction={setChannelFunction}
            navigate={navigate}
          />
        );
      default:
        return <></>;
    }
  }

  return (
    <div className="chat--container" style={{ animation: "fadeIn 1" }}>
      <div className="chat">{feedDisplay()}</div>
    </div>
  );
}
