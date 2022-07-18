import { Tooltip } from "@mui/material";
import { useContext, useEffect } from "react";
import ChatContext from "../../context/Chat";
import ChatToggleContext from "../../context/ChatToggle";
import DestinationContext from "../../context/Destination";
import "../../style/Header.css"

export default function ChatIcon() {
  const { useChat, setChat } = useContext(ChatContext);
  const { setDestination } = useContext(DestinationContext);
  const { chatToggle } = useContext(ChatToggleContext);

  function enableChat(): void {
    setChat((prevState: boolean) => !prevState);
    setDestination(0);
    localStorage.setItem("useChat", `${!useChat}`);
  }

  useEffect(() => {}, [chatToggle]);

  return (
    <div className="chat--button">
      <Tooltip title="Chat" onClick={enableChat} >
        {chatToggle.privateChatNot ||
        chatToggle.friendshipNotific ||
        chatToggle.channelChatNot > 0 ? (
          <i
            style={{ color: "black", fontSize: 30, animation:"fadeIn 2s infinite", marginTop: "5px"}}
            className="bi bi-exclamation"
          ></i>
        ) : (
          <i
            className="bi bi-chat-dots"
            style={{ color: "black", fontSize: 20, marginTop: "5px"}}
          ></i>
        )}
      </Tooltip>
    </div>
  );
}
