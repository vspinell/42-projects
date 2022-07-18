import React, { createContext } from "react";


const ChatToggleContext = createContext<any>({
    privateChatNot: 0,
    channelChatNot: 0,
    friendshipNotific: 0,
  });

export default ChatToggleContext;