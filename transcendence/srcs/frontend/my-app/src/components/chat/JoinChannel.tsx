import { useEffect, useState } from "react";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import GroupIcon from "@mui/icons-material/Group";
import LockIcon from "@mui/icons-material/Lock";
import PublicIcon from "@mui/icons-material/Public";
import RefreshIcon from "@mui/icons-material/Refresh";
import {
  Avatar,
  List,
  ListItem,
  ListItemAvatar,
  ListItemText,
  Tooltip,
  Typography,
} from "@mui/material";
import { channel_type, insertPsw } from "../../types/type";

export default function JoinChannel({ setChatFunction }) {
  const [channelToJoin, SetChannelToJoin] = useState<JSX.Element[]>([]);
  const [channelToJoinServer, SetChannelToJoinServer] = useState<
    channel_type[]
  >([]);
  const [refresh, SetRefresh] = useState<boolean>(false);
  const [pswAnim, setPswAni] = useState<boolean>(false);
  const [insertPsw, setInsertPsw] = useState<insertPsw>({
    insert: false,
    password: "",
    where: "",
  });

  const style = {
    color: "white",
    flexWrap: "wrap",
    "&:hover": {
      color: "black",
      backgroundColor: " #f5c71a",
      cursor: "pointer",
    },
  };

  function disablecreateChannel(): void {
    setChatFunction("");
  }

  function iconsSwitch(type: string): JSX.Element {
    switch (type) {
      case "public":
        return <PublicIcon />;
      case "protected":
        return <LockIcon />;
      default:
        return <></>;
    }
  }

  function handleChange(e: any): void {
    const { name, value } = e.target;
    setInsertPsw((prevState: insertPsw) => {
      return {
        ...prevState,
        [name]: value,
      };
    });
  }

  function joinChannel(_name: string, _key: string): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/join`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ name: _name, key: _key }),
      }
    )
      .then((res) => res.json())
      .then((res) => {
        if (res) SetRefresh((prev) => !prev);
        else setPswAni(true);
      });
  }

  useEffect(() => {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/noChannels`,
      { credentials: "include" }
    )
      .then((res) => res.json())
      .then((res) => {
        SetChannelToJoinServer(res);
      });
  }, [refresh]);

  useEffect(() => {
    const channelToJoinTemp: JSX.Element[] = channelToJoinServer.map(
      (channel) => {
        return (
          <div key={channel.name} className="channel-join-list">
            <ListItem
              sx={style}
              onClick={(e) => {
                if (channel.type == "public") joinChannel(channel.name, "");
                else if (
                  channel.type == "protected" &&
                  insertPsw.where != channel.name
                ) {
                  setInsertPsw((prev: insertPsw) => {
                    return {
                      insert: true,
                      password: "",
                      where: channel.name,
                    };
                  });
                } else if ((e.target as any).name != "password") {
                  setInsertPsw((prev: insertPsw) => {
                    return {
                      insert: false,
                      password: "",
                      where: "",
                    };
                  });
                }
              }}
            >
              <ListItemAvatar>
                <Avatar>
                  <GroupIcon />
                </Avatar>
              </ListItemAvatar>
              <ListItemText
                primary={channel.name}
                secondary={
                  <Typography
                    className="typo"
                    component="span"
                    variant="subtitle2"
                  >
                    {channel.type + " channel"}
                  </Typography>
                }
              />
              {iconsSwitch(channel.type)}
              {insertPsw.insert && insertPsw.where == channel.name && (
                <div
                  style={{
                    display: "flex",
                    flexDirection: "row",
                    gap: "10px",
                  }}
                >
                  <p>password:</p>
                  <input
                    type="password"
                    name="password"
                    className={pswAnim ? "demo-password" : ""}
                    onAnimationEnd={() => setPswAni(false)}
                    value={insertPsw.password}
                    onChange={handleChange}
                    onKeyDown={(e) => {
                      if (e.key === "Enter")
                        joinChannel(insertPsw.where, insertPsw.password);
                    }}
                    style={{ height: "25px", width: "80%" }}
                    autoFocus
                  />
                </div>
              )}
            </ListItem>
          </div>
        );
      }
    );
    SetChannelToJoin(channelToJoinTemp);
  }, [channelToJoinServer, insertPsw, pswAnim]);

  return (
    <div>
      <div
        className="people-list-title"
        style={{
          display: "flex",
          alignItems: "center",
          justifyContent: "space-between",
        }}
      >
        <ArrowBackIcon
          className="ArrowBack"
          onClick={() => {
            disablecreateChannel();
          }}
        />
        <Tooltip title="Refresh channels" placement="left">
          <RefreshIcon
            className="refresh-butt"
            onClick={() => SetRefresh((prev) => !prev)}
          />
        </Tooltip>
      </div>
      <div className="join-channel">
        <fieldset>
          <legend>Join channel </legend>
        </fieldset>
        <List
          sx={{ bgcolor: "", width: "100%", maxWidth: 360, color: "white" }}
        >
          {channelToJoin}
        </List>
      </div>
    </div>
  );
}
