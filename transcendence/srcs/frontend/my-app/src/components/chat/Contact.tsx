import { Menu, MenuItem, Stack, styled } from "@mui/material";
import { useContext, useState } from "react";
import "../../style/chat/Contact.css";
import VisibilityIcon from "@mui/icons-material/Visibility";
import SportsEsportsIcon from "@mui/icons-material/SportsEsports";
import {
  StyledBadge,
  StyledBadgeNegative,
} from "../../style/chat/styledComponents/styledBadge";
import WatchContext from "../../context/WatchGame";
import ContactAvatar from "./ContactAvatar";
import SocketContext from "../../context/Socket";
import UserContext from "../../context/User";
import { useSnackbar } from "notistack";

export default function Contact({
  friend,
  setDestination,
  setChannelFunction,
  navigate,
}) {
  const [isShown, setIsShown] = useState<boolean>(false);
  const { setWatchMode } = useContext(WatchContext);
  const [anchorEl, setAnchorEl] = useState<null | HTMLElement>(null);
  const open = Boolean(anchorEl);
  const { User } = useContext(UserContext);
  const { socket } = useContext(SocketContext);
  const { enqueueSnackbar } = useSnackbar();

  function handleWatchClick(): void {
    setWatchMode((prev) => {
      return {
        mode: true,
        idToWatch: friend.id,
      };
    });
    navigate("../Home/WatchGame");
  }

  const handleClick = (event: any): void => {
    setAnchorEl(event.currentTarget);
  };
  const handleClose = (): void => {
    setAnchorEl(null);
  };

  function gameInvitation(mode: string): void {
    socket.emit("game", {
      idSender: User.id,
      idRecever: friend.id,
      gameMode: mode,
      accepted: false,
    });
  }

  return (
    <div
      onMouseEnter={() => setIsShown(true)}
      onMouseLeave={() => setIsShown(false)}
      className="friend-list"
      onClick={() => {
        setDestination((prevState: number | string) => {
          return prevState == friend.id ? 0 : friend.id;
        });
        setChannelFunction("chat");
      }}
    >
      <li className="clearfix">
        <ContactAvatar friend={friend} navigate={navigate} />
      </li>
      {friend.status == "in game" ? (
        <>
          <VisibilityIcon
            onClick={(e) => {
              e.stopPropagation();
              handleWatchClick();
            }}
          />
        </>
      ) : (
        <>
          <SportsEsportsIcon
            className="chat-icon-multiple"
            onClick={(event: any) => {
              event.stopPropagation();
              handleClick(event);
            }}
          />
          <Menu
            id="basic-menu"
            anchorEl={anchorEl}
            open={open}
            onClose={handleClose}
            MenuListProps={{
              "aria-labelledby": "basic-button",
            }}
          >
            <MenuItem
              onClick={(e) => {
                e.stopPropagation();
                gameInvitation("classic");
                handleClose();
                enqueueSnackbar(`Invite sent`, {
                  variant: "success",
                  autoHideDuration: 3000,
                });
              }}
            >
              Classic
            </MenuItem>
            <MenuItem
              onClick={(e) => {
                e.stopPropagation();
                gameInvitation("special");
                handleClose();
              }}
            >
              Special
            </MenuItem>
          </Menu>
        </>
      )}
      {isShown ? (
        <StyledBadgeNegative
          className="badge-notif"
          badgeContent={friend.notifications}
        ></StyledBadgeNegative>
      ) : (
        <StyledBadge
          className="badge-notif"
          badgeContent={friend.notifications}
        ></StyledBadge>
      )}
    </div>
  );
}
