import {
  Button,
  createTheme,
  FormControlLabel,
  Switch,
  Theme,
  ThemeProvider,
} from "@mui/material";
import React, { useContext, useEffect, useState } from "react";
import UserContext from "../../context/User";
import { useNavigate } from "react-router-dom";
import SoundsStatusContext from "../../context/SoundsStatus";
import { Howl, Howler } from "howler";
import { audio } from "../App";
import { soundStatus } from "../../types/type";

export default function Sounds() {
  const { soundStatus, setSoundStatus } = useContext(SoundsStatusContext);

  const theme: Theme = createTheme({
    palette: {
      primary: {
        main: "#000000",
      },
    },
  });

  const handleChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    if (event.target.name == "notification")
      (audio.notification as Howler).volume(Number(event.target.checked));
    else if (event.target.name == "gameSong") {
      let volume = event.target.checked ? 0.4 : 0;
      (audio.gameSong as Howler).volume(volume);
    } else if (event.target.name == "gameEffects") {
      let volume = event.target.checked ? 1 : 0;
      (audio.score as Howler).volume(volume);
      (audio.bounce as Howler).volume(volume);
      (audio.gameOver as Howler).volume(volume);
    }

    setSoundStatus((prev: soundStatus) => {
      return {
        ...prev,
        [event.target.name]: event.target.checked,
      };
    });
  };

  return (
    <div>
      <ThemeProvider theme={theme}>
        <div className="settings-twofa">
          <FormControlLabel
            className="settings-twofa-switch"
            label="Notifications"
            control={
              <Switch
                name="notification"
                checked={soundStatus.notification}
                onChange={(e) => handleChange(e)}
                inputProps={{ "aria-label": "controlled" }}
              />
            }
          />
          <FormControlLabel
            className="settings-twofa-switch"
            label="Game soundtrack"
            control={
              <Switch
                name="gameSong"
                checked={soundStatus.gameSong}
                onChange={(e) => handleChange(e)}
                inputProps={{ "aria-label": "controlled" }}
              />
            }
          />
          <FormControlLabel
            className="settings-twofa-switch"
            label="Game effects"
            control={
              <Switch
                name="gameEffects"
                checked={soundStatus.gameEffects}
                onChange={(e) => handleChange(e)}
                inputProps={{ "aria-label": "controlled" }}
              />
            }
          />
        </div>
      </ThemeProvider>
    </div>
  );
}
