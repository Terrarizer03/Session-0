//
// Created by Terrarizer on 09/03/2026.
//

#ifndef DNDCREATOR_PROJECTINFO_H
#define DNDCREATOR_PROJECTINFO_H
#include <string>
#include <unordered_map>

struct ProjectInfo {
    std::string name;
    std::string version;
    std::string author;
    std::string timeCreated;
    std::string timeModified; // This will be hardcoded into the JSON for now
    std::unordered_map<std::string, std::string> mapPaths; // MapName : "path_to/map_file"
    std::unordered_map<std::string, std::string> characterPaths;
    std::unordered_map<std::string, std::string> rules;
};

#endif //DNDCREATOR_PROJECTINFO_H