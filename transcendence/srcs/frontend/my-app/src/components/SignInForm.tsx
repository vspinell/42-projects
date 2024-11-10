import { useState, useEffect } from "react";
import "../style/SignInForm.css";
import { AuthType } from "../types/type";

type AuthProps = {
  auth_type: AuthType | "";
};

export default function SignInForm({ auth_type }: AuthProps) {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");
  const [error, setError] = useState("");

  async function signIn(auth: AuthType): Promise<Promise<void>> {
    try {
      let payload: any = {
        login: "koffing",
        password: "qwe",
      };
      if (auth == "signUp") {
        payload = {
          ...payload,
          email: "koffing@email.it",
        };
      }
      console.log(payload);
      console.log(auth);
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
        // console.log("User signed up successfully:", data);
        if (twoFaStep === true)
          window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}/twoFactorAuth`;
        else
          window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}/home`;
      } else if (response.status === 409) {
        // setError("User with this email already exists.");
        console.log("User with this email already exists.");
      }
    } catch (error) {
      console.error("Fetch error:", error);
      setError("An error occurred. Please try again.");
    }
  }

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setError("");

    // Basic form validation
    if (!username || !password || (!email && auth_type == "signUp")) {
      setError("Please fill in all fields");
      return;
    }

    try {
      console.log("Logging in with", { email, password });
      if (auth_type) signIn(auth_type);
      alert("Signed in successfully!");
    } catch (err) {
      setError("Invalid email or password");
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
        {error && <p className="text-red-500 text-sm">{error}</p>}
        <div className="flex justify-between">
          <button type="submit" className="signin-btn">
            Submit
          </button>
        </div>
      </form>
    </div>
  );
}
