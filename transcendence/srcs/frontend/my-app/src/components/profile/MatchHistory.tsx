import { NavigateFunction, useNavigate } from "react-router-dom";
import ContactAvatar from "../chat/ContactAvatar";
import "../../style/chat/Chat.css";
import "../../style/chat/Contact.css";
import "../../style/FriendsUser.css";
import ContactAvatarReversed from "./ContactAvatarReversed";
import { matchHistory } from "../../types/type";

export default function MatchHistory({ matchHistory }) {
  const navigate: NavigateFunction = useNavigate();

  let matches: JSX.Element[] = matchHistory.map((match: matchHistory) => {
    return (
      <div
        className="friend-list friends-user"
        key={`${match.id}-usrlist`}
      >
        <li className="clearfix score-board">
          <ContactAvatar friend={match.winner} navigate={navigate} />
            {match.winningScore} - {match.losingScore}
          <ContactAvatarReversed friend={match.loser} navigate={navigate} />
        </li>
      </div>
    );
  });

  return <div className="friends-container">{matches}</div>;
}
