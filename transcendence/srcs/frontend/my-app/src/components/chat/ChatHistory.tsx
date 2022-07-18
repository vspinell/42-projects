import { message_type } from "../../types/type";
import ChatMessage from "./ChatMessage";
import ReactScrollableFeed from "react-scrollable-feed";

export default function ChatHistory({ chatHistory }) {
  let chatMessages: JSX.Element[] = [];

  chatMessages = chatHistory.map((message: message_type, index: number) => {
    if (message.text && !message.serverMessage)
      return (
        <ChatMessage
          key={`${message.sender}:${index}`}
          sender={message.sender}
          text={message.text}
        />
      );
    else
      return (
        <p key={`${message.sender}:${index}`} className="server-message">
          {message.text}
        </p>
      );
  });

  return (
    <div className="chat-history">
      <ReactScrollableFeed>
        <ul>{chatMessages}</ul>
      </ReactScrollableFeed>
    </div>
  );
}
