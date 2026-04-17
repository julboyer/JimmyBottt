const {Events} = require('discord.js');

module.exports = {
	name:Events.MessageCreate,
	autobanChannelId: "",
	purgeMessageTime: 60 * 60, // temps en secondes
	async execute(message){
		if (message.channelId == this.autobanChannelId) {

			targetMember = await message.guild.members.fetch(message.author.id);

			hammer = {
				reason:"Autodetection d'un compte spam",
				deleteMessageSeconds: this.purgeMessageTime
			};

			if (targetMember && targetMember.bannable) await targetMember.ban(hammer);
		}	
	}
};
