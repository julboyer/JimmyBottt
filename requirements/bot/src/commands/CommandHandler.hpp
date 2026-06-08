#pragma once

#include <dpp/dpp.h>

using namespace std;
using namespace dpp;

/**
Interface pour la gestion des commandes
*/
class ICommandHandler {

    public:
        virtual ~ICommandHandler() = default;

        /**
        Gère l'évenement si besoin, sinon passe au suivant
        */
        virtual void handle(const slashcommand_t& event) = 0;
        
        /**
        Passe l'évenement au suivant
        */
        virtual ICommandHandler* next() = 0;

        /**
        Permet de définir le handler suivant
        */
        virtual void set_next(ICommandHandler* next_handler) = 0;
};

/**
Implémentation concrète du handler
*/
class ConcreteCommandHandler : public ICommandHandler {
    private:
        ICommandHandler* next_handler = nullptr;
    
    public:
        ConcreteCommandHandler();
        ~ConcreteCommandHandler();
        
        void handle(const slashcommand_t& event) override;
        ICommandHandler* next() override;
        void set_next(ICommandHandler* next_handler) override;
};