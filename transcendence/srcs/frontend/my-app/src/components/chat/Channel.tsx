import { Avatar } from "@mui/material";
import { useContext, useState } from "react";
import ChatToggleContext from "../../context/ChatToggle";
import UserContext from "../../context/User";
import "../../style/chat/Contact.css";
import {
  StyledBadge,
  StyledBadgeNegative,
} from "../../style/chat/styledComponents/styledBadge";

export default function Channel({
  channel,
  setDestination,
  setChannelFunction,
}) {
  const [isShown, setIsShown] = useState<boolean>(false);

  return (
    <div
      onMouseEnter={() => setIsShown(true)}
      onMouseLeave={() => setIsShown(false)}
      className="friend-list"
      onClick={() => {
        setDestination((prevState) => {
          return prevState == channel.name ? 0 : channel.name;
        });
        setChannelFunction("chat");
      }}
    >
      <li className="clearfix">
        <Avatar alt={channel.name} src={channel.image} />
        <div className="about">
          <div className="name">{channel.name}</div>
        </div>
      </li>
      {isShown ? (
        <StyledBadgeNegative
          className="badge-notif"
          badgeContent={channel.notifications}
        ></StyledBadgeNegative>
      ) : (
        <StyledBadge
          className="badge-notif"
          badgeContent={channel.notifications}
        ></StyledBadge>
      )}
    </div>
  );
}
