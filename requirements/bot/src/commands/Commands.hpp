#pragma once

#include <dpp/dpp.h>
#include <string>
#include <map>

using namespace std;
using namespace dpp;

class ICommand {
    /**
        Interface pour les commandes
    */
    public:
        virtual ~ICommand() = default;
        virtual string get_name() const = 0;
        virtual string get_description() const = 0;
        virtual void execute(cluster& bot, const slashcommand_t& event) = 0;
};

class CommandRegistry {
    private:

        map<string, ICommand*> commands;

    public:
        /*
        Ajout d'une commande dans le Registre
        */
        void add(ICommand& command){
            commands[command.get_name()] = &command;
        }

        /*
        Recherche d'une commande dans le registre

        @return le pointeur vers l'objet commande si elle est enregistrée,
        le pointeur nul sinon.
        */
        ICommand* get(const string name){
            auto it = commands.find(name);
            if (it != commands.end()){
                return it->second;
            }
            return nullptr;
        }

        /*
        Enregistre/Déclare toutes les commandes connues vers l'API Discord
        */
        void register_all_known_commands(cluster& bot) {
            for (const auto& [_, cmd] : commands){
                slashcommand scmd(cmd->get_name(), cmd->get_description(), bot.me.id);
                bot.global_command_create(scmd);
            }
        }
};