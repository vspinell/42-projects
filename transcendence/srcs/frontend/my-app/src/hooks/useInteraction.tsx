import { useEffect, useState } from 'react';

const events = ["click"];

export default function useInteraction() {
  const [ready, setReady] = useState<boolean>(false);

  const listener = () => {
    if (ready === false) {
      setReady(true);
    }
  };

  useEffect(() => {
    events.forEach((event) => {
      document.addEventListener(event, listener);
    });

    return () => {
      events.forEach((event) => {
        document.removeEventListener(event, listener);
      });   
    };
  }, []);

  return ready;
}