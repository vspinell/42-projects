import React, { useContext, useEffect, useState } from "react";
import CreateChannel from "./CreateChannel";
import ChatHome from "./ChatHome";
import "../../style/chat/Channel.css";
import AddFriend from "./AddFriend";
import PendingFriend from "./PendingFriend";
import * as types from "../../types/type";
import ChatToggleContext from "../../context/ChatToggle";
import JoinChannel from "./JoinChannel";
import FriendsContext from "../../context/Friends";
import ChannelsContext from "../../context/Channels";
import DestinationContext from "../../context/Destination";

export default function ChatMenu({
  loading,
  updateRequest,
  setChannelFunction,
  navigate
}) {
  const { friends } = useContext(FriendsContext);
  const { channels } = useContext(ChannelsContext);
  const { destination, setDestination } = useContext(DestinationContext);
  const [chatFunction, setChatFunction] = useState<string>("");
  let [pendingFriends, setPendingFriends] = useState<types.User_type[]>([]);
  const { setChatToggle } = useContext(ChatToggleContext);
  const [chatSelector, setChatSelector] = useState<string>("friends");

  useEffect(() => {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/requests`,
      { credentials: "include"})
      .then((resp) => resp.json())
      .then((res) => {
        setPendingFriends(res);
        setChatToggle((prev: types.chatToggle) => {
          return {
            ...prev,
            friendshipNotific: res.length,
          };
        });
      });
  }, [updateRequest, friends]);

  function setMenuByFunc(): JSX.Element {
    switch (chatFunction) {
      case "":
        return (
          <ChatHome
            setChatFunction={setChatFunction}
            friends={friends}
            destination={destination}
            setDestination={setDestination}
            loading={loading}
            pendingFriends={pendingFriends}
            channels={channels}
            setChannelFunction={setChannelFunction}
            chatSelector={chatSelector}
            setChatSelector={setChatSelector}
            navigate={navigate}
          />
        );
      case "createChannel":
        return (
          <CreateChannel
            friends={friends}
            setChatFunction={setChatFunction}
          />
        );
      case "joinChannel":
        return <JoinChannel setChatFunction={setChatFunction} />;
      case "addFriend":
        return (
          <AddFriend
            setChatFunction={setChatFunction}
            updateRequest={updateRequest}
          />
        );
      case "pendingFriend":
        return (
          <PendingFriend
            setChatFunction={setChatFunction}
            pendingFriends={pendingFriends}
          />
        );
        default:
          return <></>
    }
  }

  return <div className="people-list">{setMenuByFunc()}</div>;
}
