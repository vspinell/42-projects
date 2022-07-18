import "../../style/Game.css";
import { CircularProgress } from "@mui/material";
import { margin } from "@mui/system";

export default function Matchmaking({ changeMode }) {

  function handleClickBack() {
    changeMode();
  }

  return (

    <>
    <div className="back--button--cont">
      <button className="back--button" onClick={handleClickBack}>
          ↵
      </button> 
    </div>


    <div className="matchWrapper">
      <h1 className="match-title">
        SEARCHING FOR AN OPPONENT!
      </h1>
      <CircularProgress
        style={{
          color:"lightgray",
          alignSelf:"center",
          width:"60px",
          height:"60px",
          marginTop: "20px",
          marginLeft: "-60px"
        }}
      />
    </div>
    </>
  );
}

