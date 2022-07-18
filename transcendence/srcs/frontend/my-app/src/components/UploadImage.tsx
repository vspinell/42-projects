import { Avatar, Badge, IconButton } from "@mui/material";
import React, { useEffect, useState } from "react";
import GroupIcon from "@mui/icons-material/Group";
import EditIcon from "@mui/icons-material/Edit";
import Input from "@mui/material/Input";
import "../style/chat/UploadImage.css";

export default function UploadAndDisplayImage({
  selectedImage,
  setSelectedImage,
  setNewChannel,
}) {
  const hiddenFileInput = React.useRef<any>(null);
  // https://dev.to/przpiw/file-upload-with-react-nodejs-2ho7
  // https://wanago.io/2021/11/08/api-nestjs-uploading-files-to-server/
  const [image2, setImage2] = useState<any>(null);

  const [image, setImage] = useState({ preview: "", data: "" });

  function testImg(image) {
    let formData = new FormData()
    formData.append('file', image.data)
    fetch(
      `http://${process.env.REACT_APP_IP_SERVER}:${process.env.REACT_APP_BACKEND_PORT}/api/users/imageFront`,
      {
        method: "POST",
        credentials: "include",
        body: formData,
      }).then(res => res.blob()).then(res => setImage2(URL.createObjectURL(res)))
  }


  return (
    <div className="uploaded-image">
      <div>
        <Badge
          anchorOrigin={{
            vertical: "bottom",
            horizontal: "right",
          }}
          badgeContent={
            <IconButton
              className="icon-button"
              onClick={() => {
                hiddenFileInput.current.click()!;
              }}
            >
              <EditIcon />
            </IconButton>
          }
        >
          {selectedImage == null ? (
            <>
              <Avatar style={{ height: "100px", width: "100px" }}>
                <GroupIcon style={{ height: "50px", width: "50px" }} />
              </Avatar>
            </>
          ) : (
            <Avatar
              style={{ height: "100px", width: "100px" }}
              alt={"uploaded"}
              src={URL.createObjectURL(selectedImage)}
            />
          )}
        </Badge>
      </div>
      <input
        type="file"
        ref={hiddenFileInput}
        style={{ display: "none" }}
        onChange={(e: any) => {
          const img = {
            preview: URL.createObjectURL(e.target.files[0]),
            data: e.target.files[0],
          };
          // setImage(img);
          setNewChannel((prevState) => {
            return {
              ...prevState,
              image: URL.createObjectURL(e.target.files[0]),
            };
          });
          setSelectedImage(e.target.files[0]);
          e.target.value = null;
        }}
      />
      {/* <Stack direction="row" spacing={2}> */}

      {/* </Stack> */}
      {/* <Button variant="contained" component="label">
        Upload File
        <input type="file" hidden />
      </Button> */}
      {/* <input
        type="file"
        name="myImage"
        className="input-upload"
        onChange={(e: any) => {
          const img = {
            preview: URL.createObjectURL(e.target.files[0]),
            data: e.target.files[0],
          };
          setImage(img);
          setNewChannel((prevState) => {
            return {
              ...prevState,
              image: URL.createObjectURL(e.target.files[0]),
            };
          });
          setSelectedImage(e.target.files[0]);
          e.target.value = null;
        }}
      /> */}
    </div>
  );
}
