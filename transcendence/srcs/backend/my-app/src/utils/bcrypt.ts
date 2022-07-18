import * as bcrypt from 'bcrypt';

export async function encodePassword(rawPassword: string) {
	const SALT = bcrypt.genSaltSync();
	return bcrypt.hashSync(rawPassword, SALT);
}

export function checkPasswords(rawPassword: string, hash: string) {
	return bcrypt.compareSync(rawPassword, hash);
}
