import {
  Box,
  Button,
  createTheme,
  TextField,
  Theme,
  ThemeProvider,
} from "@mui/material";
import { useSnackbar } from "notistack";
import { useContext, useState } from "react";
import UserContext from "../../context/User";
import { User_me_type } from "../../types/type";

export default function ChangeInfo() {
  const { User, setUser } = useContext(UserContext);
  const [name, setName] = useState<string>(User.login);
  const { enqueueSnackbar } = useSnackbar();

  const theme: Theme = createTheme({
    palette: {
      primary: {
        main: "#000000",
      },
    },
  });

  function checkSave(): boolean {
    if (name == User.login || name == "") return true;
    return false;
  }

  function sendName(): void {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/users/name`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ userId: User.id, name: name }),
      }
    )
      .then((res) => res.json())
      .then((res) => {
        if (!res)
          enqueueSnackbar("Name already used!", {
            variant: "error",
            autoHideDuration: 3000,
          });
        else
          setUser((prev: User_me_type) => {
            return {
              ...prev,
              login: name,
            };
          });
      });
  }

  return (
    <div className="account-settings">
      <ThemeProvider theme={theme}>
        <Box
          component="form"
          sx={{
            "& .MuiTextField-root": { m: 1, width: "25ch" },
          }}
          noValidate
          autoComplete="off"
        >
          {}
          <TextField
            id="standard-required"
            label="Name"
            placeholder={User.login}
            value={name}
            variant="standard"
            onChange={(e) => {
              setName(e.target.value.slice(0, 10));
            }}
            onKeyDown={(e) => {
              if (e.key === "Enter") {
                e.preventDefault();
                sendName();
              }
            }}
          />
        </Box>
        <Button
          sx={{ width: "20%", marginLeft: "1%", marginTop: "5%" }}
          variant="outlined"
          disabled={checkSave()}
          onClick={() => {
            sendName();
          }}
        >
          Save
        </Button>
      </ThemeProvider>
    </div>
  );
}
