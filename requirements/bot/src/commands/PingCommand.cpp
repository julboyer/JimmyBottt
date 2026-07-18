#include "commands/PingCommand.hpp"

string PingCommand::get_name() const {
    return "ping";
}

string PingCommand::get_description() const {
    return "Réponds pong";
}

void PingCommand::execute(cluster& bot, const slashcommand_t& event) {
    event.reply("Pong!");
};