import React, { useContext, useEffect, useState } from "react";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import {
  List,
  Avatar,
} from "@mui/material";
import ChatToggleContext from "../../context/ChatToggle";
import "../../style/chat/Contact.css";
import "../../style/chat/AddFriend.css";
import { NavigateFunction, useNavigate } from "react-router-dom";
import CheckIcon from '@mui/icons-material/Check';
import CloseIcon from '@mui/icons-material/Close';
import { chatToggle, friend_type } from "../../types/type";

export default function PendingFriend({ setChatFunction, pendingFriends }) {
  const {setChatToggle } = useContext(ChatToggleContext);
  const [isShown, setIsShown] = useState<boolean>(false);
  const navigate: NavigateFunction = useNavigate();

  function accept(_userId: number): void {
    fetch(`http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/accept`, {
      method: "POST",
      credentials: "include",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ userId: _userId }),
    }).then(() =>
      setChatToggle((prev: chatToggle) => {
        return {
          ...prev,
          friendshipNotific: prev.friendshipNotific--,
        };
      })
    );
  }

  function decline(_userId: number): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/declineReceived`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: _userId }),
      }
    ).then(() =>
      setChatToggle((prev: chatToggle) => {
        return {
          ...prev,
          friendshipNotific: prev.friendshipNotific--,
        };
      })
    );
  }

  function showPendingList(): JSX.Element[] {
    const users: JSX.Element[] = pendingFriends.map((user: friend_type) => {
      const labelId = `checkbox-list-secondary-label-${user.id}`;
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
          <CloseIcon
            className="decline-icon"
            onClick={(e) => {
              e.preventDefault();
              decline(user.id);
            }}
          />
          <CheckIcon
            className="add-icon"
            onClick={(e) => {
              e.preventDefault();
              accept(user.id);
            }}
          />
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
          <legend style={{ textAlign: "center" }}>Pending requests</legend>
          <List className="chat-list" dense>
            {pendingFriends.length > 0 ? (
              showPendingList()
            ) : (
              <h5
                style={{
                  textAlign: "center",
                  color: "white",
                  marginTop: "40px",
                  whiteSpace: "pre-line",
                }}
              >
                No pending request...
              </h5>
            )}
          </List>
        </fieldset>
      </form>
    </div>
  );
}
