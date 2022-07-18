import React, { useContext } from "react";
import { Link } from "react-router-dom";
import LoggedContext from "../context/Logged";
import "../style/NotFound.scss";

const NotFound = () => {
  const { logged } = useContext(LoggedContext);
  const path = logged ? "/home" : "/";

  return (
    <div className="not-found">
      <div className="not-found-body"></div>
      <div className="field">
        <h1 className="first-four">4</h1>
        <div className="net"></div>
        <div className="ping"></div>
        <div className="pong"></div>
        <div className="ball"></div>
        <h1 className="second-four">4</h1>
      </div>
      <h1 className="page-not-found">page not found</h1>
      <div className="go-home">
        <Link to={path} style={{ color: "black" }}>
          Go Home
        </Link>
      </div>
    </div>
  );
};

export default NotFound;
