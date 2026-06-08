#pragma once

#include "CommandHandler.hpp"

using namespace std;
using namespace dpp;

/**
Command /ping
*/
class PingCommand : public ICommandHandler {
    private:
        ICommandHandler* next_handler = nullptr;
    
    public:
        PingCommand();
        ~PingCommand();
        
        void handle(const slashcommand_t& event) override;
        ICommandHandler* next() override;
        void set_next(ICommandHandler* next_handler) override;
};