#include <dpp/dpp.h>
#include <cstdlib>

#include "commands/Commands.hpp"
#include "commands/PingCommand.hpp"

using namespace std;
using namespace dpp;

const string BOT_TOKEN = getenv("DISCORD_TOKEN");

int main(){

    cluster bot(BOT_TOKEN);

    // Utilise le logger par défaut
    bot.on_log(utility::cout_logger());

    PingCommand pingCommand;

    CommandRegistry registry;
    registry.add(pingCommand);

    // La fonction anonyme est un handler de TOUTES les commandes
    bot.on_slashcommand([&bot, &registry](const slashcommand_t& event){
        string cmd_name = event.command.get_command_name();
        if ( ICommand* cmd = registry.get(cmd_name) ) {
            cmd->execute(bot, event);
        }
    });

    bot.on_ready([&bot, &registry](const ready_t& event){
        if (run_once<struct register_bot_command>()) {
            registry.register_all_known_commands(bot);
        }
    });

    bot.start(st_wait);
}