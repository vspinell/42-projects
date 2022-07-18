import { useContext } from "react";
import { Link } from "react-router-dom";
import LoggedContext from "../context/Logged";
import "../style/ErrorPage.css";

export default function ErrorPage() {
    const { logged } = useContext(LoggedContext);
  const path = logged ? "/home" : "/";

  return (
    <div className="not-found-e">
      <div className="not-found-body-e">
      </div>
        <h1 className="second-four-e">OPS!</h1>
      <h1 className="page-not-found-e">something went wrong!</h1>
      <div className="go-home-e">
      <Link to={path} style={{color:"black"}} >Go Home</Link>
      </div>
    </div>
  )
}
