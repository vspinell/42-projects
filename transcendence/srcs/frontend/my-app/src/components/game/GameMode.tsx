import { useState } from "react";
import SpriteInfos from "./SpriteInfos";
import { useNavigate } from "react-router-dom";

export default function GameMode(props: any) {
  let navigate = useNavigate();
  const [open, setOpen] = useState(false);
  

  function handleClickInfo() {
    setOpen((prevOpen) => !prevOpen);
  }

  function handleClickBack() {
    if (!open)
      navigate("/home");
    else
      setOpen(false);
  }

  return (
    <div className="game--body">


      <div className="back--button--cont">
        <button className="back--button" onClick={handleClickBack}>
          ↵
        </button>
        {!open && <button className="rules--button" onClick={handleClickInfo}>
          RULES
        </button>}
      </div>


      

      {!open ? 
      (<div className="game-choosing-mode">
      <h1>SELECT A GAME MODE</h1>
      <button
        className="game--button"
        onClick={() => props.handleSelectedMode("classic")}
      >
        CLASSIC
      </button>
      <button
        className="game--button"
        onClick={() => props.handleSelectedMode("special")}
      >
        SPECIAL
      </button>
    </div>) : 
      <SpriteInfos />}
    </div>
  )
}
