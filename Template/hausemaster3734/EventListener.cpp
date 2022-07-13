//
// Created by pepef on 13.07.2022.
//

#include "EventListener.h"

THook(void*, "?write@AvailableCommandsPacket@@UEBAXAEAVBinaryStream@@@Z", void* dktapps, void* SOFe3) {
    CommandManager* cmd_mgr = ((CommandManager*)CommandAPI::getCommandManager());
    auto* end_packet = (AvailableCommandsPacket*)cmd_mgr->handleJoinCommands((AvailableCommandsPacket *)dktapps);
    return original(end_packet, SOFe3);
}

bool handleJoin(Event::PlayerPreJoinEvent &event) {
    CommandAPI::setTemp(event.mPlayer->getRealName());
    return true;
}

bool handleCommandPlayer(Event::PlayerCmdEvent &event) {
    if (event.mCommand.empty()) {
        return true;
    }
    vector<string> args_raw = Utils::explode(' ', event.mCommand);
    string command = args_raw[0];
    args_raw.erase(args_raw.begin());
    return !((CommandManager *) CommandAPI::getCommandManager())->tryExecuteCommand(event.mPlayer, command, args_raw);
}

bool handleCommandConsole(Event::ConsoleCmdEvent &event) {
    if (event.mCommand.empty()) {
        return true;
    }
    vector<string> args_raw = Utils::explode(' ', event.mCommand);
    string command = args_raw[0];
    args_raw.erase(args_raw.begin());
    return !((CommandManager *) CommandAPI::getCommandManager())->tryExecuteCommand(nullptr, command, args_raw);
}

void EventListener::init() {
    Event::ConsoleCmdEvent::subscribe_ref(handleCommandConsole);
    Event::PlayerCmdEvent::subscribe_ref(handleCommandPlayer);
    Event::PlayerPreJoinEvent::subscribe_ref(handleJoin);
}