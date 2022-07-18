import React, { createContext } from "react";
import { Socket, io  } from "socket.io-client";
import { DefaultEventsMap } from "@socket.io/component-emitter";


const SocketContext = createContext<any>(0); // Creo un'oggetto di default da passare ai child. Sará sempre settato con lo State 

export default SocketContext;