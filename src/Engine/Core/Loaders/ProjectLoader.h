//
// Created by Terrarizer on 08/03/2026.
//

#ifndef SESSIONZERO_PROJECTLOADER_H
#define SESSIONZERO_PROJECTLOADER_H
#include "../Project/ProjectInfo.h"
#include "../Project/MapData.h"

namespace zeroProjectLoader {
    // Project - reads project.json and returns metadata
    ProjectInfo loadProject(const std::string& zeroPath);
    void saveProject(const ProjectInfo& info, const std::string& zeroPath);

    // Map - reads specific map.json and returns scene data
    MapData loadMapData(const ProjectInfo& projectInfo, const std::string& mapName);
    void saveMapData(MapData& mapData, const std::string& projectPath, const std::string& mapName);

    // TODO: Make loaders for the rules and the characters (but that's in the future for the model and campaign editors)

    // Project Creation
    std::string createProject(const std::string& name, const std::string& author);
    bool isValidProject(const std::string& zeroPath);
    std::string generateUUID();
}


#endif //SESSIONZERO_PROJECTLOADER_H