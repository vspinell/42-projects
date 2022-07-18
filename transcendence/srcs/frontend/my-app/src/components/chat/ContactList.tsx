import Contact from "./Contact";
import { CircularProgress } from "@mui/material";
import { yellow } from "@mui/material/colors";
import { channel_type } from "../../types/type";
import Channel from "./Channel";

export default function ContactList({
  friends,
  setDestination,
  loading,
  chatSelector,
  channels,
  setChannelFunction,
  navigate
}) {
 

  let contactElements: JSX.Element[] | JSX.Element = friends.map((friend) => {
    return (
      <Contact
        key={friend.id}
        friend={friend}
        setDestination={setDestination}
        setChannelFunction={setChannelFunction}
        navigate={navigate}
      />
    );
  });
  if (!contactElements[0]){
    contactElements = (
      <h5
        style={{
          textAlign: "center",
          color: "white",
          marginTop: "40px",
          whiteSpace: "pre-line",
          fontSize: "20px",
        }}
      >
        You don't have friends <br />
        &#128546;
      </h5>
    );
  }

  let channelElements: JSX.Element[] | JSX.Element = channels.map((channel: channel_type) => {
    return (
      <Channel
        key={channel.name}
        channel={channel}
        setDestination={setDestination}
        setChannelFunction={setChannelFunction}
      />
    );
  });
  if (!channelElements[0]){
    channelElements = (
      <h5
        style={{
          textAlign: "center",
          color: "white",
          marginTop: "40px",
          whiteSpace: "pre-line",
        }}
      >
        You don't have channels <br />
        &#128546;
      </h5>
    );
  }

  function loadingContacts(): JSX.Element | JSX.Element[] {
    switch (loading) {
      case "fetch":
        return (
          <div style={{ height: "300px" }}>
            <CircularProgress
              sx={{
                color: yellow[500],
                marginLeft: "150px",
                marginTop: "100px",
                overflow: "hidden",
              }}
            />
          </div>
        );
      case "idle":
        if(chatSelector == "friends")
          return contactElements;
        return channelElements;
      default:
        return <></>
    }
  }

  return <div>{loadingContacts()}</div>;
}
