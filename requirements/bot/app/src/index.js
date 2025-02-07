const { Client, Events, GatewayIntentBits, Collection, MessageFlags, Message, EmbedBuilder, ActionRow, ActionRowBuilder, ButtonBuilder, ButtonStyle, messageLink, ChannelType, CategoryChannelChildManager} = require('discord.js');
require('dotenv').config();
// console.log(process.env);
const token = process.env.DISCORD_TOKEN;
const path = require('node:path');
const fs = require('node:fs');

const client = new Client({ intents: [GatewayIntentBits.Guilds] });

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

client.once(Events.ClientReady, readyClient => {
	console.log(`Ready! Logged in as ${readyClient.user.tag}`);
});

client.on(Events.InteractionCreate, async interaction => {
	if (!interaction.isChatInputCommand()) return;
	const command = interaction.client.commands.get(interaction.commandName);

	if (!command) {
		console.error(`No command matching ${interaction.commandName} was found.`);
		return;
	}

	try {
		await command.execute(interaction);
	} catch (error) {
		console.error(error);
		if (interaction.replied || interaction.deferred) {
			await interaction.followUp({ content: 'There was an error while executing this command!', flags: MessageFlags.Ephemeral });
		} else {
			await interaction.reply({ content: 'There was an error while executing this command!', flags: MessageFlags.Ephemeral });
		}
	}
});

client.on('interactionCreate', async interaction => {
    if (!interaction.isButton()) return;
	if (interaction.customId === 'ticket')
	{
		interaction.deferReply();
		const channel = interaction.channel;
		var server = interaction.guild;
		var category = server.channels.cache.find(channel => channel.type == ChannelType.GuildCategory && channel.name == "ModMail");
		category.children.create({name : interaction.user.username, //Create a channel with the same name as the user who clicked the button
								type : ChannelType.GuildText,
								});
		interaction.deleteReply();
		// console.log(interaction);
	}
});

// console.log(token);
client.login(token);