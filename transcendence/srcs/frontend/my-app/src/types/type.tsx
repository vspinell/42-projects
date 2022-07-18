import { Howler } from "howler";

export type User_type = {
  id: number;
  login: string;
  image: string;
};

export interface User_me_type extends User_type {
  email: string;
  isTwoFactorAuthEnabled: boolean;
  channels: string[];
  friends: User_type[];
}

export interface friend_type extends User_type {
  notifications: number;
  // updatedAt: string | Date;
  request: string;
  status: string;
  messages: message_type[];
}

export type server_response_type = {
  type: string;
  message: string;
  origin: any;
  login: string;
};

export type message_type = {
  sender: number | User_type;
  receiver: number | string;
  text: string;
  serverMessage: boolean;
};

export type chatToggle = {
  privateChatNot: number;
  channelChatNot: number;
  friendshipNotific: number;
};

export type chat_message = {
  id: number;
  senderId: number;
  text: string;
  createdAt: string;
  ad: boolean;
};

export type soundStatus = {
  notification: boolean;
  gameSong: boolean;
  gameEffects: boolean;
};

export type insertPsw = {
  insert: boolean;
  password: string;
  where: string;
};

export type achievement = {
  description: string;
};

export type statisticsType = {
  wins: number;
  winsSpecial: number;
  losses: number;
  lossesSpecial: number;
  ladderLevel: number;
  ladderLevelSpecial: number;
  rank: number;
  rankSpecial: number;
  matchHistory: matchHistory[];
  achievements: achievement[];
};

export type matchHistory = {
  createdAt: string;
  id: number;
  loser: friend_type;
  loserId: number;
  losingScore: number;
  special: boolean;
  winner: friend_type;
  winnerId: number;
  winningScore: number;
};

export interface gameInviteType {
  idSender: number;
  idRecever: number;
  gameMode: "classic" | "special";
  accepted: boolean;
}

export type channel_type = {
  name: string;
  image: string | FormData;
  type: string;
  key: string;
  owner: User_type;
  description: string;
  admins: User_type[];
  users: User_type[];
  banned: number[];
  muted: number[];
  messages: message_type[];
  notifications: number;
};

export interface InviteObj {
  idSender: number;
  idRecever: number;
  gameMode: "classic" | "special";
  accepted: boolean;
}

export type peopleSettings = {
  id: number;
  login: string;
  image: string;
  admin: boolean;
  owner: boolean;
};
export interface Audio {
  notification: Howler;
  bounce: Howler;
  score: Howler;
  gameSong: Howler;
  gameOver: Howler;
}
