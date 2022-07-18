import { useContext, useEffect, useState } from "react";
import { useParams } from "react-router-dom";
import LoggedContext from "../context/Logged";
import ProtectedRoute from "./auth/ProtectedRoute";
import NotFound from "./NotFound";
import UserInfo from "./profile/UserInfo";

export default function CheckUrl() {
  let { url } = useParams();
  const [page, setPage] = useState<JSX.Element>(<></>);
  const [change, setChange] = useState<boolean>(false);
  const { logged, setLogged } = useContext(LoggedContext);

  useEffect(() => {
    fetch(`http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/users/userInfo`, {
      method: "POST",
      credentials: "include",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ url }), 
    })
      .then((res) => res.json())
      .then((res) => {
        if (!res) setPage(<NotFound />);
        else{
          setPage((prev) => {
            if (logged)
              return <UserInfo user={res} change={change} />
            else
              return (
                <ProtectedRoute>
                  <UserInfo user={res}change={change} />
                </ProtectedRoute>
              );
          });
          setChange(prev => !prev)
        }
      });
  }, [url]);

  return page;
}
