//
// Created by Terrarizer on 08/03/2026.
//

#ifndef DNDCREATOR_PROJECTLOADER_H
#define DNDCREATOR_PROJECTLOADER_H
#include "../Project/ProjectInfo.h"
#include "../Project/MapData.h"

namespace dndProjectLoader {
    // Project - reads project.json and returns metadata
    ProjectInfo loadProject(const std::string& dndPath);
    void saveProject(const ProjectInfo& info, const std::string& dndPath);

    // Map - reads specific map.json and returns scene data
    MapData loadMapData(const std::string& mapPath, const std::string& mapName);
    void saveMapData(const MapData& mapData, const std::string& mapPath);

    // Project Creation
    bool createProject(const std::string& dndPath, const std::string& name);
    bool isValidProject(const std::string& dndPath);
}


#endif //DNDCREATOR_PROJECTLOADER_H