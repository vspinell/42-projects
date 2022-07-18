import React, { useState, createContext, useContext, useEffect } from "react";
import ChatContext from "../../context/Chat";

// Create the context
const AuthContext = createContext<any>(null);

export const AuthProvider = ({ children }) => {
  // Using the useState hook to keep track of the value authed (if a
  // user is logged in)
  const { useChat, setChat } = useContext(ChatContext);
  const [authed, setAuthed] = useState<boolean>(false);

  const login = async (): Promise<void> => {
    const result = await fakeAsyncLogin();

    if (result) {

      setAuthed(true);
    }
  };

  const logout = async (): Promise<void> => {
    const result = await fakeAsyncLogout();

    if (result) {
      setAuthed(false);
    }
  };

  /// Mock Async Login API call.
  // TODO: Replace with your actual login API Call code
  const fakeAsyncLogin = async (): Promise<string> => {
    return new Promise((resolve, reject) => {
      setTimeout(() => {
        resolve("Logged In");
      }, 300);
    });
  };

  // Mock Async Logout API call.
  // TODO: Replace with your actual logout API Call code
  const fakeAsyncLogout = async (): Promise<string> => {
    return new Promise((resolve, reject) => {
      setTimeout(() => {
        resolve("The user has successfully logged on the server");
      }, 300);
    });
  };

  return (
    // Using the provider so that ANY component in our application can
    // use the values that we are sending.
    <AuthContext.Provider value={{ authed, setAuthed, login, logout }}>
      {children}
    </AuthContext.Provider>
  );
};

// Finally creating the custom hook
export const useAuth = () => useContext(AuthContext);
