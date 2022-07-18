import {
  Alert,
  Avatar,
  SpeedDial,
  SpeedDialAction,
  SpeedDialIcon,
} from "@mui/material";
import "../../style/chat/Chat.css";
import { useContext, useState } from "react";
import DestinationContext from "../../context/Destination";
import PersonRemoveIcon from "@mui/icons-material/PersonRemove";
import SettingsIcon from "@mui/icons-material/Settings";
import * as types from "../../types/type";
import InfoIcon from "@mui/icons-material/Info";
import BlockIcon from "@mui/icons-material/Block";
import UserContext from "../../context/User";

export default function ChatHeader({ friend, setChannelFunction, navigate }) {
  const { destination, setDestination } = useContext(DestinationContext);
  const [alert, setAlert] = useState<string>("");

  const actionsFriends = [
    {
      icon: <PersonRemoveIcon style={{ fill: "black" }} />,
      name: "Remove friend",
      func: "remove",
      menu: enableChatFunct,
    },
    {
      icon: <BlockIcon style={{ fill: "black" }} />,
      name: "Block friend",
      func: "block",
      menu: enableChatFunct,
    },
  ];

  const actionsChannels = [
    {
      icon: <InfoIcon style={{ fill: "black" }} />,
      name: "Channel info",
      func: "info",
      menu: enableChatFunct,
    },
  ];

  async function removeFriend(friend: types.friend_type): Promise<void> {
    await fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/remove`,
      {
        method: "DELETE",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: friend }),
      }
    );
  }

  async function blockFriend(friend: types.friend_type): Promise<void> {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/block`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: friend }),
      }
    );
  }

  function enableChatFunct(_function: string): void {
    switch (_function) {
      case "close":
        setDestination(0);
        break;
      case "remove":
        setAlert("remove");
        break;
      case "block":
        setAlert("blocked");
        break;
      case "info":
        setChannelFunction("info");
    }
  }

  function alertSwitch(): JSX.Element {
    switch (alert) {
      case "remove":
        return (
          <Alert
            variant="filled"
            severity="warning"
            sx={{
              backgroundColor: "#f5c71a",
              color: "black",
              overflowWrap: "break-word",
              maxWidth: "inherit",
            }}
          >
            {friend.login} will be removed! &emsp;{" "}
            <button
              style={{ color: "black" }}
              onClick={() => removeFriend(destination)}
              className="button-alert"
            >
              CONFIRM
            </button>
            &emsp;{" "}
            <button
              style={{ color: "black" }}
              onClick={() => setAlert("")}
              className="button-alert"
            >
              DISCARD
            </button>
          </Alert>
        );
      case "blocked":
        return (
          <Alert
            variant="filled"
            severity="error"
            sx={{
              backgroundColor: "#f5c71a",
              color: "black",
              overflowWrap: "break-word",
              maxWidth: "inherit",
            }}
          >
            {friend.login} will be blocked! &emsp;{" "}
            <button
              style={{ color: "black" }}
              onClick={() => blockFriend(destination)}
              className="button-alert"
            >
              CONFIRM
            </button>
            &emsp;{" "}
            <button
              style={{ color: "black" }}
              onClick={() => setAlert("")}
              className="button-alert"
            >
              DISCARD
            </button>
          </Alert>
        );
      default:
        return <></>;
    }
  }

  return (
    <>
      {alert != "" && alertSwitch()}
      <div
        className="chat-header"
        style={{
          width: "100%",
          display: "flex",
          alignItems: "center",
          justifyContent: "space-between",
        }}
      >
        <div
          style={{
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            animation: "fadeIn 0.5s",
          }}
        >
          {typeof destination == "number" ? (
            <>
              <Avatar
                className="Avatar"
                alt={friend.login}
                src={friend.image}
                onClick={(e) => navigate(`${friend.login}`, { replace: true })}
              />
              <div className="chat-about">
                <h6 className="m-b-0">{friend.login}</h6>
              </div>
            </>
          ) : (
            <>
              <Avatar alt={friend.name} src={friend.image} />
              <div className="chat-about">
                <h6 className="m-b-0">{friend.name}</h6>
              </div>
            </>
          )}
        </div>
        <SpeedDial
          ariaLabel="SpeedDial basic example"
          sx={{ height: "10px" }}
          icon={
            <SpeedDialIcon icon={<SettingsIcon style={{ fill: "black" }} />} />
          }
          direction="left"
          FabProps={{
            sx: {
              width: "40px",
              height: "40px",
              bgcolor: "#f5c71a",
              "&:hover": {
                bgcolor: "#c59b06",
              },
            },
          }}
        >
          {typeof destination == "number"
            ? actionsFriends.map((action) => (
                <SpeedDialAction
                  key={action.name}
                  icon={action.icon}
                  tooltipTitle={action.name}
                  tooltipPlacement={"bottom"}
                  onClick={() => action.menu(action.func!)}
                />
              ))
            : actionsChannels.map((action) => (
                <SpeedDialAction
                  key={action.name}
                  icon={action.icon}
                  tooltipTitle={action.name}
                  tooltipPlacement={"bottom"}
                  onClick={() => action.menu(action.func!)}
                />
              ))}
        </SpeedDial>
      </div>
    </>
  );
}
