import { useState, useEffect } from "react";
import "../style/SignInForm.css";
import { AuthType } from "../types/type";
import { Dialog, DialogTitle, DialogContent, DialogActions, Button } from "@mui/material";

type AuthProps = {
  auth_type: AuthType | "";
};

export default function SignInForm({ auth_type }: AuthProps) {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");
  const [error, setError] = useState({ dialog: false, message: "" });

  function reset_error() {
    setError((prev) => {
      return {
        dialog: false,
        message: "",
      };
    });
  }

  function setDialogMsg(msg: string) {
    setError((prev) => {
      return {
        dialog: true,
        message: msg,
      };
    });
  }

  async function signIn(auth: AuthType): Promise<Promise<void>> {
    try {
      let payload: any = {
        login: username,
        password,
      };
      if (auth == "signUp") {
        payload = {
          ...payload,
          email,
        };
      }
      const response = await fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/auth/${auth}`,
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify(payload),
          credentials: "include",
        }
      );
      if (response.ok) {
        const { twoFaStep }: { userId: number; twoFaStep: boolean } =
          await response.json();
        if (twoFaStep === true)
          window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}/twoFactorAuth`;
        else
          window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}/home`;
      } else if (response.status === 409) {
        setDialogMsg(`User username ${username} already exists`);
      } else if (response.status == 404) {
        setDialogMsg(`User not found: ${username}`);
      }
    } catch (error) {
      console.error("Fetch error:", error);
      setDialogMsg("An error occurred. Please try again.");
    }
  }

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    reset_error();

    // Basic form validation
    if (!username || !password || (!email && auth_type == "signUp")) {
      setDialogMsg("Please fill in all fields");
      return;
    }

    try {
      if (auth_type) signIn(auth_type);
    } catch (err) {
      setDialogMsg("Invalid email or password");
    }
  };

  return (
    <div className="signIn--container">
      <form onSubmit={handleSubmit} className="signin-form">
        <div className="form-group">
          <label htmlFor="login">Username</label>
          <input
            type="username"
            id="username"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            placeholder="Insert a user alias"
            required
          />
        </div>
        <div className="form-group">
          <label htmlFor="password">Password</label>
          <input
            type="password"
            id="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            placeholder="********"
            required
          />
        </div>
        <div className="form-group">
          {auth_type == "signUp" && (
            <div>
              <label htmlFor="email">Email</label>
              <input
                type="email"
                id="email"
                value={email}
                onChange={(e) => setEmail(e.target.value)}
                placeholder="you@example.com"
                required
              />
            </div>
          )}
        </div>
        {error.message && <p>{error.message}</p>}
        <div className="flex justify-between">
          <button type="submit" className="signin-btn">
            Submit
          </button>
        </div>
      </form>

      <Dialog open={error.dialog} onClose={() => reset_error()}>
        <DialogTitle>Error</DialogTitle>
        <DialogContent>
          <p>{error.message}</p>
        </DialogContent>
        <DialogActions>
          <Button onClick={() => reset_error()} color="primary">
            Close
          </Button>
        </DialogActions>
      </Dialog>
    </div>
  );
}
