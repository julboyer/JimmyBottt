#include "TicketManager.hpp"

TicketManager::TicketManager(
        cluster& bot,
        const snowflake guild_id,
        const snowflake tickets_category_id
    ) : bot(bot) {
    this->guild_id = guild_id;
    this->tickets_category_id = tickets_category_id;
}

void TicketManager::open(const snowflake user_id){
    channel ch;
    
    ch.name = "ticket-USER";
    ch.topic = "Ticket n°X - Créé par USER";
    ch.guild_id = this->guild_id;
    ch.parent_id = this->tickets_category_id;

    this->bot.channel_create(ch);
}

bool TicketManager::close(const snowflake ticket_channel_id){
    return false;
}