import { useContext, useEffect, useState } from "react";
import { useLocation, Navigate, Outlet } from "react-router-dom";
import LoggedContext from "../../context/Logged";
import WatchContext from "../../context/WatchGame";

export default function WatchModeProtected({
  children,
}: {
  children: JSX.Element;
}) {
  const [page, setPage] = useState<JSX.Element>(<></>);
  const { watchMode, setWatchMode } = useContext(WatchContext);
  let location = useLocation();

  useEffect(() => {
    async function getUser() {
      const res = await fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/users/me`,
        {
          credentials: "include",
        }
      );
      const data = await res.json();
      if (data && watchMode.mode) {
        setPage(children);
      } else if (data)
        setPage(<Navigate to="/home" state={{ from: location }} replace />);
      else setPage(<Navigate to="/" state={{ from: location }} replace />);
    }
    getUser();
  }, [location]);
  return page;
}
