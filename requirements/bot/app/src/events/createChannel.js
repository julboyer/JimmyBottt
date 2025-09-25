const { Events, ChannelType,  } = require('discord.js');
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

module.exports = {
	name: Events.InteractionCreate,
	async execute(interaction) {
		if (!interaction.isButton()) return;
		if (interaction.customId === 'ticket')
		{
			await interaction.deferReply();
			
			var server = interaction.guild;
			var category = server.channels.cache.find(channel => channel.type == ChannelType.GuildCategory && channel.name == "ModMail");
			const channel = await category.children.create({name : interaction.user.username, //Create a channel with the same name as the user who clicked the button
									type : ChannelType.GuildText,
									});
			await interaction.deleteReply();
			var ret = await knex('TICKETS').insert({
				channelID : channel.id,
				userID : interaction.user.id,
				logFile : 'test.txt'
			});
		}
		else 
		{
			console.log('button test');
			return;
		}
	},
};