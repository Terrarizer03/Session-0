//
// Created by Terrarizer on 09/03/2026.
//

#ifndef DNDCREATOR_PROJECTINFO_H
#define DNDCREATOR_PROJECTINFO_H
#include <map>
#include <string>
#include <vector>

struct ProjectInfo {
    std::string name;
    std::string version;
    std::string author;
    std::vector<std::string> mapPaths;
    std::vector<std::string> characterPaths;
    std::map<std::string, std::string> rules;
};

#endif //DNDCREATOR_PROJECTINFO_H