import { useContext, useEffect, useState } from "react";
import { useLocation, Navigate, Outlet } from "react-router-dom";
import LoggedContext from "../../context/Logged";

export default function ProtectedTwoFa({
    children,
  }: {
    children: JSX.Element;
  })  {
    const [page, setPage] = useState<JSX.Element>(<></>);
    let location = useLocation();

    useEffect(() => {
        async function fa_me() {
          const res = await fetch(
            `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/2fa/me`,
            {
              credentials: "include",
            }
          );
          const data = await res.json();
          if (data) {
            setPage(children);
          } else setPage(<Navigate to="/ErrorPage" state={{ from: location }} replace />);
        }
        fa_me();
      }, [location]);
      return page;
}
