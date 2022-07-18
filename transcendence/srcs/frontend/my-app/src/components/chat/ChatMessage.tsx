import { useContext } from "react";
import UserContext from "../../context/User";
import { channel_type, User_type } from "../../types/type";

export default function ChatMessage({ sender, text }) {
  const { User } = useContext(UserContext);

  
  function isPrivate(_sender: number | User_type){
    if(typeof _sender != "number")
      return _sender.id
    else
      return _sender

  }

  return (
    <div>
      <div className="chatBox">
        <div
          className={`message ${
            isPrivate(sender) == User.id ? "my-message" : " other-message"
          } `}
        >
          { 
            <p
              className={`${
                isPrivate(sender) == User.id
                  ? "my-message-paragraph"
                  : "other-message-paragraph"
              }`}
            >
              {(typeof sender) != "number" && isPrivate(sender) != User.id && (
                <span
                  style={{
                    display: "inline",
                    fontSize: "15px",
                    fontStyle: "oblique",
                    fontWeight: "600",
                    color: `${sender.color}`,
                  }}
                >{`${sender.login}\n`}</span>
              )}
              {text}
            </p>
          }
        </div>
      </div>
    </div>
  );
}