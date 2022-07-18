import { Avatar, Stack } from "@mui/material";
import {
  InGameStyledBadge,
  OfflineStyledBadge,
  OnlineStyledBadge,
} from "../../style/chat/styledComponents/styledBadge";

export default function ContactAvatarReversed({ friend, navigate }) {
  function friendAvatar(): JSX.Element {
    switch (friend.status) {
      case "online":
        return (
          <>
            <div className="about">
              <div className="name">{friend.login}</div>
              <div className="status">{friend.status}</div>
            </div>
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
          </>
        );
      case "offline":
        return (
          <>
            <div className="about">
              <div className="name">{friend.login}</div>
              <div className="status">{friend.status}</div>
            </div>
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
          </>
        );
      case "inGame":
        return (
          <>
            <div className="about">
              <div className="name">{friend.login}</div>
              <div className="status">{friend.status}</div>
            </div>
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
          </>
        );
      default:
        return <></>;
    }
  }

  return <>{friendAvatar()}</>;
}
