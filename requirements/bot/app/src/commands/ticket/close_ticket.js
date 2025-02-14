const { SlashCommandBuilder, PermissionFlagsBits, InteractionContextType, ButtonBuilder, ButtonStyle, ActionRowBuilder } = require('discord.js');
const { execute } = require('./startup');

module.exports = {
	data: new SlashCommandBuilder()
	.setName('close_ticket')
	.setDescription('Ferme le ticket et l\'archive')
	.setDefaultMemberPermissions(PermissionFlagsBits.ManageChannels)
	.setContexts(InteractionContextType.Guild),

	async execute(interaction){
		const channel = interaction.channel;
		
		const confirm = new ButtonBuilder()
			.setCustomId('confirm')
			.setLabel('Fermer le ticket')
			.setStyle(ButtonStyle.Success);
		
		const deny = new ButtonBuilder()
			.setCustomId('cancel')
			.setLabel('Annuler')
			.setStyle(ButtonStyle.Danger);
		const row = new ActionRowBuilder()
			.addComponents(confirm)
			.addComponents(deny);
		
		const response = await interaction.reply({
			content : `Voulez vous fermer ce ticket ?`,
			components : [row],
			withResponse: true,
		});

		const collectorFilter = i => i.user.id === interaction.user.id;

		try {
			console.log(response);
			const confirmation = await response.awaitMessageComponent({ filter: collectorFilter, time: 60_000 });
			// var category = server.channels.cache.find(channel => channel.type == ChannelType.GuildCategory && channel.name == "ModMail");
			console.log(confirmation);
			if (confirmation.customId === 'confirm')
		
			{
				console.log('button get');
				await confirmation.update('validé');
				await interaction.channel.delete();
			}
		} catch (error) {
			console.error('CATCH');
			console.error(error);
			await interaction.editReply({ content: 'Confirmation not received within 1 minute, cancelling', components: [] });
		}
	}
};