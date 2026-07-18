#pragma once

#include "commands/Commands.hpp"
#include "utils/TicketManager.hpp"

using namespace std;
using namespace dpp;

/**
Commande /ticket
*/
class OpenTicketCommand : public ICommand{
    
    private:
        TicketManager& manager;

    public:
        OpenTicketCommand(TicketManager& manager);

        string get_name() const override;
        string get_description() const override;
        void execute(cluster& bot, const slashcommand_t& event) override;

};