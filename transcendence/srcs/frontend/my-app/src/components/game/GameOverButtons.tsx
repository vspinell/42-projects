import { useNavigate } from "react-router-dom";

interface Props {
  socketId: any;
  message: string;
}

export default function GameOverButtons(props: Props) {
  let navigate = useNavigate();

  function handleClickGameOver(id: 0 | 1) {
    if (id === 1) {
      navigate("/home", { replace: true });
      props.socketId.close();
    }
    if (id === 0) window.location.reload();
  }

  return (
    <div className="game--over--wrapper">
      <h1>{props.message}</h1>
      <button
        className="game--button"
        onClick={() => {
          handleClickGameOver(0);
        }}
      >
        PLAY AGAIN
      </button>
      <button
        className="game--button"
        onClick={() => {
          handleClickGameOver(1);
        }}
      >
        BACK HOME
      </button>
    </div>
  );
}
