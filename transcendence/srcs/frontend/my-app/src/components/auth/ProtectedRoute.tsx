import { useContext, useEffect, useState } from "react";
import { useLocation, Navigate, Outlet } from "react-router-dom";
import LoggedContext from "../../context/Logged";

export default function ProtectedRoute({
  children,
}: {
  children: JSX.Element;
}) {
  const [page, setPage] = useState<JSX.Element>(<></>);
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
      if (data) {
        setPage(children);
      } else setPage(<Navigate to="/" state={{ from: location }} replace />);
    }
    getUser();
  }, [location]);
  return page;
}
