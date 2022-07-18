import { useContext, useState } from "react";
import AddCircleIcon from "@mui/icons-material/AddCircle";
import ArrowForwardIcon from "@mui/icons-material/ArrowForward";
import ContactList from "./ContactList";
import PersonAddIcon from "@mui/icons-material/PersonAdd";
import GroupIcon from "@mui/icons-material/Group";
import PersonIcon from "@mui/icons-material/Person";
import "../../style/chat/Chat.css";
import {
  Badge,
  Box,
  createTheme,
  SpeedDial,
  SpeedDialAction,
  Tab,
  Tabs,
  Theme,
  ThemeProvider,
} from "@mui/material";
import PeopleIcon from "@mui/icons-material/People";
import CircleNotificationsIcon from "@mui/icons-material/CircleNotifications";
import {
  StyledBadgeDotReq,
  StyledBadgeMenu,
} from "../../style/chat/styledComponents/styledBadge";
import ChatToggleContext from "../../context/ChatToggle";

export default function ChatHome({
  setChatFunction,
  friends,
  destination,
  setDestination,
  loading,
  pendingFriends,
  channels,
  setChannelFunction,
  chatSelector,
  setChatSelector,
  navigate,
}) {
  const { chatToggle } = useContext(ChatToggleContext);

  const actionsFriends = [
    {
      icon: (
        <StyledBadgeDotReq
          variant="dot"
          invisible={pendingFriends.length > 0 ? false : true}
        >
          <CircleNotificationsIcon />
        </StyledBadgeDotReq>
      ),
      name: "Pending friend requests",
      func: "pendingFriend",
      menu: enableChatFunct,
    },
    {
      icon: <PersonAddIcon />,
      name: "Add friend",
      func: "addFriend",
      menu: enableChatFunct,
    },
  ];

  const actionsChannels = [
    {
      icon: <ArrowForwardIcon />,
      name: "Join channel",
      func: "joinChannel",
      menu: enableChatFunct,
    },
    {
      icon: <AddCircleIcon />,
      name: "Create channel",
      func: "createChannel",
      menu: enableChatFunct,
    },
  ];

  function enableChatFunct(_function: string): void {
    setChatFunction(_function);
  }

  const handleChange = (event, newValue: string) => {
    setChatSelector(newValue);
  };

  function speedDialSel(): JSX.Element {
    if (chatSelector != "friends")
      return <PeopleIcon style={{ fill: "black" }} />;
    else return <PersonIcon style={{ fill: "black" }} />;
  }

  const theme: Theme = createTheme({
    palette: {
      primary: {
        main: "#f5c71a",
      },
      secondary: {
        main: "#ffffff",
      },
    },
  });

  function pendingFriendDial(): number {
    if (chatSelector == "friends") return pendingFriends.length;
    else return 0;
  }

  return (
    <>
      <div
        style={{
          display: "flex",
          justifyContent: "flex-end",
          margin: "0px",
          height: "20px",
        }}
      >
        {destination != 0 && (
          <ArrowForwardIcon
            className="Arrow"
            style={{ fill: "#f5c71a" }}
            onClick={() => setDestination(0)}
          />
        )}
      </div>
      <div className="menu-home">
        <div>
          <ThemeProvider theme={theme}>
            <Box sx={{ marginBottom: "10px" }}>
              <Tabs
                textColor="primary"
                indicatorColor="primary"
                value={chatSelector}
                onChange={handleChange}
                aria-label="scrollable auto tabs example"
                centered
              >
                <Tab
                  icon={
                    <Badge badgeContent={chatToggle.privateChatNot}>
                      <PersonIcon />
                    </Badge>
                  }
                  iconPosition="start"
                  value="friends"
                  sx={{ color: "white" }}
                />
                <Tab
                  icon={
                    <Badge badgeContent={chatToggle.channelChatNot}>
                      <GroupIcon />
                    </Badge>
                  }
                  iconPosition="start"
                  value="channels"
                  sx={{ color: "white" }}
                />
              </Tabs>
            </Box>
          </ThemeProvider>
          <div className="contact-list">
            <ul className="list-unstyled chat-list mt-2 mb-0">
              <ContactList
                friends={friends}
                setDestination={setDestination}
                loading={loading}
                chatSelector={chatSelector}
                channels={channels}
                setChannelFunction={setChannelFunction}
                navigate={navigate}
              />
            </ul>
          </div>
        </div>
        <StyledBadgeMenu color="primary" badgeContent={pendingFriendDial()}>
          <Box sx={{ height: 80, transform: "translateZ(0px)", flexGrow: 1 }}>
            <SpeedDial
              ariaLabel="SpeedDial basic example"
              sx={{ position: "absolute", bottom: 16, right: 16 }}
              icon={speedDialSel()}
              FabProps={{
                sx: {
                  bgcolor: "#f5c71a",
                  "&:hover": {
                    bgcolor: "#c59b06",
                  },
                },
              }}
            >
              {chatSelector == "friends"
                ? actionsFriends.map((action) => (
                    <SpeedDialAction
                      key={action.name}
                      icon={action.icon}
                      tooltipTitle={action.name}
                      onClick={() => action.menu(action.func!)}
                    />
                  ))
                : actionsChannels.map((action) => (
                    <SpeedDialAction
                      key={action.name}
                      icon={action.icon}
                      tooltipTitle={action.name}
                      onClick={() => action.menu(action.func!)}
                    />
                  ))}
            </SpeedDial>
          </Box>
        </StyledBadgeMenu>
      </div>
    </>
  );
}
