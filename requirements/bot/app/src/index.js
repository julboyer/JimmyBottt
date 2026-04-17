const { Client, Intents, GatewayIntentBits, Collection} = require('discord.js');
require('dotenv').config();
// console.log(process.env);
const token = process.env.DISCORD_TOKEN;
const path = require('node:path');
const fs = require('node:fs');
const knex = require('knex')({
	client: 'mysql',
	connection: {
	  host: 'database',
	  port: 3306,
	  user: process.env.SQL_USER,
	  password: process.env.SQL_PASSWORD,
	  database: process.env.SQL_DATABASE,
	},
  });

const client = new Client({ intents: [
									GatewayIntentBits.Guilds,
									GatewayIntentBits.GuildMessages,
									GatewayIntentBits.MessageContent] });

client.commands = new Collection();
const foldersPath = path.join(__dirname, 'commands');
const commandFolders = fs.readdirSync(foldersPath);

for (const folder of commandFolders) {
	const commandsPath = path.join(foldersPath, folder);
	const commandFiles = fs.readdirSync(commandsPath).filter(file => file.endsWith('.js'));
	for (const file of commandFiles) {
		const filePath = path.join(commandsPath, file);
		const command = require(filePath);
		if ('data' in command && 'execute' in command) {
			client.commands.set(command.data.name, command);
		} else {
			console.log(`[WARNING] The command at ${filePath} is missing a required "data" or "execute" property.`);
		}
	}
}

const eventsPath = path.join(__dirname, 'events');
const eventFiles = fs.readdirSync(eventsPath).filter(file => file.endsWith('.js'));

for (const file of eventFiles) {
	const filePath = path.join(eventsPath, file);
	const event = require(filePath);
	console.log(event.name);
	if (event.once) {
		client.once(event.name, (...args) => event.execute(...args));
	} else {
		client.on(event.name, (...args) => event.execute(...args));
	}
}

// console.log(token);
client.login(token);