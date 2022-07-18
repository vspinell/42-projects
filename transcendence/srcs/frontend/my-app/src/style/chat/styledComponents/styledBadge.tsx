import { Badge, styled } from "@mui/material";

export const StyledBadge = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "#f5c71a",
    color: "rgba(0, 0, 0, 0.8)",
  },
}));

export const StyledBadgeNegative = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "rgba(0, 0, 0, 0.8)",
    color: "#f5c71a",
  },
}));

export const StyledBadgeDot = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "red",
    color: "rgba(0, 0, 0, 0.8)",
    position: "absolute",
    top: 11,
    right: 12,
  },
}));

export const StyledBadgeDotHeader = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "red",
    color: "rgba(0, 0, 0, 0.8)",
    position: "absolute",
    top: 26,
    right: 12,
  },
}));

export const StyledBadgeMenu = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "red",
    color: "rgba(0, 0, 0, 0.8)",
    position: "absolute",
    top: 18,
    right: 25,
  },
}));

export const StyledBadgeDotReq = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-dot": {
    backgroundColor: "red",
    color: "rgba(0, 0, 0, 0.8)",
    position: "absolute",
    top: 5,
    right: 2,
  },
}));

export const OnlineStyledBadge = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "#44b700",
    color: "#44b700",
    boxShadow: `0 0 0 0.5px rgba(0, 0, 0, 0.8)`,
    position: "relative",
    top: "25px",
    right: "12px",
    "&::after": {
      position: "absolute",
      top: 0,
      left: 0,
      width: "100%",
      height: "100%",
      borderRadius: "50%",
      animation: "ripple 1.2s infinite ease-in-out",
      border: "1px solid currentColor",
      content: '""',
    },
  },
  "@keyframes ripple": {
    "0%": {
      transform: "scale(.8)",
      opacity: 1,
    },
    "100%": {
      transform: "scale(2.4)",
      opacity: 0,
    },
  },
}));

export const OfflineStyledBadge = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "#ed3131cc",
    color: "#ed3131cc",
    boxShadow: `0 0 0 0.5px rgba(0, 0, 0, 0.8)`,
    position: "relative",
    top: "25px",
    right: "12px",
    "&::after": {
      position: "absolute",
      top: 0,
      left: 0,
      width: "100%",
      height: "100%",
      borderRadius: "50%",
      border: "1px solid currentColor",
      content: '""',
    },
  },
}));

export const InGameStyledBadge = styled(Badge)(({ theme }) => ({
  "& .MuiBadge-badge": {
    backgroundColor: "#4178dfcc",
    color: "#4178dfcc",
    boxShadow: `0 0 0 0.5px rgba(0, 0, 0, 0.8)`,
    position: "relative",
    top: "25px",
    right: "12px",
    "&::after": {
      position: "absolute",
      top: 0,
      left: 0,
      width: "100%",
      height: "100%",
      borderRadius: "50%",
      animation: "ripple 1.2s infinite ease-in-out",
      border: "1px solid currentColor",
      content: '""',
    },
  },
}));
