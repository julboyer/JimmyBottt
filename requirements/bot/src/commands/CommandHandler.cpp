#include "CommandHandler.hpp"

// Constructeur
ConcreteCommandHandler::ConcreteCommandHandler() : next_handler(nullptr) {
}

// Destructeur
ConcreteCommandHandler::~ConcreteCommandHandler() {}

// Gestion de l'event 
void ConcreteCommandHandler::handle(const slashcommand_t& event) {
    if (this->next_handler != nullptr) {
        this->next_handler->handle(event);
    }
}

// Obtenir le suivant
ICommandHandler* ConcreteCommandHandler::next() {
    return this->next_handler;
}

// Définir le suivant
void ConcreteCommandHandler::set_next(ICommandHandler* next_handler) {
    this->next_handler = next_handler;
}