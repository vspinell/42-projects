import React, { createContext } from "react";


const LoggedContext = createContext<any>(false); // Creo un'oggetto di default da passare ai child. Sará sempre settato con lo State 

export default LoggedContext;