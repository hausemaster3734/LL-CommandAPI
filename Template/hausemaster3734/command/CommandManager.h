//
// Created by pepef on 13.07.2022.
//

#ifndef TEMPLATEPLUGIN_COMMANDMANAGER_H
#define TEMPLATEPLUGIN_COMMANDMANAGER_H

#include "pch.h"

#include "ICommand.hpp"
#include "../CommandAPI.h"
#include "../utils/Utils.hpp"

#include <MC/AvailableCommandsPacket.hpp>
#include <MC/MinecraftPackets.hpp>
#include <MC/Command.hpp>
#include <MC/Level.hpp>
#include <MC/Player.hpp>
#include <utility>

class CommandManager {
public:
    CommandManager() = default;
    void init();
    void addCommand(void* command);
    void* getCommand(const string& command);
    bool tryExecuteCommand(Player* player, const string& command, const vector<string>& args);
    void* handleJoinCommands(AvailableCommandsPacket* packet);
private:
    int command_count = 0;
};


#endif //TEMPLATEPLUGIN_COMMANDMANAGER_H
