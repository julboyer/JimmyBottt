#include "PingCommand.hpp"

// Constructeur
PingCommand::PingCommand() : next_handler(nullptr) {
}

// Destructeur
PingCommand::~PingCommand() {}

// Gestion de l'event 
void PingCommand::handle(const slashcommand_t& event) {

    if (event.command.get_command_name() == "ping"){
        event.reply("Pong!");
    } else {
        if (this->next_handler != nullptr) {
            this->next_handler->handle(event);
        }
    }
}

// Obtenir le suivant
ICommandHandler* PingCommand::next() {
    return this->next_handler;
}

// Définir le suivant
void PingCommand::set_next(ICommandHandler* next_handler) {
    this->next_handler = next_handler;
}