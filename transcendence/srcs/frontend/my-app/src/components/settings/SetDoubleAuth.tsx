import {
  Button,
  CircularProgress,
  createTheme,
  FormControlLabel,
  Switch,
  Theme,
  ThemeProvider,
} from "@mui/material";
import React, { useContext, useEffect, useState } from "react";
import UserContext from "../../context/User";
import { useNavigate } from "react-router-dom";
import AuthCode from "react-auth-code-input";
import { User_me_type } from "../../types/type";

export default function SetDoubleAuth() {
  const { User, setUser } = useContext(UserContext);
  const [qrCode, setQrCode] = useState<string>("");
  const [insertCode, setInsertCode] = useState<boolean>(false);
  const [checked, setChecked] = useState<boolean>(User.isTwoFactorAuthEnabled);
  const [result, setResult] = useState<string>("");

  useEffect(() => {
    if (User.isTwoFactorAuthEnabled)
      fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/2fa/qrcode`,
        {
          credentials: "include",
        }
      )
        .then((res) => res.blob())
        .then((blob) => setQrCode(URL.createObjectURL(blob)));
    else if (!User.isTwoFactorAuthEnabled && result.length == 6) {
      window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/2fa/turnOn?code=${result}`;
    }
  }, [result]);

  const handleOnChange = (res: string) => {
    setResult(res);
  };

  function generateTwoFa(): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/2fa/generate`,
      {
        method: "POST",
        credentials: "include",
      }
    )
      .then((res) => res.blob())
      .then((blob) => {
        setQrCode(URL.createObjectURL(blob));
      });
  }

  const theme: Theme = createTheme({
    palette: {
      primary: {
        main: "#000000",
      },
    },
  });

  const handleChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setChecked(event.target.checked);
    if (event.target.checked == true) generateTwoFa();
    else {
      fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/2fa/turnOff`,
        {
          method: "POST",
          credentials: "include",
        }
      );
      setUser((prev: User_me_type) => {
        return {
          ...prev,
          isTwoFactorAuthEnabled: false,
        };
      });
      setInsertCode((prev) => false);
    }
  };

  return (
    <div>
      <ThemeProvider theme={theme}>
        <div className="settings-twofa">
          <FormControlLabel
            className="settings-twofa-switch"
            label="Enable Two Factor Authentication (2FA)"
            control={
              <Switch
                checked={checked}
                onChange={handleChange}
                inputProps={{ "aria-label": "controlled" }}
              />
            }
          />
          {checked && qrCode != "" && !insertCode && (
            <>
              <div className="settings-twofa-image-descrip">
                <img
                  className="settings-twofa-image"
                  width="200"
                  height="200"
                  src={qrCode}
                  alt="qrCode"
                />
                <code>
                  Two-factor authentication (2FA) is one of the best and easiest
                  ways to keep your online accounts secure. It works by issuing
                  an authentication code on your phone when somebody tries to
                  access the account; if that person doesn’t have the code, they
                  (or you) don’t get in. By using a 2FA app to save this code,
                  such as Google Authenticator or Authy, you can prevent
                  somebody from accessing your data by getting your password.
                  <br />
                  <br />
                </code>
              </div>
              {!User.isTwoFactorAuthEnabled && (
                <Button
                  className="settings-twofa-button"
                  variant="contained"
                  onClick={() => setInsertCode((prev) => true)}
                >
                  NEXT
                </Button>
              )}
            </>
          )}
          {insertCode && (
            <>
              <h5 className="two-fa-title-sett">
                Please insert your private code
              </h5>
              <AuthCode
                onChange={handleOnChange}
                containerClassName="container"
                inputClassName="input"
                autoFocus
              />
              <CircularProgress
                style={{
                  color: `${result.length == 6 ? "black" : "transparent"}`,
                }}
                className="loading-twoFa-set"
              />
            </>
          )}
        </div>
      </ThemeProvider>
    </div>
  );
}
