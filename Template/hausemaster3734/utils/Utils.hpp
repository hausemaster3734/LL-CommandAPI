//
// Created by pepef on 13.07.2022.
//

#ifndef TEMPLATEPLUGIN_UTILS_H
#define TEMPLATEPLUGIN_UTILS_H

#include "pch.h"

class Utils {
public:
    static std::vector<std::string> explode(const char pattern, const std::string& basicString) {
        std::vector<std::string> res;
        std::stringstream input(basicString);
        std::string temp;
        while (getline(input, temp, pattern)) {
            res.push_back(temp);
        }
        return res;
    }

    static std::string& implode(const std::vector<std::string>& elements, std::string& delimiter, std::string& basicString) {
        for (auto constIterator = elements.begin(); constIterator != elements.end(); ++constIterator) {
            basicString += (*constIterator);
            if (constIterator + 1 != elements.end()) {
                basicString += delimiter;
            }
        }
        return basicString;
    }
};

#endif //TEMPLATEPLUGIN_UTILS_H
