#include "commands/OpenTicketCommand.hpp"

OpenTicketCommand::OpenTicketCommand(TicketManager& manager):manager(manager){}

string OpenTicketCommand::get_name() const {
    return "ticket";
}

string OpenTicketCommand::get_description() const {
    return "Ouvre un ticket";
}

void OpenTicketCommand::execute(cluster& bot, const slashcommand_t& event) {
    snowflake user_id = event.command.get_issuing_user().id;
    this->manager.open(user_id);
    event.reply(message("Ticket ouvert!").set_flags(dpp::m_ephemeral));
};