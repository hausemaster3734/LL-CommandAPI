//
// Created by pepef on 10.07.2022.
//

#ifndef TEMPLATEPLUGIN_OVERLOADBUILDER_H
#define TEMPLATEPLUGIN_OVERLOADBUILDER_H

#include "pch.h"

#include <MC/AvailableCommandsPacket.hpp>
#include <utility>

enum EnumType : int {
    INTEGER = 0x01,
    FLOAT_A = 0x03,
    VALUE = 0x04,
    WILDCARD_INT = 0x05,
    OPERATOR = 0x06,
    TARGET = 0x08,
    STRING = 0x27,
};

class OverloadBuilder {
public:
    OverloadBuilder() = default;
    void addData(string desc_i) {
        AvailableCommandsPacket::ParamData data_;
        data_.desc = std::move(desc_i);
        data_.sym = 0;
        para_data.push_back(data_);
    }
    void _break() {
        overload_d.push_back(AvailableCommandsPacket::OverloadData{para_data});
        para_data = {};
    }
    vector<AvailableCommandsPacket::OverloadData> payload() {
        return overload_d;
    }
private:
    vector<AvailableCommandsPacket::OverloadData> overload_d;
    vector<AvailableCommandsPacket::ParamData> para_data;
};

#endif //TEMPLATEPLUGIN_OVERLOADBUILDER_H
