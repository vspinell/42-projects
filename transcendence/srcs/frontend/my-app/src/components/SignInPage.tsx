import React, { useState } from "react";

export default function SignIn() {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [email, setEmail] = useState("");
  const [error, setError] = useState("");
  const [authType, setAuthType] = useState<"signIn" | "signUp" | null>(null); // Track which button was clicked

  async function signIn(): Promise<Promise<void>> {
    try {
      const response = await fetch(
        `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/auth/${authType}`,
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
        const { twoFaStep }: { userId: number; twoFaStep: boolean } =
          await response.json();
        // console.log("User signed up successfully:", data);
        if (twoFaStep === true)
          window.location.href = `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_FRONTEND_PORT}/twoFactorAuth`;
        else
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
  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setError("");

    // Basic form validation
    if (!email || !password) {
      setError("Please fill in all fields");
      return;
    }

    // Here, you would send the data to the backend for authentication
    // For example: const response = await api.post('/auth/signin', { email, password });

    try {
      // Mock authentication response
      console.log("Logging in with", { email, password });
      signIn();
      alert("Signed in successfully!");
    } catch (err) {
      setError("Invalid email or password");
    }
  };

  return (
    <div className="flex justify-center items-center h-screen bg-gray-100">
      <div className="w-full max-w-lg p-9 bg-white rounded shadow-md">
        <h2 className="text-2xl font-bold text-center mb-6">Sign In</h2>
        <form onSubmit={handleSubmit} className="space-y-4">
          <div>
            <label htmlFor="login" className="block text-sm font-medium text-gray-700">
              username
            </label>
            <input
              type="username"
              id="username"
              value={username}
              onChange={(e) => setUsername(e.target.value)}
              className="mt-1 block w-full px-3 py-2 border rounded-md shadow-sm focus:outline-none focus:ring focus:ring-blue-500 focus:border-blue-500"
              placeholder="Insert a user alias"
              required
            />
            <label htmlFor="password" className="block text-sm font-medium text-gray-700">
              Password
            </label>
            <input
              type="password"
              id="password"
              value={password}
              onChange={(e) => setPassword(e.target.value)}
              className="mt-1 block w-full px-3 py-2 border rounded-md shadow-sm focus:outline-none focus:ring focus:ring-blue-500 focus:border-blue-500"
              placeholder="********"
              required
            />
            <div>
              <label htmlFor="email" className="block text-sm font-medium text-gray-700">
                Email
              </label>
              <input
                type="email"
                id="email"
                value={email}
                onChange={(e) => setEmail(e.target.value)}
                className="mt-1 block w-full px-3 py-2 border rounded-md shadow-sm focus:outline-none focus:ring focus:ring-blue-500 focus:border-blue-500"
                placeholder="you@example.com"
                required
              />
            </div>
          </div>
          {error && <p className="text-red-500 text-sm">{error}</p>}
          <div className="flex justify-between">
            <button
              type="submit"
              onClick={() => setAuthType("signIn")}
              className="w-full py-2 px-4 bg-blue-600 hover:bg-blue-900 text-white rounded-md font-semibold transition duration-300"
            >
              Sign In
            </button>
            <button
              type="submit"
              onClick={() => setAuthType("signUp")}
              className=" py-2 px-4 bg-blue-600 hover:bg-yellow-300 text-white rounded-md font-semibold transition duration-300"
            >
              Sign Up
            </button>
          </div>
        </form>
      </div>
    </div>
  );
}
