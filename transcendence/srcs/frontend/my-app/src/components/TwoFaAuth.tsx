import { CircularProgress } from "@mui/material";
import { useEffect, useRef, useState } from "react";
import AuthCode, { AuthCodeRef } from "react-auth-code-input";
import "../style/TwoFaAuth.css";

export default function TwoFaAuth() {
  const [result, setResult] = useState<string>("");

  useEffect(() => {
    if (result.length == 6)
      window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/2fa/validate?code=${result}`;
  }, [result]);

  const handleOnChange = (res: string) => {
    setResult(res);
  };

  return (
    <div className="two-fa">
      <div className="main">
        <div className="body">
          <h1>Two-Factor Authentication</h1>
          <h5 className="subtitle">Please insert your private code</h5>
          <AuthCode
            onChange={handleOnChange}
            containerClassName="container"
            inputClassName="input"
            autoFocus
          />
          <CircularProgress
            style={{ color: `${result.length == 6 ? "black" : "transparent"}` }}
            className="loading-twoFa"
          />
        </div>
      </div>
    </div>
  );
}
