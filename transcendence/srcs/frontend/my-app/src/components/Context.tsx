import { useState } from "react";
import { Socket } from "socket.io-client";
import { DefaultEventsMap } from "@socket.io/component-emitter";
import * as types from "../types/type";
import UserContext from "../context/User";
import ChatContext from "../context/Chat";
import LoggedContext from "../context/Logged";
import DestinationContext from "../context/Destination";
import SocketContext from "../context/Socket";
import FriendsContext from "../context/Friends";
import ChatToggleContext from "../context/ChatToggle";
import ChannelsContext from "../context/Channels";
import WatchContext from "../context/WatchGame";
import GameInviteContext from "../context/GameInvite";
import SoundsStatusContext from "../context/SoundsStatus";

export const Context = ({ children }) => {
  const [User, setUser] = useState<types.User_me_type>({
    id: 0,
    login: "",
    email: "",
    image: "",
    channels: [],
    friends: [],
    isTwoFactorAuthEnabled: false,
  });

  const [useChat, setChat] = useState<boolean>(false);
  const [logged, setLogged] = useState<boolean>(false);
  const [destination, setDestination] = useState<number | string>(0);
  const [soundStatus, setSoundStatus] = useState<types.soundStatus>({
    notification: true,
    gameSong: true,
    gameEffects: true,
  });
  const [friends, setFriends] = useState<types.friend_type[]>([]);
  const [channels, setChannels] = useState<types.channel_type[]>([]);
  const [watchMode, setWatchMode] = useState<{
    mode: boolean;
    idToWatch: string;
  }>({
    mode: false,
    idToWatch: "",
  });

  const [gameInvite, setGameInvite] = useState<types.gameInviteType>({
    idSender: 0,
    idRecever: 0,
    gameMode: "classic",
    accepted: false,
  });

  const [chatToggle, setChatToggle] = useState<types.chatToggle>({
    privateChatNot: 0,
    channelChatNot: 0,
    friendshipNotific: 0,
  });

  const [socket, setSocket] =
    useState<Socket<DefaultEventsMap, DefaultEventsMap>>();
  const value = { User, setUser };
  const _socket = { socket, setSocket };
  const chatSet = { useChat, setChat };
  const _logged = { logged, setLogged };
  const _destination = { destination, setDestination };
  const _friends = { friends, setFriends };
  const _channels = { channels, setChannels };
  const _chatToggle = { chatToggle, setChatToggle };
  const _watchMode = { watchMode, setWatchMode };
  const _gameInvite = { gameInvite, setGameInvite };
  const _soundStatus = { soundStatus, setSoundStatus };

  return (
    <UserContext.Provider value={value}>
      <ChatContext.Provider value={chatSet}>
        <LoggedContext.Provider value={_logged}>
          <SocketContext.Provider value={_socket}>
            <DestinationContext.Provider value={_destination}>
              <FriendsContext.Provider value={_friends}>
                <ChannelsContext.Provider value={_channels}>
                  <ChatToggleContext.Provider value={_chatToggle}>
                    <WatchContext.Provider value={_watchMode}>
                      <GameInviteContext.Provider value={_gameInvite}>
                        <SoundsStatusContext.Provider value={_soundStatus}>
                          {children}
                        </SoundsStatusContext.Provider>
                      </GameInviteContext.Provider>
                    </WatchContext.Provider>
                  </ChatToggleContext.Provider>
                </ChannelsContext.Provider>
              </FriendsContext.Provider>
            </DestinationContext.Provider>
          </SocketContext.Provider>
        </LoggedContext.Provider>
      </ChatContext.Provider>
    </UserContext.Provider>
  );
};
