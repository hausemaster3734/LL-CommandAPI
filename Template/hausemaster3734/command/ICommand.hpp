//
// Created by pepef on 09.07.2022.
//

#ifndef TEMPLATEPLUGIN_COMMAND_H
#define TEMPLATEPLUGIN_COMMAND_H

#include "pch.h"

#include <MC/AvailableCommandsPacket.hpp>
#include <MC/Player.hpp>
#include <utility>

enum CommandResult {
    VANILLA_PASSED,
    FAILED_PERMISSION,
    INVALID_ARGS,
    SUCCESS
};

class ICommand {
public:
    explicit ICommand(string command_name, string desc = "", string usage_m = "", const vector<string>& aliases = {}) {
        this->c_name = std::move(command_name);
        this->m_usage = std::move(usage_m);
        this->aliases_d = aliases;
        this->c_desc = std::move(desc);
    }
    virtual CommandResult execute(Player* pl_sender, string alias_used, vector<string> c_arg) = 0;
    virtual vector<AvailableCommandsPacket::OverloadData> getOverloads() = 0;
    static bool testSender(Player* pl_sender) {
        if(pl_sender == nullptr) {
            std::cout << "Console sucks." << std::endl;
            return false;
        }
        return true;
    }
    string getName() {
        return this->c_name;
    }
    CommandResult getResult() {
        return this->res_t;
    }
    vector<string> getAliases() {
        return this->aliases_d;
    }
    string getUsage() {
        return this->m_usage;
    }
    string getDescription() {
        return this->c_desc;
    }
private:
    CommandResult res_t = CommandResult::VANILLA_PASSED;
    vector<string> aliases_d;
    string m_usage;
    string c_name;
    string c_desc;
};

#endif //TEMPLATEPLUGIN_COMMAND_H
