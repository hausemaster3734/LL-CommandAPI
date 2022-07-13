//
// Created by pepef on 09.07.2022.
//

#include "CommandManager.h"

static map<string, ICommand*> command_map;

void CommandManager::init() {
    for(std::pair<string, ICommand*> p_r : command_map) {
        CommandAPI::getLogger().info("Loaded \"" + p_r.first + "\" command");
        command_count++;
    }
    CommandAPI::getLogger().info("Loaded " + std::to_string(command_count) + " commands");
}

void CommandManager::addCommand(void* command) {
    auto* cmd = (ICommand*)command;
    command_map.insert_or_assign(cmd->getName(), cmd);
}

void* CommandManager::getCommand(const string& command) {
    for(std::pair<string, ICommand*> command_pair : command_map) {
        for(const string& aliases : command_pair.second->getAliases()) {
            if(aliases == command) {
                return command_pair.second;
            }
        }
        if(command_pair.first == command) {
            return command_pair.second;
        }
    }
    return nullptr;
}

bool CommandManager::tryExecuteCommand(Player *player, const string& command, const vector<string>& args) {
    void* command_ptr = this->getCommand(command);
    if(command_ptr == nullptr) {
        return false;
    }
    auto* command_ptr_2 = (ICommand*) command_ptr;
    string raw_args;
    vector<string> args_complete;
    string delimiter = " ";
    Utils::implode(args, delimiter, raw_args);
    bool isArgsInvalid = false;
    for(char & b : raw_args) {
        if(b == '\t' || b == '\\') {
            isArgsInvalid = true;
        }
    }
    if(!isArgsInvalid) {
        bool is_quotes = false;
        for(char & i : raw_args) {
            if(i == '\"') {
                is_quotes = !is_quotes;
                continue;
            }
            if(i == ' ') {
                i = (is_quotes) ? '\t' : '\\'; // reachable...
            }
        }
    }
    args_complete = Utils::explode('\\', raw_args);
    for(string &argument_explicit : args_complete) {
        for(char & i : argument_explicit) {
            if(i == '\t') {
                i = ' ';
            }
        }
    }
    if(isArgsInvalid) {
        args_complete = {};
    }
    CommandResult result = command_ptr_2->execute(player, command, std::move(args_complete));
    if(result == CommandResult::INVALID_ARGS) {
        if(player != nullptr) {
            player->sendText("Usage: " + command_ptr_2->getUsage());
        } else {
            CommandAPI::getLogger().error("Usage: " + command_ptr_2->getUsage());
        }
        return true;
    }
    if(result == CommandResult::FAILED_PERMISSION) {
        return false;
    }
    return true;
}

void* CommandManager::handleJoinCommands(AvailableCommandsPacket* packet) {
    Player* player = nullptr;
    for(auto* player_ : Level::getAllPlayers()) {
        if(!player_->isPlayerInitialized()) {
            if(player_->getRealName() == CommandAPI::getTemp()) {
                player = player_;
                std::string emty;
                CommandAPI::setTemp(emty);
                // na usyaki slucha.
            }
        }
    }
    for(std::pair<string, ICommand*> cmdpair : command_map) {
        AvailableCommandsPacket::CommandData cmd_data{
                cmdpair.first,
                cmdpair.second->getDescription(),
                CommandFlag{CommandFlagValue::None},
                CommandPermissionLevel::Any,
                cmdpair.second->getOverloads(),
                -1
        };
        for(const string& ali_a : cmdpair.second->getAliases()) {
            AvailableCommandsPacket::CommandData cmd_data_a{
                    ali_a,
                    cmdpair.second->getDescription(),
                    CommandFlag{CommandFlagValue::None},
                    CommandPermissionLevel::Any,
                    cmdpair.second->getOverloads(),
                    -1
            };
            packet->mCommandDatas.push_back(cmd_data_a);
        }
        packet->mCommandDatas.push_back(cmd_data);
    }
    return packet;
}