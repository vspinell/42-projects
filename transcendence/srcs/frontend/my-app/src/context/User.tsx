import React, { createContext } from "react";


const UserContext = createContext<any>({  // Creo un'oggetto di default da passare ai child. Sará sempre settato con lo State 
    id: 0,
    login: "",
    image: ""
  });

export default UserContext;