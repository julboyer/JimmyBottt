#include <dpp/dpp.h>
#include <cstdlib>

#include "commands/CommandHandler.hpp"
#include "commands/PingCommand.hpp"

using namespace std;
using namespace dpp;

const string BOT_TOKEN = getenv("TOKEN");

int main(){

    cluster bot(BOT_TOKEN);

    // Utilise le logger par défaut
    bot.on_log(utility::cout_logger());

    ConcreteCommandHandler handler;
    PingCommand ping_cmd;

    handler.set_next(&ping_cmd);

    // La fonction anonyme est un handler de TOUTES les commandes
    bot.on_slashcommand([](const slashcommand_t& event){
        string cmd_name = event.command.get_command_name();
        if (cmd_name == "ping") event.reply("Pong!");
    });

    bot.on_ready([&bot](const ready_t& event){
        if (run_once<struct register_bot_command>()) {
            bot.global_command_create(slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });

    bot.start(st_wait);
}