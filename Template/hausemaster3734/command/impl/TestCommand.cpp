//
// Created by pepef on 09.07.2022.
//

#include "TestCommand.h"

TestCommand::TestCommand(string command_name) : ICommand(std::move(command_name), "test command.", "/test <arg1>", {"test1"}) {}

vector<AvailableCommandsPacket::OverloadData> TestCommand::getOverloads() {
    OverloadBuilder builder = OverloadBuilder();
    builder.addData("test");
    builder._break();
    builder.addData("test2");
    builder.addData("test3");
    builder._break();
    return builder.payload();
}

CommandResult TestCommand::execute(Player *pl_sender, string alias_used, vector<string> c_arg) {
    if(c_arg.empty()) {
        return CommandResult::INVALID_ARGS;
    }
    for(const string& arg : c_arg) {
        pl_sender->sendText("Arg: " + arg);
    }
    pl_sender->sendText("Alias used: " + alias_used);
    return CommandResult::SUCCESS;
}