const { SlashCommandBuilder, PermissionFlagsBits, InteractionContextType, Client, GatewayIntentBits, EmbedBuilder, ButtonBuilder, ActionRowBuilder, ButtonStyle, MessageComponentInteraction } = require("discord.js");

const client = new Client({ intents: [GatewayIntentBits.Guilds] });

module.exports = {
	data: new SlashCommandBuilder()
		.setName('startup')
		.setDescription('startup command')
		.addChannelOption(option =>
			option
				.setName('channel')
				.setDescription('Channel où envoyer le message')
				.setRequired(true)
		)
		.setDefaultMemberPermissions(PermissionFlagsBits.ManageChannels)
		.setContexts(InteractionContextType.Guild),

		async execute(interaction){
			const channel = interaction.options.getChannel('channel');
			channel.messages.fetch(100).then(messages => { //delete all messages from the bot in the defined channel to avoid double posting
				messages.forEach(message => {
					if(message.author.id === process.env.APP_ID) {
						message.delete();
					}
				});
			});
			const embed = new EmbedBuilder()
			.setTitle("Création de ticket")
			.setDescription("Texte bidon.txt")
			.setColor("#00b0f4");
			const ticket = new ButtonBuilder()
				.setCustomId('ticket')
				.setLabel('Envoyer un ticket')
				.setStyle(ButtonStyle.Primary);
			const row = new ActionRowBuilder().addComponents(ticket);
			await interaction.deferReply();
			await interaction.deleteReply();
			await channel.send({
				embeds: [embed],
				components: [row],
				withResponse: true,
				});
		},
	};