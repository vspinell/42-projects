import { Avatar, Stack } from "@mui/material";
import {
  InGameStyledBadge,
  OfflineStyledBadge,
  OnlineStyledBadge,
} from "../../style/chat/styledComponents/styledBadge";

export default function ContactAvatar({ friend, navigate }) {
  
  function friendAvatar(): JSX.Element {
    switch (friend.status) {
      case "online":
        return (
          <>
            <Stack direction="row" spacing={2}>
              <OnlineStyledBadge
                overlap="circular"
                anchorOrigin={{ vertical: "bottom", horizontal: "right" }}
                variant="dot"
              >
                <Avatar
                  alt={friend.login}
                  src={friend.image}
                  onClick={(e) => {
                    e.stopPropagation();
                    navigate(`/${friend.login}`);
                  }}
                />
              </OnlineStyledBadge>
            </Stack>
            <div className="about">
              <div className="name">{friend.login}</div>
              <div className="status">{friend.status}</div>
            </div>
          </>
        );
      case "offline":
        return (
          <>
            <Stack direction="row" spacing={2}>
              <OfflineStyledBadge
                overlap="circular"
                anchorOrigin={{ vertical: "bottom", horizontal: "right" }}
                variant="dot"
              >
                <Avatar
                  alt={friend.login}
                  src={friend.image}
                  onClick={(e) => {
                    e.stopPropagation();
                    navigate(`/${friend.login}`);
                  }}
                />
              </OfflineStyledBadge>
            </Stack>
            <div className="about">
              <div className="name">{friend.login}</div>
              <div className="status">{friend.status}</div>
            </div>
          </>
        );
      case "in game":
        return (
          <>
            <Stack direction="row" spacing={2}>
              <InGameStyledBadge
                overlap="circular"
                anchorOrigin={{ vertical: "bottom", horizontal: "right" }}
                variant="dot"
              >
                <Avatar
                  alt={friend.login}
                  src={friend.image}
                  onClick={(e) => {
                    e.stopPropagation();
                    navigate(`/${friend.login}`);
                  }}
                />
              </InGameStyledBadge>
            </Stack>
            <div className="about">
              <div className="name">{friend.login}</div>
              <div className="status">{friend.status}</div>
            </div>
          </>
        );
        default:
          return <></>
    }
  }

  return <>{friendAvatar()}</>;
}
