import { Injectable } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import {
	OnGatewayConnection,
	OnGatewayDisconnect,
	SubscribeMessage,
	WebSocketGateway,
	WebSocketServer,
} from '@nestjs/websockets';
import { GameService } from './game.service';
import {
	FrameToRender,
	RoomFromClient,
	Rooms,
	User,
} from './interfaces/game.interfaces';
import { MatchService } from './match.service';

const FRAME_PER_SECOND = 1000 / 57;

@WebSocketGateway({
	cors: {
		origin: '*',
	},
	namespace: '/game',
})
@Injectable()
export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect {
	constructor(private readonly game: GameService, private database: MatchService) {}

	private room: RoomFromClient = {};
	private rooms: Rooms = {};

	@WebSocketServer() server: Server;
	handleConnection(client: Socket): void {
		const clientId = client.id;
	}

	handleDisconnect(client: Socket): void {
		const roomName = this.room[client.id];
		const winNum = roomName === client.id ? 1 : 0;
		this.handleGameOver(roomName, winNum);
	}

	@SubscribeMessage('watchGame')
	handleWatchGame(client: Socket, idToWatch: number) {
		const roomName = this.findRoom(idToWatch);
		if (roomName) {
			client.join(roomName);
			client.emit('playerNum', this.rooms[roomName].users);
		}
	}

	@SubscribeMessage('joinGame')
	handleInitGame(client: Socket, user: User): any {
		let lastRoomKey: string;
		this.database.updateInGameState(user.id);
		if (!user.friendlyMatch) {
			let allRooms: string[] = Object.keys(this.rooms);
			let availableRooms: string[] = allRooms.filter(
				(singleRoom) =>
					!this.rooms[singleRoom].users[1] &&
					this.rooms[singleRoom].users[0].special === user.special,
			);
			lastRoomKey = availableRooms[0];
		}
		//crea stanza se non esistono stanze o se l'ultima stanza è piena
		if (
			(!lastRoomKey && !user.friendlyMatch) ||
			(user.friendlyMatch && !this.findRoom(user.idFriend))
		) {
			this.room[client.id] = client.id; //assegno id del primo client ad entrare nella stanza al nome della stanza
			this.createGame(client, user);
			// ogni client joina automaticamente in una room con il suo id
		} else {
			if (user.friendlyMatch) lastRoomKey = this.findRoom(user.idFriend);
			this.room[client.id] = lastRoomKey; // assegno al nuovo id, la key(id primo giocatore) come nome stanza
			client.data.number = 1;
			client.join(lastRoomKey); // joino l ultima stanza
			this.rooms[lastRoomKey].users[1] = { ...user };
			client.emit('playerNum', 1);
			this.server.to(lastRoomKey).emit('playerNum', this.rooms[lastRoomKey].users);
			this.startGameLoop(lastRoomKey); //passo il nome dell'ultima stanza
		}
	}

	@SubscribeMessage('keyPress')
	handleKeyPress(client: Socket, key: string) {
		const roomName = this.room[client.id];
		if (!roomName) return;
		const special = this.rooms[roomName].powerUpHit !== undefined ? true : false;
		let inverted = false;
		if (special)
			inverted = this.rooms[roomName].frame.players[client.data.number].inverted;
		if (key == 'ArrowUp') {
			if (inverted) this.rooms[roomName].moves[client.data.number].arrowDown = true;
			else this.rooms[roomName].moves[client.data.number].arrowUp = true;
		} else {
			if (inverted) this.rooms[roomName].moves[client.data.number].arrowUp = true;
			else this.rooms[roomName].moves[client.data.number].arrowDown = true;
		}
	}

	@SubscribeMessage('keyRelease')
	handleKeyRelease(client: Socket, key: string) {
		const roomName = this.room[client.id];
		if (!roomName) return;
		const special = this.rooms[roomName].powerUpHit !== undefined ? true : false;
		let inverted = false;
		if (special)
			inverted = this.rooms[roomName].frame.players[client.data.number].inverted;
		if (key == 'ArrowUp') {
			if (special && inverted)
				this.rooms[roomName].moves[client.data.number].arrowDown = false;
			else this.rooms[roomName].moves[client.data.number].arrowUp = false;
		} else {
			if (special && inverted)
				this.rooms[roomName].moves[client.data.number].arrowUp = false;
			else this.rooms[roomName].moves[client.data.number].arrowDown = false;
		}
	}

	findRoom(idToWatch: number): string | undefined {
		const keys = Object.keys(this.rooms);
		for (let key of keys) {
			if (
				this.rooms[key].users[0].id === idToWatch ||
				this.rooms[key].users[1].id === idToWatch
			)
				return key;
		}
		return;
	}

	createGame(client: Socket, user: User) {
		this.rooms[client.id] = {
			frame: this.game.initGame(user.special),
			moves: [
				{
					arrowUp: false,
					arrowDown: false,
				},
				{
					arrowUp: false,
					arrowDown: false,
				},
			],
			users: [{ ...user }, undefined],
			intervalID: undefined,
			winner: undefined,
			time: {
				startTime: 0,
				lastUpdate: 0,
			},
		};
		if (user.special) {
			this.rooms[client.id].frame.players[0].inverted = false;
			this.rooms[client.id].powerUpHit = false;
			this.rooms[client.id].firstSpawn = true;
		}
		client.data.number = 0;
		client.emit('playerNum', 0);
	}

	saveFrame(frame: FrameToRender, roomName: string) {
		if (!this.rooms[roomName]) return;
		this.rooms[roomName].frame = { ...frame };
	}

	handleGameOver(roomName: string, winnerNb: number) {
		const clientids = Object.keys(this.room);
		if (!this.rooms[roomName]) {
			return;
		}
		if (!this.rooms[roomName].users[1]) {
			this.database.updateInGameState(this.rooms[roomName].users[0].id);
			delete this.rooms[roomName];
			delete this.room[roomName];
			return;
		}
		const room = this.rooms[roomName];
		const winnerID = room.users[winnerNb].id;
		const loserID = room.users[winnerNb === 0 ? 1 : 0].id;
		clearInterval(room.intervalID);
		this.database.createMatch({
			winnerID,
			loserID,
			losingScore: room.frame.players[winnerNb === 0 ? 1 : 0].score,
			special: room.frame.powerUp !== undefined ? true : false,
		});
		this.database.updateInGameState(winnerID);
		this.database.updateInGameState(loserID);
		this.server.to(roomName).emit('gameOver', winnerNb);
		delete this.rooms[roomName];
		const playersToRemove = clientids.filter((client) => this.room[client] === roomName);
		for (let i = 0; i < playersToRemove.length; i++) delete this.room[playersToRemove[i]];
	}

	startGameLoop(roomName: string) {
		const time = Date.now();
		const room = this.rooms[roomName];
		this.server.to(roomName).emit('updateGame', room.frame);
		room.time.startTime = time;
		room.time.lastUpdate = time;
		setTimeout(
			() =>
				(room.intervalID = setInterval(() => {
					if (room.users[0].special === true)
						this.saveFrame(this.game.gameLoopSpecial(room), roomName);
					else this.saveFrame(this.game.gameLoop(room), roomName);
					this.server.to(roomName).emit('updateGame', room.frame);
					if (room.winner !== undefined) {
						this.handleGameOver(roomName, room.winner);
					}
				}, FRAME_PER_SECOND)),
			100,
		);
	}
}
