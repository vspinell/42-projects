import { IsEmail, IsNotEmpty, IsString } from 'class-validator';

export interface ReqObj {
	grant_type: string;
	client_id: string;
	client_secret: string;
	code: string;
	redirect_uri: string;
}

export class SingUpData {
	@IsString()
	@IsNotEmpty()
	login: string;

	@IsString()
	@IsNotEmpty()
	password: string;

	@IsEmail()
	@IsNotEmpty()
	email: string;
}

export class SingInData {
	@IsString()
	@IsNotEmpty()
	login: string;

	@IsString()
	@IsNotEmpty()
	password: string;
}

export interface Token {
	access_token: string;
	refresh_token: string;
}
