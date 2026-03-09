//
// Created by Terrarizer on 08/03/2026.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include "ProjectLoader.h"
#include "AssetLoader.h"
#include "nlohmann/json.hpp"
#include "../Utilities/toLower.h"

namespace dndProjectLoader {
    ProjectInfo loadProject(const std::string& dndPath) {
        /*
         * This check will probably never be used since this function will only be
         * called when loading a valid project. Still good to have it tho just in case
         */
        if (!std::filesystem::exists(dndPath))
            return {}; // TODO: Change this to an error that visually shows in-engine

        ProjectInfo projectInfo;

        std::ifstream file(dndPath + "/project.json");

        if (file.peek() == std::ifstream::traits_type::eof()) {
            return {}; // TODO: Change this to an error that says "This file is empty."
        }

        nlohmann::json data;

        try {
            data = nlohmann::json::parse(file);
        } catch (const nlohmann::json::exception& e) {
            std::cout << "Failed to parse" << dndPath << ": " << e.what() << "\n";
            return {}; // TODO: Change this to an error that says "Could not parse file."
        }

        projectInfo.name = data.value("name", "Unnamed");
        projectInfo.version = data.value("version", "X.X");
        projectInfo.author = data.value("author", "Unnamed");
        projectInfo.mapPaths = data.value("mapPaths", std::vector<std::string>{});
        projectInfo.characterPaths = data.value("characterPaths", std::vector<std::string>{});
        projectInfo.rules = data.value("rules", std::map<std::string, std::string>{});

        return projectInfo;
    }

    void saveProject(const ProjectInfo& info, const std::string& dndPath) {

    }

    MapData loadMapData(const std::string& dndPath, const std::string& mapName) {
        std::string mapDir = dndPath + "/maps/";

        for (auto& entry : std::filesystem::directory_iterator(mapDir)) {
            if (!entry.is_directory()) continue;

            std::string folderName = entry.path().filename().string();
            // Example: "Tavern" or "Dungeon"

            if (toLower(folderName) == toLower(mapName)) {
                std::string mapPath = entry.path().string() + "/map.json";
                // Example: "my_campaign.dnd/maps/tavern/map.json"

                MapData mapData;

                std::ifstream file(mapPath);

                if (file.peek() == std::ifstream::traits_type::eof()) {
                    return {};
                }

                nlohmann::json data;

                try {
                    data = nlohmann::json::parse(file);
                } catch (const nlohmann::json::exception& e) {
                    std::cout << "Failed to parse" << mapPath << ": " << e.what() << "\n";
                    return {}; // TODO: Change this to an error that says "Could not parse file."
                }

                mapData.name = data.value("name", "Unnamed");

                if (data.contains("objects")) {
                    for (auto& obj : data["objects"]) {
                        SceneObject sceneObj;
                        sceneObj.name = obj["name"].get<std::string>();

                        // mesh field is a path string
                        std::string meshPath = obj["mesh"].get<std::string>();

                        std::string fullMeshPath = entry.path().string() + "/" + meshPath;
                        // Example: "my_campaign.dnd/maps/tavern/models/table.obj"

                        sceneObj.mesh = std::make_shared<Mesh>(std::move(dndAssetLoader::loadOBJ(fullMeshPath)));
                        mapData.objects.push_back(sceneObj);
                    }
                }

                return mapData;
            }
        }

        return {};
    }

    void saveMapData(const MapData& mapData, const std::string& dndPath) {

    }

    bool createProject(const std::string& dndPath) {
        return true;
    }

    bool isValidProject(const std::string& dndPath) { // TODO: Implement this to every loader
        // Check folder exists
        if (!std::filesystem::exists(dndPath))
            return false;

        // Check .dnd extension
        if (std::filesystem::path(dndPath).extension() != ".dnd")
            return false;

        // Check project.json exists
        std::string projectJsonPath = dndPath + "/project.json";
        if (!std::filesystem::exists(projectJsonPath))
            return false;

        // Check project.json has necessary fields
        std::ifstream file(projectJsonPath);
        nlohmann::json data;

        try {
            data = nlohmann::json::parse(file);
        } catch (...) {
            return false;
        }

        // Necessary fields
        if (!data.contains("name"))    return false;
        if (!data.contains("version")) return false;
        if (!data.contains("author"))  return false;

        return true;
    }
}