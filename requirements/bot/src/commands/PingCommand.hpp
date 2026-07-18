#pragma once

#include "commands/Commands.hpp"

using namespace std;
using namespace dpp;

/**
Commande /ping
*/
class PingCommand : public ICommand{
    
    string get_name() const override;

    string get_description() const override;

    void execute(cluster& bot, const slashcommand_t& event) override;

};