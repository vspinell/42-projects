import { useContext, useState } from "react";
import {
  Avatar,
  IconButton,
  ListItemIcon,
  Menu,
  MenuItem,
  Tooltip,
} from "@mui/material";
import Button from "@mui/material/Button";
import { styled } from "@mui/material/styles";
import { Logout, Settings } from "@mui/icons-material";
import UserContext from "../../context/User";
import ChatContext from "../../context/Chat";
import LoggedContext from "../../context/Logged";
import PersonIcon from "@mui/icons-material/Person";
import "../../style/Header.css";
import ChatIcon from "./ChatIcon";
import { Link } from "react-router-dom";
import { User_me_type } from "../../types/type";

export default function Header() {
  const { User, setUser } = useContext(UserContext);
  const { setChat } = useContext(ChatContext);
  const { logged, setLogged } = useContext(LoggedContext);
  const [anchorEl, setAnchorEl] = useState(null);
  const open = Boolean(anchorEl);

  type ButtonProps = {
    Lock: boolean;
  };

  const CustButton = styled(Button, {
    shouldForwardProp: (props) => props !== "Lock",
  })<ButtonProps>(({ Lock }) => ({
    opacity: Lock === false ? 0.5 : 1,
    color: "black",
    backgroundColor: "white",
    borderColor: "white",
    marginRight: "2vh",
    borderRadius: "1px",
    [`&:hover`]: {
      color: "black",
      backgroundColor: "#f5c71a",
      opacity: Lock === false ? 0.5 : 1,
      borderColor: "white",
      boxShadow: Lock === false ? "none" : "0px 0px 5px white",
    },
  }));

  const paperProps = {
    elevation: 0,
    sx: {
      overflow: "visible",
      filter: "drop-shadow(0px 2px 8px rgba(0,0,0,0.32))",
      mt: 1.5,
      "& .MuiAvatar-root": {
        width: 32,
        height: 32,
        ml: -0.5,
        mr: 1,
      },
      "&:before": {
        content: '""',
        display: "block",
        position: "absolute",
        top: 0,
        right: "1.5vh",
        width: 10,
        height: 10,
        bgcolor: "background.paper",
        transform: "translateY(-50%) rotate(45deg)",
        zIndex: 0,
      },
    },
  };

  function LoginHandler(): void {
    window.location.href = `${process.env.REACT_APP_REDIRECT_URL}`;
  }

  function refreshPage(): void {
    window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}`;
  }

  function LogoutHandler(): void {
    if (logged)
      fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/auth/logout`,
        {
          credentials: "include",
        }
      ).then((resp) => {
        if (resp.ok)
          setUser((prevUser: User_me_type) => {
            return {
              ...prevUser,
              id: 0,
              login: "",
              image: "",
            };
          });
        setLogged(false);
        setChat(false);
        localStorage.clear();
        refreshPage();
      });
  }

  const handleClick = (event: any) => {
    setAnchorEl(event.currentTarget);
  };
  const handleClose = () => {
    setAnchorEl(null);
  };

  function disableChat(): void {
    setChat(false);
    localStorage.setItem("useChat", "false"); /// PER IL TITOLO TRASCENDENCE
  }

  return (
    <header>
      <Link to="/home" style={{ textDecoration: "none", color: "white" }}>
        <h3 onClick={() => disableChat()} className="title">
          TRANSCENDENCE
        </h3>
      </Link>
      {logged && (
        <div id="UserNameImg">
          <h4 className="user--name overflow">{User.login}</h4>
          <Tooltip title="Account settings">
            <IconButton
              onClick={handleClick}
              size="small"
              sx={{ ml: "2" }}
              aria-controls={open ? "account-menu" : undefined}
              aria-haspopup="true"
              aria-expanded={open ? "true" : undefined}
            >
              <Avatar className="Avatar" alt={User.login} src={User.image} />
            </IconButton>
          </Tooltip>
          <ChatIcon />
          <Menu
            id="account-menu"
            open={open}
            anchorEl={anchorEl}
            onClose={handleClose}
            onClick={handleClose}
            PaperProps={paperProps}
            transformOrigin={{ horizontal: "right", vertical: "top" }}
            anchorOrigin={{ horizontal: "right", vertical: "bottom" }}
          >
            <Link
              to={`${User.login}`}
              style={{ textDecoration: "none", color: "inherit" }}
            >
              <MenuItem>
                <ListItemIcon>
                  <PersonIcon fontSize="small" />
                </ListItemIcon>
                Profile
              </MenuItem>
            </Link>
            <Link
              to="/settings"
              style={{ textDecoration: "none", color: "inherit" }}
            >
              <MenuItem>
                <ListItemIcon>
                  <Settings fontSize="small" />
                </ListItemIcon>
                Settings
              </MenuItem>
            </Link>
            <MenuItem onClick={LogoutHandler}>
              <ListItemIcon>
                <Logout fontSize="small" />
              </ListItemIcon>
              Logout
            </MenuItem>
          </Menu>
        </div>
      )}
    </header>
  );
}
