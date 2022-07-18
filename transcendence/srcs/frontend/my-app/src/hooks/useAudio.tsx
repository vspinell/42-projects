import { Howl, Howler } from "howler";
import { useEffect, useRef } from "react";

import useInteraction from "./useInteraction";

export default function useAudio(setLoadedAudio) {
  const hasInteracted = useInteraction();
  const notificRef: any = useRef();

  useEffect(() => {
    if (!hasInteracted) {
      return;
    }
    let audio = {
      notification: new Howl({
        src: [require("../sounds/notific.mp3")],
        format: ["mp3"],
        onload() {
          setLoadedAudio(true);
        },
      }),
      bounce: new Howl({
        src: [require("../sounds/paddle.mp3")],
        format: ["mp3"],
      }),
      score: new Howl({
        src: [require("../sounds/score.mp3")],
        format: ["mp3"],
      }),
      gameSong: new Howl({
        src: [require("../sounds/gameSong.mp3")],
        format: ["mp3"],
        loop: true
      }),
      gameOver: new Howl({
        src: [require("../sounds/gameOver1.mp3")],
        format: ["mp3"],
      }),
    };
    notificRef.current = audio;
  }, [hasInteracted]);
  return notificRef.current;
}
