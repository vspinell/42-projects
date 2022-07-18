import React, { useContext, useEffect, useState } from "react";
import "../../style/UserInfo.css";
import ChatIcon from "@mui/icons-material/Chat";
import {
  Avatar,
  Box,
  createTheme,
  Menu,
  MenuItem,
  Tab,
  Tabs,
  Theme,
  ThemeProvider,
} from "@mui/material";
import DestinationContext from "../../context/Destination";
import GroupIcon from "@mui/icons-material/Group";
import EqualizerIcon from "@mui/icons-material/Equalizer";
import UserContext from "../../context/User";
import { friendIndex } from "../chat/ChatEngine";
import FriendsContext from "../../context/Friends";
import SportsEsportsIcon from "@mui/icons-material/SportsEsports";
import SocketContext from "../../context/Socket";
import { useSnackbar } from "notistack";
import ChatContext from "../../context/Chat";
import SettingsIcon from "@mui/icons-material/Settings";
import ScoreboardIcon from "@mui/icons-material/Scoreboard";
import { NavigateFunction, useNavigate } from "react-router-dom";
import TableUser from "./TableUser";
import FriendsUser from "./FriendsUser";
import MatchHistory from "./MatchHistory";
import EmojiEventsIcon from "@mui/icons-material/EmojiEvents";
import {
  achievement,
  friend_type,
  matchHistory,
  statisticsType,
  User_type,
} from "../../types/type";

export default function UserInfo({ user, change }) {
  const { setDestination } = useContext(DestinationContext);
  const { friends } = useContext(FriendsContext);
  const [value, setValue] = useState<string>("scores");
  const { User } = useContext(UserContext);
  const { socket, setSocket } = useContext(SocketContext);
  const [anchorEl, setAnchorEl] = useState<null | HTMLElement>(null);
  const { enqueueSnackbar } = useSnackbar();
  const { setChat } = useContext(ChatContext);
  const navigate: NavigateFunction = useNavigate();
  const [statistics, setStatistics] = useState<statisticsType>({
    wins: 0,
    winsSpecial: 0,
    losses: 0,
    lossesSpecial: 0,
    ladderLevel: 0,
    ladderLevelSpecial: 0,
    rank: 0,
    rankSpecial: 0,
    matchHistory: [],
    achievements: [],
  });
  const open = Boolean(anchorEl);
  const [userFriends, setUserFriends] = useState<friend_type[]>([]);

  useEffect(() => {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/statistics`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: user.id }),
      }
    )
      .then((res) => res.json())
      .then((res) => {
        setStatistics((prev) => {
          return {
            ...prev,
            wins: res.wins,
            winsSpecial: res.winsSpecial,
            losses: res.losses,
            lossesSpecial: res.lossesSpecial,
            ladderLevel: res.ladderLevel,
            ladderLevelSpecial: res.ladderLevelSpecial,
            rank: res.rank,
            rankSpecial: res.rankSpecial,
            matchHistory: res.matchHistory,
            achievements: res.achievements,
          };
        });
      });
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/friends/userFriends`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: user.id }),
      }
    )
      .then((res) => res.json())
      .then((res) => {
        setUserFriends((prev) => res);
      });
  }, [change]);

  const handleClick = (event: any) => {
    setAnchorEl(event.currentTarget);
  };
  const handleClose = () => {
    setAnchorEl(null);
  };

  const handleChange = (event: React.SyntheticEvent, newValue: string) => {
    setValue(newValue);
  };

  const theme: Theme = createTheme({
    palette: {
      primary: {
        main: "#000000",
      },
    },
  });

  function createData(
    name: string,
    total: number
  ): { name: string; total: number } {
    return { name, total };
  }

  function gameInvitation(mode: string): void {
    socket.emit("game", {
      idSender: User.id,
      idRecever: user.id,
      gameMode: mode,
      accepted: false,
    });
  }

  function userAction(user: friend_type): JSX.Element {
    if (user.id == User.id)
      return (
        <SettingsIcon
          className="chat-icon"
          onClick={(event: any) => navigate(`/Settings`)}
        />
      );
    else if (friendIndex(user.id, friends) == -1) return <></>;
    else
      return (
        <>
          <ChatIcon
            className="chat-icon"
            onClick={() => {
              setChat((prev) => true);
              setDestination((prev) => user.id);
            }}
          />

          {user.status == "online" && (
            <SportsEsportsIcon
              className="chat-icon-multiple"
              onClick={(event: any) => handleClick(event)}
            />
          )}
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
              onClick={() => {
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
              onClick={() => {
                gameInvitation("special");
                handleClose();
              }}
            >
              Special
            </MenuItem>
          </Menu>
        </>
      );
  }

  const rows = [
    createData("Wins", statistics.wins),
    createData("Losses", statistics.losses),
    createData("Ladder Level (points)", statistics.ladderLevel),
    createData("Wins Special", statistics.winsSpecial),
    createData("Losses Special", statistics.lossesSpecial),
    createData("Ladder Level Special (points)", statistics.ladderLevelSpecial),
  ];

  function createAchievTable() {
    return statistics.achievements.map((achi: achievement) => {
      return createData(achi.description, 1);
    });
  }

  return (
    <div className="user-info">
      <div className="user-info-body">
        <div className="user-info-header">
          <Avatar className="avatar-login" alt={user.login} src={user.image} />
          <div className="user-description">
            <h1>{user.login}</h1>
            <h5>{user.email}</h5>
            <h6>{`Rank position: ${statistics.rank}th`}</h6>
          </div>
          {userAction(user)}
        </div>
        <div>
          <ThemeProvider theme={theme}>
            <Box sx={{ marginBottom: "10px" }}>
              <Tabs
                textColor="primary"
                indicatorColor="primary"
                value={value}
                onChange={handleChange}
                aria-label="scrollable auto tabs example"
                centered
              >
                <Tab
                  icon={<EqualizerIcon />}
                  iconPosition="start"
                  value="scores"
                />
                <Tab
                  icon={<GroupIcon />}
                  iconPosition="start"
                  value="friends"
                />
                <Tab
                  icon={<ScoreboardIcon />}
                  iconPosition="start"
                  value="scoreBoard"
                />
                <Tab
                  icon={<EmojiEventsIcon />}
                  iconPosition="start"
                  value="achievement"
                />
              </Tabs>
            </Box>
          </ThemeProvider>
        </div>
        {value == "scores" && (
          <TableUser rows={rows} descrStart={"Statistics"} descrEnd={"Total"} />
        )}
        {value == "friends" && <FriendsUser friends={userFriends} />}
        {value == "scoreBoard" && (
          <MatchHistory matchHistory={statistics.matchHistory} />
        )}
        {value == "achievement" && (
          <TableUser
            rows={createAchievTable()}
            descrStart={"Achievement"}
            descrEnd={"Total"}
          />
        )}
      </div>
    </div>
  );
}
