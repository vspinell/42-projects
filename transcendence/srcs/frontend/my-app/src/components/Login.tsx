import { useContext, useState } from "react";
import LoggedContext from "../context/Logged";
import { useNavigate, Link } from "react-router-dom";
import "../style/Login.css";
import "./SignInForm";
import { AuthType } from "../types/type";
import SignInForm from "./SignInForm";

export default function Login() {
  const { logged } = useContext(LoggedContext);
  const [authType, setAuthType] = useState<AuthType | "">(""); // Track which button was clic

  function createfakeUser(): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/fakeusers`,
      {
        credentials: "include",
      }
    ).then(
      () =>
        (window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}/home`)
    );
  }

  const handleAuthType = (auth: AuthType) => {
    setAuthType((prev) => auth);
  };

  console.log(authType);

  return (
    <div className="login--container">
      <Link to="/home" style={{ textDecoration: "none", color: "white" }}>
        <h1 className="login--title">TRANSCENDENCE</h1>
      </Link>
      <div className="login-group">
        <div className="button-group">
          {!logged && <button onClick={() => handleAuthType("signIn")}>Sign In</button>}
          {!logged && <button onClick={() => handleAuthType("signUp")}>Sign Up</button>}
        </div>
        {authType && <SignInForm auth_type={authType} />}
      </div>
    </div>
  );
}
