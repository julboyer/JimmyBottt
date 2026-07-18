#pragma once

#include <dpp/dpp.h>

using namespace dpp;

class TicketManager {

    private:
        cluster& bot;
        snowflake guild_id;
        snowflake tickets_category_id;

    public:

        TicketManager(cluster& bot, const snowflake guild_id, const snowflake tickets_category_id);

        ~TicketManager() = default;

        /**
        
        */
        void open(const snowflake user_id);
        
        /**
        
        */
        bool close(const snowflake ticket_channel_id);

};