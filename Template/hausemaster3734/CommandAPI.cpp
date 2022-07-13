//
// Created by pepef on 13.07.2022.
//

#include "CommandAPI.h"

static void* command_manager;
static string temp;

void CommandAPI::onEnable() {
    command_manager = new CommandManager();
    CommandManager* local = ((CommandManager *) command_manager);
    local->addCommand(new TestCommand("testa"));
    local->init();
    EventListener *listener = new EventListener();
    listener->init();
}

void* CommandAPI::getCommandManager() {
    return command_manager;
}

void CommandAPI::setTemp(string t) {
    temp = std::move(t);
}

string CommandAPI::getTemp() {
    return temp;
}