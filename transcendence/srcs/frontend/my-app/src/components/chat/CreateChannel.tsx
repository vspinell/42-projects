import { useContext, useEffect, useState } from "react";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import ArrowForwardIcon from "@mui/icons-material/ArrowForward";
import { channel_type } from "../../types/type";
import UserContext from "../../context/User";
import {
  Avatar,
  Checkbox,
  List,
  ListItem,
  ListItemAvatar,
  ListItemButton,
  ListItemText,
} from "@mui/material";
import UploadImage from "../UploadImage";

export default function CreateChannel({ friends, setChatFunction }) {
  const { User } = useContext(UserContext);
  const [newChannel, setNewChannel] = useState<channel_type>({
    name: "",
    image: "",
    type: "public",
    key: "",
    owner: User,
    description: "",
    admins: [],
    users: [],
    banned: [],
    muted: [],
    messages: [],
    notifications: 0,
  });
  const [step, setStep] = useState<number>(0);
  const [checkChannel, setCheckChannel] = useState<boolean>(true);
  const [checked, setChecked] = useState([User]);
  const [selectedImage, setSelectedImage] = useState<string | null>(null);

  const handleToggle = (value) => () => {
    const currentIndex: number = checked.indexOf(value);
    const newChecked = [...checked];
    if (currentIndex === -1) {
      newChecked.push(value);
    } else {
      newChecked.splice(currentIndex, 1);
    }
    setChecked(newChecked);
    setNewChannel((prevState: channel_type) => {
      return {
        ...prevState,
        users: [...newChecked],
      };
    });
  };

  function handleChange(e: any) {
    let { name, value } = e.target;
    if (name == "name") value = value.slice(0, 20);
    setNewChannel((prevState: channel_type) => {
      return {
        ...prevState,
        [name]: value,
      };
    });
  }

  function handleButton(): boolean {
    if (newChannel.type === "protected") {
      if (!newChannel.key || !newChannel.name) return true;
    } else {
      if (!newChannel.name || !checkChannel) return true;
    }
    return false;
  }

  function createChannel(): void {
    const newChannelString: string = JSON.stringify(newChannel);
    let formData = new FormData();
    formData.append("channel", newChannelString);
    formData.append("file", selectedImage as string);

    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/create`,
      {
        method: "POST",
        credentials: "include",
        body: formData,
      }
    );
  }

  function disablecreateChannel(): void {
    setChatFunction("");
  }

  useEffect(() => {
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/channel/channelExist`,
      {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ name: newChannel.name }),
      }
    )
      .then((res) => res.json())
      .then((res) => {
        if (res === false) setCheckChannel(false);
        else setCheckChannel(true);
      });
  }, [newChannel.name]);

  return (
    <div>
      <div
        className="people-list-title"
        style={{
          display: "flex",
          alignItems: "center",
          justifyContent: "space-between",
        }}
      >
        <ArrowBackIcon
          className="ArrowBack"
          onClick={() => {
            if (!step) disablecreateChannel();
            else setStep((prevState) => --prevState);
          }}
        />
      </div>
      {!step && (
        <form>
          <fieldset>
            <legend>Customize your channel</legend>
            <UploadImage
              selectedImage={selectedImage}
              setSelectedImage={setSelectedImage}
              setNewChannel={setNewChannel}
            />
            <label
              style={{
                fontSize: "15px",
                fontWeight: "700",
              }}
            >
              CHANNEL NAME
            </label>
            <input
              className={checkChannel ? `` : "inputfalse"}
              type="text"
              name="name"
              placeholder="awesome_channel"
              onChange={handleChange}
              value={newChannel.name}
              style={{ fontWeight: "500" }}
            />
            {!checkChannel && (
              <span className="errorChannel">Channel name not available</span>
            )}
            <label
              style={{
                fontSize: "15px",
                fontWeight: "700",
              }}
            >
              PRIVACY LEVEL
            </label>
            <select
              name="type"
              className="form-select"
              aria-label="Default select "
              value={newChannel.type}
              onChange={handleChange}
              style={{ fontWeight: "500" }}
            >
              <option value="public">Public - Visible to anyone</option>
              <option value="private">Private - No visible, invite only</option>
              <option value="protected">
                Protected - Visible with password
              </option>
            </select>
            {newChannel.type === "protected" && (
              <>
                <label>Password</label>
                <input
                  type="password"
                  name="key"
                  onChange={handleChange}
                  value={newChannel.key}
                />
              </>
            )}
            <label
              style={{
                fontSize: "15px",
                fontWeight: "700",
              }}
            >
              DESCRIPTION
            </label>
            <textarea
              name="description"
              placeholder="Insert description of the channel here"
              onChange={handleChange}
              value={newChannel.description}
              style={{
                resize: "vertical",
                maxHeight: "80px",
                minHeight: "40px",
                fontWeight: "500",
              }}
            />
            <button
              className="btn btn-primary"
              disabled={handleButton()}
              onClick={(e) => {
                e.preventDefault();
                setStep((prevState) => ++prevState);
              }}
            >
              {" "}
              Next <ArrowForwardIcon style={{ marginRight: "8px" }} />{" "}
            </button>
          </fieldset>
        </form>
      )}
      {step == 1 && (
        <form>
          <fieldset>
            <legend>Add people to {newChannel.name}</legend>
            {/* <label>Add people to {newChannel.name}</label> */}
            <List
              dense
              sx={{ width: "100%", maxWidth: 360, bgcolor: "0, 0, 0, 0.8" }}
            >
              {friends.map((value) => {
                const labelId = `checkbox-list-secondary-label-${value.id}`;
                return (
                  <ListItem
                    key={value.id}
                    secondaryAction={
                      <Checkbox
                        edge="end"
                        onChange={handleToggle(value)}
                        checked={checked.indexOf(value) !== -1}
                        inputProps={{ "aria-labelledby": labelId }}
                        style={{ color: "#f5c71a" }}
                      />
                    }
                    // disablePadding
                  >
                    <ListItemButton className="provola">
                      <ListItemAvatar>
                        <Avatar
                          alt={`Avatar n°${value.id}`}
                          src={value.image}
                        />
                      </ListItemAvatar>
                      <ListItemText id={labelId} primary={value.login} />
                    </ListItemButton>
                  </ListItem>
                );
              })}
            </List>
            <button
              className="btn btn-primary"
              onClick={(e) => {
                e.preventDefault();
                createChannel();
                disablecreateChannel();
              }}
            >
              {" "}
              Next <ArrowForwardIcon style={{ marginRight: "8px" }} />{" "}
            </button>
          </fieldset>
        </form>
      )}
    </div>
  );
}
