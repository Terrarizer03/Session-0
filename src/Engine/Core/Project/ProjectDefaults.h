//
// Created by Terrarizer on 12/03/2026.
//

#ifndef SESSIONZERO_PROJECTDEFAULTS_H
#define SESSIONZERO_PROJECTDEFAULTS_H
#include <string>
#include <vector>
#include "ProjectInfo.h"
#include "nlohmann/json.hpp"

namespace zeroProjectDefaults {
    extern std::vector<std::string> defaultFolders;
    nlohmann::json createDefaultProjectJson(const std::string& name, const std::string& author);
    ProjectInfo createDefaultMap(const std::string& mapName, const std::string& projectFile);
};

#endif //SESSIONZERO_PROJECTDEFAULTS_H