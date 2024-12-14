const { Client, Events, GatewayIntentBits } = require('discord.js');
require('dotenv').config();
const token  = process.env.DISCORD_TOKEN;
// console.log(token);

const client = new Client({ intents: [GatewayIntentBits.Guilds] });

client.once(Events.ClientReady, readyClient => {
	console.log(`Ready! Logged in as ${readyClient.user.tag}`);
});

client.login(token);