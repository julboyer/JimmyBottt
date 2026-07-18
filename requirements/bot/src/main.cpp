#include <dpp/dpp.h>
#include <cstdlib>

#include "commands/Commands.hpp"
#include "commands/PingCommand.hpp"
#include "utils/TicketManager.hpp"
#include "commands/OpenTicketCommand.hpp"

using namespace std;
using namespace dpp;

const string BOT_TOKEN = getenv("DISCORD_TOKEN");

// Tout ce qui est ID doit être vu comme un dpp::snowflake
// PS : Des strings, mais reloues
const snowflake AUTOBAN_CHANNEL_ID = (snowflake) getenv("AUTOBAN_CHANNEL_ID");
const snowflake LOGS_CHANNEL_ID = (snowflake) getenv("LOGS_CHANNEL_ID");
const snowflake GUILD_ID = (snowflake) getenv("GUILD_ID");
const snowflake SUPPORT_CATEGORY_ID = (snowflake) getenv("SUPPORT_CATEGORY_ID");

int main(){

    cluster bot(BOT_TOKEN);

    // Utilise le logger par défaut
    bot.on_log(utility::cout_logger());

    TicketManager ticket_manager(bot, GUILD_ID, SUPPORT_CATEGORY_ID);

    PingCommand pingCommand;

    OpenTicketCommand open_ticket_cmd(ticket_manager);

    CommandRegistry registry;
    registry.add(pingCommand);
    registry.add(open_ticket_cmd);

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

    bot.on_message_create([&bot](const message_create_t& event){
        const message& msg = event.msg;

        // Ignore les DM 
        if (!msg.guild_id) return;

        if (event.msg.channel_id == AUTOBAN_CHANNEL_ID) {
            bot.guild_ban_add(
                msg.guild_id,
                msg.author.id,
                60 * 60 * 60, // = 1h
                [&bot, msg](const confirmation_callback_t& callback) {
                    // On ignore les erreurs
                    if (callback.is_error()) return;
                    bot.message_create(
                        message(
                            LOGS_CHANNEL_ID,
                            "Ban de <@" + to_string(msg.author.id) + "> pour suspicion de spam."
                        )
                    );
                }
            );
        }
    });

    bot.start(st_wait);
}