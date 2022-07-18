import { useState } from "react";
import { NavigateFunction, useNavigate } from "react-router-dom";
import ContactAvatar from "../chat/ContactAvatar";
import "../../style/chat/Chat.css";
import "../../style/chat/Contact.css";
import "../../style/FriendsUser.css";
import { friend_type } from "../../types/type";

export default function FriendsUser({ friends }) {
  const [isShown, setIsShown] = useState<boolean>(false);
  const navigate: NavigateFunction = useNavigate();

  let contactElements: JSX.Element[] = friends.map((friend: friend_type) => {
    return (
      <div
        onMouseEnter={() => setIsShown(true)}
        onMouseLeave={() => setIsShown(false)}
        className="friend-list friends-user"
        key={`${friend.id}-usrlist`}
        onClick={() => {
          navigate(`/${friend.login}`);
        }}
      >
        <li className="clearfix">
          <ContactAvatar friend={friend} navigate={navigate} />
        </li>
      </div>
    );
  });

  return <div className="friends-container">{contactElements}</div>;
}
