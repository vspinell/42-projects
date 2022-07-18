import React, { useContext, useEffect, useState } from "react";
import {
  Avatar,
  Button,
  Checkbox,
  createTheme,
  Divider,
  List,
  ListItem,
  ListItemAvatar,
  ListItemButton,
  ListItemText,
  Theme,
  ThemeProvider,
  Tooltip,
  Typography,
} from "@mui/material";
import { peopleSettings, User_type } from "../../types/type";
import UserContext from "../../context/User";
import PersonAddIcon from "@mui/icons-material/PersonAdd";
import FriendsContext from "../../context/Friends";
import CloseIcon from "@mui/icons-material/Close";
import RemoveIcon from "@mui/icons-material/Remove";
import AddModeratorIcon from "@mui/icons-material/AddModerator";
import RemoveModeratorIcon from "@mui/icons-material/RemoveModerator";
import CommentsDisabledIcon from "@mui/icons-material/CommentsDisabled";
import CommentIcon from "@mui/icons-material/Comment";
import LockIcon from "@mui/icons-material/Lock";
import { leaveChannel } from "./ChatFeed";
import LogoutIcon from "@mui/icons-material/Logout";

export default function ChannelSettings({
  channel,
  setChannelFunction,
  navigate,
}) {
  const { User } = useContext(UserContext);
  const [addUser, setAddUser] = useState<boolean>(false);
  const [checked, setChecked] = useState<number[]>([1]);
  const { friends } = useContext(FriendsContext);
  const [insertPsw, setInsertPsw] = useState<{
    insert: boolean;
    password: string;
    where: string;
  }>({
    insert: false,
    password: "",
    where: channel.name,
  });
  let partecipantsList: peopleSettings[] | JSX.Element[] = [];

  function handleChange(e: any): void {
    const { name, value } = e.target;
    setInsertPsw((prevState) => {
      return {
        ...prevState,
        [name]: value,
      };
    });
  }

  const theme: Theme = createTheme({
    palette: {
      primary: {
        main: "#000000",
      },
      secondary: {
        main: "#f5c71a",
      },
    },
  });

  async function setAdmin(info: {
    channelName: string;
    user: peopleSettings;
  }): Promise<void> {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/setAdmin`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(info),
      }
    );
  }

  async function setMuted(info: {
    channelName: string;
    user: peopleSettings;
  }): Promise<void> {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/setMuted`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(info),
      }
    );
  }

  async function unsetMuted(info: {
    channelName: string;
    user: peopleSettings;
  }): Promise<void> {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/unsetMuted`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(info),
      }
    );
  }

  async function setBanned(info: {
    channelName: string;
    user: peopleSettings;
  }): Promise<void> {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/setBanned`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(info),
      }
    );
  }

  async function unsetAdmin(info: {
    channelName: string;
    user: peopleSettings;
  }): Promise<void> {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/unsetAdmin`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(info),
      }
    );
  }

  function isAdmin(user: User_type): boolean {
    if (
      (channel.admins as []).findIndex(
        (admin) => (admin as any).id == user.id
      ) != -1
    )
      return true;
    return false;
  }

  function isMuted(user: User_type): boolean {
    if ((channel.muted as []).findIndex((id) => id == user.id) != -1)
      return true;
    return false;
  }

  //Buttons on Users
  function adminSet(partecipant: peopleSettings): JSX.Element | undefined {
    if (User.id == channel.owner.id || isAdmin(User)) {
      if (!partecipant.admin && !partecipant.owner)
        return (
          <Tooltip title="Set admin">
            <button
              className="btn btn-primary butt-add-friend"
              onClick={() =>
                setAdmin({ channelName: channel.name, user: partecipant })
              }
            >
              <AddModeratorIcon />
            </button>
          </Tooltip>
        );
      else if (partecipant.admin && !partecipant.owner)
        return (
          <Tooltip title="Unset admin">
            <button
              className="btn btn-primary butt-add-friend"
              onClick={() =>
                unsetAdmin({ channelName: channel.name, user: partecipant })
              }
            >
              <RemoveModeratorIcon />
            </button>
          </Tooltip>
        );
    }
  }

  async function dataRemoveUser(info: {
    channelName: string;
    user: peopleSettings;
  }): Promise<void> {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/removeUser`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(info),
      }
    );
  }

  function removeUser(partecipant: peopleSettings): JSX.Element | undefined {
    if (User.id == channel.owner.id || isAdmin(User)) {
      if (!partecipant.owner)
        return (
          <Tooltip title="Remove user">
            <button
              className="btn btn-primary butt-add-friend"
              onClick={() =>
                dataRemoveUser({ channelName: channel.name, user: partecipant })
              }
            >
              <RemoveIcon />
            </button>
          </Tooltip>
        );
    }
  }

  function muteUser(partecipant: peopleSettings): JSX.Element | undefined {
    if (User.id == channel.owner.id || isAdmin(User)) {
      if (!partecipant.owner && !isAdmin(partecipant) && !isMuted(partecipant))
        return (
          <Tooltip title="Mute user">
            <button
              className="btn btn-primary butt-add-friend"
              onClick={() =>
                setMuted({ channelName: channel.name, user: partecipant })
              }
            >
              <CommentsDisabledIcon />
            </button>
          </Tooltip>
        );
      else if (isMuted(partecipant))
        return (
          <Tooltip title="Disable mute">
            <button
              className="btn btn-primary butt-add-friend"
              onClick={() =>
                unsetMuted({ channelName: channel.name, user: partecipant })
              }
            >
              <CommentIcon />
            </button>
          </Tooltip>
        );
    }
  }

  function banUser(partecipant: peopleSettings): JSX.Element | undefined {
    if (User.id == channel.owner.id || isAdmin(User)) {
      if (!partecipant.owner && !isAdmin(partecipant))
        return (
          <Tooltip title="Ban user">
            <button
              className="btn btn-primary butt-add-friend"
              onClick={() =>
                setBanned({ channelName: channel.name, user: partecipant })
              }
            >
              <LockIcon />
            </button>
          </Tooltip>
        );
    }
  }

  function changePassword(_name: string, _key: string): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/changePassword`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ channelName: _name, newPassword: _key }),
      }
    );
  }

  function removePassword(_name: string): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/removePassword`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ channelName: _name }),
      }
    );
  }

  partecipantsList = channel.users.map((user: User_type) => {
    return {
      id: user.id,
      login: user.login,
      image: user.image,
      admin: isAdmin(user) == true ? true : false,
      owner: user.id == channel.owner.id ? true : false,
    };
  });

  const found: number = partecipantsList.findIndex(
    (user) => user.id == User.id
  );
  const userInChannel: peopleSettings | JSX.Element = partecipantsList.splice(
    found,
    1
  )[0];

  function findPrivilegeStr(user: peopleSettings) {
    if (user.owner == true) return "Owner";
    if (isAdmin(user)) return "Admin";
    return "User";
  }

  //Users as Elements
  partecipantsList = partecipantsList.map((partecipant) => {
    return (
      <div key={partecipant.id + "inlist"}>
        <ListItem key={partecipant.id} alignItems="center">
          <ListItemAvatar>
            <Avatar
              className="Avatar"
              alt={partecipant.login}
              src={partecipant.image}
              onClick={(e) => navigate(`${partecipant.login}`)}
            />
          </ListItemAvatar>
          <ListItemText
            primary={partecipant.login}
            secondary={
              <React.Fragment>
                <Typography
                  sx={{ display: "inline" }}
                  component="span"
                  variant="body2"
                  color="text.primary"
                >
                  {findPrivilegeStr(partecipant)}
                </Typography>
              </React.Fragment>
            }
          />
          {adminSet(partecipant)}
          {banUser(partecipant)}
          {muteUser(partecipant)}
          {removeUser(partecipant)}
        </ListItem>
        {(partecipantsList[partecipantsList.length - 1] as peopleSettings).id ==
        partecipant.id ? (
          <></>
        ) : (
          <Divider variant="inset" component="li" />
        )}
      </div>
    );
  });

  // AddYourself
  partecipantsList.unshift(
    <div key={(User as any).id + "inlist"}>
      <ListItem key={(User as any).id} alignItems="center">
        <ListItemAvatar>
          <Avatar
            className="Avatar"
            alt={(User as any).login}
            src={(User as any).image}
            onClick={(e) => navigate(`${User.login}`, { replace: true })}
          />
        </ListItemAvatar>
        <ListItemText
          primary={(User as any).login}
          secondary={
            <React.Fragment>
              <Typography
                sx={{ display: "inline" }}
                component="span"
                variant="body2"
                color="text.primary"
              >
                {findPrivilegeStr(userInChannel as peopleSettings)}
              </Typography>
            </React.Fragment>
          }
        />
        <button
          className="btn btn-primary butt-add-friend"
          onClick={() => leaveChannel(channel.name)}
        >
          <Tooltip title="Leave channel">
            <LogoutIcon />
          </Tooltip>
        </button>
      </ListItem>
      <Divider variant="inset" component="li" />
    </div>
  );

  //AddUser
  if (User.id == channel.owner.id || isAdmin(User))
    partecipantsList.unshift(
      <div key={"AddPartinlist"} onClick={() => setAddUser(true)}>
        <ListItem
          className="channel-setting-add-user"
          key={"AddPartinlist"}
          alignItems={"center"}
        >
          <ListItemAvatar>
            <Avatar sx={{ bgcolor: "#f5c71a" }}>
              <PersonAddIcon style={{ fill: "black" }} />
            </Avatar>
          </ListItemAvatar>
          <ListItemText
            className="channel-setting-add-user-text"
            primary="Add user"
          />
        </ListItem>
        <Divider variant="inset" component="li" />
      </div>
    );

  const handleToggle = (value) => () => {
    const currentIndex: number = checked.indexOf(value);
    const newChecked: number[] = [...checked];
    if (currentIndex === -1) {
      newChecked.push(value);
    } else {
      newChecked.splice(currentIndex, 1);
    }
    setChecked(newChecked);
  };

  function addUserToChannel(info: {
    channelName: string;
    newUsers: number[];
  }): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/addUser`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(info),
      }
    );
  }

  function pswSettings(): JSX.Element | undefined {
    if (channel.owner.id == User.id && channel.type == "protected")
      return (
        <div className="pass-button">
          <button
            className="btn btn-primary butt-add-friend"
            onClick={() => removePassword(channel.name)}
          >
            Remove Password
          </button>
          <button
            className="btn btn-primary butt-add-friend"
            onClick={() => {
              setInsertPsw((prev) => {
                return {
                  ...prev,
                  insert: true,
                };
              });
            }}
          >
            Change Password
          </button>
          {insertPsw.insert && (
            <div
              style={{
                display: "flex",
                flexDirection: "row",
                gap: "10px",
                marginTop: "10px",
              }}
            >
              <p>password:</p>
              <input
                type="password"
                name="password"
                className={"demo-password"}
                value={insertPsw.password}
                onChange={handleChange}
                onKeyDown={(e) => {
                  if (e.key === "Enter") {
                    changePassword(insertPsw.where, insertPsw.password);
                    setInsertPsw((prev) => {
                      return {
                        ...prev,
                        insert: false,
                        password: "",
                      };
                    });
                  }
                }}
                style={{ height: "25px", width: "80%" }}
                autoFocus
              />
            </div>
          )}
        </div>
      );
    else if (channel.owner.id == User.id && channel.type == "public")
      return (
        <div className="pass-button">
          <button
            className="btn btn-primary butt-add-friend"
            onClick={() => {
              setInsertPsw((prev) => {
                return {
                  ...prev,
                  insert: true,
                };
              });
            }}
          >
            Set Password
          </button>
          {insertPsw.insert && (
            <div
              style={{
                display: "flex",
                flexDirection: "row",
                gap: "10px",
                marginTop: "10px",
              }}
            >
              <p>password:</p>
              <input
                type="password"
                name="password"
                className={"demo-password"}
                value={insertPsw.password}
                onChange={handleChange}
                onKeyDown={(e) => {
                  if (e.key === "Enter") {
                    changePassword(insertPsw.where, insertPsw.password);
                    setInsertPsw((prev) => {
                      return {
                        ...prev,
                        insert: false,
                        password: "",
                      };
                    });
                  }
                }}
                style={{ height: "25px", width: "80%" }}
                autoFocus
              />
            </div>
          )}
        </div>
      );
  }

  return (
    <div className="channel-settings">
      <div
        style={{
          display: "flex",
          justifyContent: "flex-end",
          margin: "0px",
          height: "20px",
        }}
      >
        <CloseIcon
          style={{ margin: "20px 20px 0 0", cursor: "pointer" }}
          onClick={() => {
            if (addUser == true) setAddUser(false);
            else setChannelFunction("chat");
          }}
        />
      </div>
      <div className="channel-settings-body">
        <h2 className="set-title">{channel.name}</h2>
        <p className="set-sub-title">
          {channel.type} channel · {(channel.users as []).length} partecipants
        </p>
        {channel.description && (
          <p className="description">"{channel.description}"</p>
        )}
        {!addUser ? (
          <div>
            <List
              sx={{
                width: 360,
                backgroundColor: "",
                border: "1px solid grey",
                borderRadius: "15px",
              }}
            >
              {partecipantsList}
            </List>
            {pswSettings()}
          </div>
        ) : (
          <>
            <p style={{ marginTop: "30px" }}>Add Users</p>
            <ThemeProvider theme={theme}>
              <List dense sx={{ width: 300, bgcolor: "0, 0, 0, 0.8" }}>
                {friends.map((value) => {
                  const labelId = `checkbox-list-secondary-label-${value.id}`;
                  if (
                    (channel.users as []).findIndex(
                      (user) => (user as any).id == value.id
                    ) == -1 &&
                    (channel.banned as []).findIndex((id) => id == value.id) ==
                      -1
                  ) {
                    return (
                      <ListItem
                        key={value.id}
                        secondaryAction={
                          <Checkbox
                            edge="end"
                            onChange={handleToggle(value)}
                            checked={checked.indexOf(value) !== -1}
                            inputProps={{ "aria-labelledby": labelId }}
                          />
                        }
                        disablePadding
                      >
                        <ListItemButton>
                          <ListItemAvatar>
                            <Avatar
                              alt={`Avatar n°${value.id}`}
                              src={value.image}
                            />
                          </ListItemAvatar>
                          <ListItemText id={labelId} primary={value.login} />
                        </ListItemButton>
                      </ListItem>
                    );
                  }
                })}
              </List>
              <Button
                color="secondary"
                variant="contained"
                style={{ margin: "10px" }}
                disabled={checked.length == 1 ? true : false}
                onClick={() => {
                  checked.splice(0, 1);
                  addUserToChannel({
                    channelName: channel.name,
                    newUsers: checked,
                  });
                  setAddUser(false);
                  setChecked([1]);
                }}
              >
                add
              </Button>
            </ThemeProvider>
          </>
        )}
      </div>
    </div>
  );
}
