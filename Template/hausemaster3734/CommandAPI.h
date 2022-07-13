//
// Created by pepef on 13.07.2022.
//

#ifndef TEMPLATEPLUGIN_COMMANDAPI_H
#define TEMPLATEPLUGIN_COMMANDAPI_H

#include "pch.h"

#include <LoggerAPI.h>

#include "command/CommandManager.h"
#include "command/impl/TestCommand.h"
#include "EventListener.h"

class CommandAPI {
public:
    CommandAPI() = default;
    void onEnable();
    static void* getCommandManager();
    static Logger getLogger() {
        return Logger("CommandAPI");
    }
    static void setTemp(string t);
    static string getTemp();
};

#endif //TEMPLATEPLUGIN_COMMANDAPI_H