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
    MapData loadMapData(const ProjectInfo& projectInfo, const std::string& mapName);
    void saveMapData(const std::string& mapPath);

    // TODO: Make loaders for the rules and the characters (but that's in the future for the model and campaign editors)

    // Project Creation
    bool createProject(const std::string& name, const std::string& author);
    bool isValidProject(const std::string& dndPath);
}


#endif //DNDCREATOR_PROJECTLOADER_H