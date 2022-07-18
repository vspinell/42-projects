import React, { useEffect, useState } from "react";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import AddIcon from "@mui/icons-material/Add";
import RemoveIcon from "@mui/icons-material/Remove";
import * as types from "../../types/type";
import { Avatar, List } from "@mui/material";
import LockOpenIcon from "@mui/icons-material/LockOpen";
import { useSnackbar } from "notistack";
import "../../style/chat/Contact.css";
import "../../style/chat/AddFriend.css";
import { useNavigate } from "react-router-dom";

export default function AddFriend({ setChatFunction, updateRequest }) {
  const [isShown, setIsShown] = useState<boolean>(false);
  let [friendAddList, setFriendAddList] = useState<types.friend_type[]>([]);
  const { enqueueSnackbar } = useSnackbar();
  const navigate = useNavigate();

  function add(_userId: number): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/add`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: _userId }),
      }
    );
  }

  function decline(_userId: number): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/declineSent`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: _userId }),
      }
    );
  }

  function unblockFriend(_userId: number): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/unblock`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: _userId }),
      }
    );
  }

  useEffect(() => {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/noFriends`,
      { credentials: "include" }
    )
      .then((resp) => resp.json())
      .then((res) => {
        setFriendAddList(res);
      });
  }, [updateRequest]);

  function userRequestStatus(user: types.friend_type): JSX.Element {
    switch (user.request) {
      case "true":
        return (
          <RemoveIcon
            className="add-icon"
            onClick={(e) => {
              decline(user.id);
            }}
          />
        );
      case "false":
        return (
          <AddIcon
            className="add-icon"
            onClick={(e) => {
              enqueueSnackbar(`Invite sent`, {
                variant: "success",
                autoHideDuration: 3000,
              });
              add(user.id);
            }}
          />
        );
      case "blocked":
        return (
          <LockOpenIcon
            className="add-icon"
            onClick={(e) => {
              unblockFriend(user.id);
            }}
          />
        );
      default:
        return <></>;
    }
  }

  function showUserList(): JSX.Element[] {
    const users: JSX.Element[] = friendAddList.map((user) => {
      const labelId: string = `checkbox-list-secondary-label-${user.id}`;
      return (
        <div
          onMouseEnter={() => setIsShown(true)}
          onMouseLeave={() => setIsShown(false)}
          className="friend-list"
          style={{ cursor: "initial" }}
          key={`${user.id}`}
        >
          <li className="clearfix" style={{ cursor: "initial" }}>
            <Avatar
              alt={`Avatar n°${user.id}`}
              src={user.image}
              style={{ cursor: "pointer" }}
              onClick={() => {
                navigate(`${user.login}`);
              }}
            />
            <div className="about">
              <div className="name">{user.login}</div>
            </div>
          </li>
          {userRequestStatus(user)}
        </div>
      );
    });
    return users;
  }

  return (
    <div className="add-friend">
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
            setChatFunction("");
          }}
        />
      </div>
      <form className="add-friend-body">
        <fieldset className="add-fieldset">
          <legend style={{ textAlign: "center" }}>Add Friend</legend>
          <List className="chat-list" dense>
            {friendAddList.length > 0 ? (
              showUserList()
            ) : (
              <h5
                style={{
                  textAlign: "center",
                  color: "white",
                  marginTop: "40px",
                  whiteSpace: "pre-line",
                }}
              >
                There are no users left <br />
                &#128546;
              </h5>
            )}
          </List>
        </fieldset>
      </form>
    </div>
  );
}
