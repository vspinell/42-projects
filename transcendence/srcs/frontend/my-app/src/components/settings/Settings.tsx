import React, { useContext, useRef, useState } from "react";
import "../../style/UserInfo.css";
import {
  Avatar,
  Badge,
  Box,
  createTheme,
  Divider,
  IconButton,
  List,
  ListItem,
  ListItemButton,
  ListItemIcon,
  ListItemText,
  Theme,
  ThemeProvider,
} from "@mui/material";
import UserContext from "../../context/User";
import QrCode2Icon from "@mui/icons-material/QrCode2";
import AccountCircleIcon from "@mui/icons-material/AccountCircle";
import EditIcon from "@mui/icons-material/Edit";
import ChangeInfo from "./ChangeInfo";
import NotificationsIcon from "@mui/icons-material/Notifications";
import SetDoubleAuth from "./SetDoubleAuth";
import Sounds from "./Sounds";

export default function UserInfo() {
  const { User, setUser } = useContext(UserContext);
  const [selectedIndex, setSelectedIndex] = useState(0);
  const hiddenFileInput = useRef<any>(null);
  const [image, setImage] = useState<string>(User.image);

  const handleListItemClick = (
    event: React.MouseEvent<HTMLDivElement, MouseEvent>,
    index: number
  ) => {
    setSelectedIndex(index);
  };

  const theme: Theme = createTheme({
    palette: {
      primary: {
        main: "#feae00",
      },
    },
  });

  function switchSettings(): JSX.Element {
    switch (selectedIndex) {
      case 0:
        return <ChangeInfo />;
      case 1:
        return <SetDoubleAuth />;
      case 2:
        return <Sounds />;
      default:
        return <></>;
    }
  }

  return (
    <div className="user-info">
      <div className="settings-body">
        <div className="user-info-header">
          <Badge
            anchorOrigin={{
              vertical: "bottom",
              horizontal: "right",
            }}
            badgeContent={
              <IconButton
                className="icon-button"
                onClick={() => {
                  hiddenFileInput.current.click()!;
                }}
              >
                <EditIcon />
              </IconButton>
            }
          >
            <Avatar
              style={{ height: "150px", width: "150px" }}
              alt={User.login}
              src={User.image}
            />
          </Badge>
          <input
            type="file"
            ref={hiddenFileInput}
            style={{ display: "none" }}
            onChange={(e: any) => {
              let formData = new FormData();
              const userId = JSON.stringify(User.id);
              formData.append("userId", userId);
              formData.append("file", e.target.files[0]!);
              setUser((prev) => {
                return {
                  ...prev,
                  image: URL.createObjectURL(e.target.files[0]),
                };
              });
              fetch(
                `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/users/image`,
                {
                  method: "POST",
                  credentials: "include",
                  body: formData,
                }
              );
              setImage((prev) => URL.createObjectURL(e.target.files[0]));
              e.target.value = null;
            }}
          />
          <div className="user-description">
            <h1>{User.login}</h1>
          </div>
        </div>
        <div className="settings-menu">
          <ThemeProvider theme={theme}>
            <Box
              sx={{
                minWidth: "25%",
                maxWidth: 360,
              }}
            >
              <List className="overflow" disablePadding>
                <ListItem disablePadding>
                  <ListItemButton
                    selected={selectedIndex === 0}
                    onClick={(event) => handleListItemClick(event, 0)}
                  >
                    <ListItemIcon>
                      <AccountCircleIcon />
                    </ListItemIcon>
                    <ListItemText primary="Account" />
                  </ListItemButton>
                </ListItem>
                <Divider />
                <ListItem disablePadding>
                  <ListItemButton
                    selected={selectedIndex === 1}
                    onClick={(event) => handleListItemClick(event, 1)}
                  >
                    <ListItemIcon>
                      <QrCode2Icon />
                    </ListItemIcon>
                    <ListItemText primary="Authentication" />
                  </ListItemButton>
                </ListItem>
                <Divider />
                <ListItem disablePadding>
                  <ListItemButton
                    selected={selectedIndex === 2}
                    onClick={(event) => handleListItemClick(event, 2)}
                  >
                    <ListItemIcon>
                      <NotificationsIcon />
                    </ListItemIcon>
                    <ListItemText primary="Sounds" />
                  </ListItemButton>
                </ListItem>
                <Divider />
              </List>
            </Box>
          </ThemeProvider>
          <Box
            sx={{
              minWidth: "75%",
              borderLeft: "0.5px black solid",
            }}
          >
            <div>{switchSettings()}</div>
          </Box>
        </div>
      </div>
    </div>
  );
}
