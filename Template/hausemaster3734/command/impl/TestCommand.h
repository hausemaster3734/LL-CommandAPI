//
// Created by pepef on 09.07.2022.
//

#ifndef TEMPLATEPLUGIN_TESTCOMMAND_H
#define TEMPLATEPLUGIN_TESTCOMMAND_H

#include "pch.h"

#include <utility>

#include "../OverloadBuilder.hpp"
#include "../ICommand.hpp"

class TestCommand : public ICommand {
public:
    explicit TestCommand(string command_name);
    CommandResult execute(Player* pl_sender, string alias_used, vector<string> c_arg) override;
    vector<AvailableCommandsPacket::OverloadData> getOverloads() override;
};

#endif //TEMPLATEPLUGIN_TESTCOMMAND_H
