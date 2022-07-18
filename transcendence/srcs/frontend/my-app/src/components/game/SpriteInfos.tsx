import * as sprites from "./sprites/images";
import "../../style/Game.css";

export default function SpriteInfos(props) {
  return (
    <div className="rules--wrapper">
      
      <h1 style={{alignSelf:"center", fontWeight:"700"}}>CLASSIC MODE</h1>
      <div className="classic--mode">
        <i className="bi bi-arrow-up-square fa-3x"></i>
        <p>Move up </p>
      </div>
      <div className="classic--mode">
        <i className="bi bi-arrow-down-square fa-3x"></i>
        <p>Move down</p>
      </div>
      <h1 style={{alignSelf:"center", fontWeight:"700"}}>SPECIAL MODE</h1>
      <h3>BONUS</h3>
      <div className="sprite--description">
        <img src={sprites.shorten1} className="rules--sprite" />
        <p>Reduces the size of the opponent's paddle</p>
      </div>
      <div className="sprite--description">
        <img src={sprites.largen1} className="rules--sprite" />
        <p>Increases the size of your paddle</p>
      </div>
      <h3>MALUS</h3>
      <div className="sprite--description">
        <img src={sprites.inverted1} className="rules--sprite" />
        <p>
          Inverts your commmands
        </p>
      </div>
      <div className="sprite--description">
        <img src={sprites.blind1} className="rules--sprite" />
        <p>
          Makes you blind for a short time
        </p>
      </div>
      <h2>SCORE 5 GOALS TO WIN!</h2>
    </div>
  );
}
