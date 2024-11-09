import { useEffect, useContext } from "react";
import LoggedContext from "../context/Logged";
import { useLocation, Navigate, useNavigate, Link } from "react-router-dom";
import Button from "@mui/material/Button";
import { styled } from "@mui/material/styles";
import "../style/Login.css";

export default function Login() {
  const { logged } = useContext(LoggedContext);
  let navigate = useNavigate();

  type ButtonProps = {
    Lock: boolean;
  };
  const CustButton = styled(Button, {
    shouldForwardProp: (props) => props !== "Lock",
  })<ButtonProps>(({ Lock }) => ({
    opacity: Lock === false ? 0.5 : 1,
    color: "white",
    borderColor: "white",
    [`&:hover`]: {
      color: "white",
      opacity: Lock === false ? 0.5 : 1,
      borderColor: "white",
      boxShadow: Lock === false ? "none" : "0px 0px 5px white",
    },
  }));

  // const LoginButton = styled(Button, {
  //   shouldForwardProp: (props) => props !== "Lock",
  // })<ButtonProps>(({ Lock }) => ({
  //   opacity: Lock === false ? 0.5 : 1,
  //   color: "black",
  //   backgroundColor: "white",
  //   borderColor: "white",
  //   // marginRight: "2vh",
  //   borderRadius: "1px",
  //   [`&:hover`]: {
  //     color: "black",
  //     backgroundColor: "#f5c71a",
  //     opacity: Lock === false ? 0.5 : 1,
  //     // borderColor: "white",
  //     boxShadow: Lock === false ? "none" : "0px 0px 5px white",
  //   },
  // }));

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

  async function signUp(): Promise<Promise<void>> {
    try {
      const response = await fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/auth/signUp`,
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({
            login: "koffing",
            password: "qwe",
            email: "koffing@email.it",
          }),
          credentials: "include",
        }
      );
      if (response.ok) {
        const data = await response.json();
        console.log("User signed up successfully:", data);
        window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}/home`;
        // navigate("/home");
      } else if (response.status === 409) {
        // setError("User with this email already exists.");
        console.log("User with this email already exists.");
      } else {
        // setError("An error occurred. Please try again.");
      }
    } catch (error) {
      console.error("Fetch error:", error);
      // setError("An error occurred. Please try again.");
    }
  }

  // function signIn(): void {
  //   window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/auth/signIn?login=koffing&password=qwe`;
  // }

  const signIn = () => {
    navigate("/signin");
  };

  function LoginHandler() {
    window.location.href = `${process.env.REACT_APP_REDIRECT_URL}`;
  }
  return (
    <div className="login--container">
      <div className="title--container">
        <Link to="/home" style={{ textDecoration: "none", color: "white" }}>
          <h1 className="login--title">TRANSCENDENCE</h1>
        </Link>
        {!logged && (
          // <LoginButton
          //   variant="contained"
          //   Lock={true}
          //   className="login--button"
          //   onClick={LoginHandler}
          //   value="Login"
          // >
          //   <div className="button--title">Login</div>
          // </LoginButton>
          <CustButton variant="outlined" Lock={true} className="Button" onClick={signIn}>
            Sign In
          </CustButton>
          // <button className="Button" onClick={signIn}>
          //   Sign in
          // </button>
        )}
        {/* {!logged && (
          <div id="ButtonList">
            <CustButton
              variant="outlined"
              Lock={true}
              className="Button"
              onClick={createfakeUser}
            >
              Fake User
            </CustButton>
          </div>
        )} */}

        {!logged && (
          <div id="ButtonList">
            <CustButton
              variant="outlined"
              Lock={true}
              className="Button"
              onClick={signUp}
            >
              Sign up
            </CustButton>
          </div>
        )}
      </div>
    </div>
  );
}
