//
// Created by Terrarizer on 08/03/2026.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include "../Utilities/parseMaterial.h"
#include "../Utilities/parseTransform.h"
#include "ProjectLoader.h"
#include "AssetLoader.h"
#include "nlohmann/json.hpp"

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

        if (file.peek() == std::ifstream::traits_type::eof())
            return {}; // TODO: Change this to an error that says "This file is empty."

        nlohmann::json data;

        try {
            data = nlohmann::json::parse(file);
        } catch (const nlohmann::json::exception& e) {
            std::cout << "Failed to parse" << dndPath << ": " << e.what() << "\n";
            return {}; // TODO: Change this to an error that says "Could not parse file."
        }

        projectInfo.name = data.value("name", "Unnamed");
        projectInfo.version = data["metadata"].value("version", "X.X");
        projectInfo.author = data["metadata"].value("author", "Unnamed");
        projectInfo.timeCreated = data["metadata"].value("timeCreated", "Unknown");
        projectInfo.timeModified = data["metadata"].value("timeModified", "Unknown");

        projectInfo.mapPaths = data.value("mapPaths", std::unordered_map<std::string, std::string>{});
        for (auto& [name, path] : projectInfo.mapPaths)
            path = dndPath + "/" + path;

        projectInfo.characterPaths = data.value("characterPaths", std::unordered_map<std::string, std::string>{});
        for (auto& [name, path] : projectInfo.characterPaths)
            path = dndPath + "/" + path;

        projectInfo.rules = data.value("rules", std::unordered_map<std::string, std::string>{}); // Maybe add the dndPath to these too.

        return projectInfo;
    }

    void saveProject(const ProjectInfo& info, const std::string& dndPath) {

    }

    MapData loadMapData(const ProjectInfo& projectInfo, const std::string& mapName) {
        // O(1) average due to unordered_map
        auto it = projectInfo.mapPaths.find(mapName);
        if (it == projectInfo.mapPaths.end()) {
            std::cout << "Map not found: " << mapName << "\n";
            std::cout << "Available maps:\n";
            for (auto& pair : projectInfo.mapPaths)
                std::cout << "  '" << pair.first << "'\n";
            return {};
        }

        std::string mapFolder = it->second;
        std::string mapPath = mapFolder + "/map.json";
        // Example: "my_campaign.dnd/maps/Tavern/map.json"

        MapData mapData;

        std::ifstream file(mapPath);

        if (file.peek() == std::ifstream::traits_type::eof())
            return {};

        nlohmann::json data;

        try {
            data = nlohmann::json::parse(file);
        } catch (const nlohmann::json::exception& e) {
            std::cout << "Failed to parse" << mapPath << ": " << e.what() << "\n";
            return {}; // TODO: Change this to an error that says "Could not parse file."
        }

        mapData.name = data.value("name", "Unnamed");

        std::cout << "Map name: " << mapData.name << "\n";
        std::cout << "Contains objects: " << data.contains("objects") << "\n";
        if (data.contains("objects"))
            std::cout << "Object count: " << data["objects"].size() << "\n";

        if (data.contains("objects")) {
            for (auto& obj : data["objects"]) {
                SceneObject sceneObj;
                sceneObj.name = obj.value("name", "Unnamed");

                // mesh field is a path string
                if (!obj.contains("mesh")) continue;
                std::string meshPath = obj["mesh"].get<std::string>();

                std::string fullMeshPath = mapFolder + "/" + meshPath;
                // Example: "my_campaign.dnd/maps/Tavern/models/table.obj"

                sceneObj.mesh = std::make_shared<Mesh>(std::move(dndAssetLoader::loadOBJ(fullMeshPath)));

                if (obj.contains("material")) {
                    /*
                     * Not sure if mapFolder being passed is a hack, but the helper does need
                     * the base path... So I guess not, it's 10pm I have to sleep tho
                     */
                    sceneObj.material = dndHelper::parseMaterial(obj["material"], mapFolder);
                }

                if (obj.contains("transform")) {
                    sceneObj.transform = dndHelper::parseTransform(obj["transform"]);
                }

                mapData.objects.push_back(sceneObj);
            }
        }

        return mapData;
    }


    void saveMapData(const MapData& mapData, const std::string& dndPath) {

    }

    bool createProject(const std::string& dndPath) {
        return true;
    }

    bool isValidProject(const std::string& dndPath) {
        // Check folder exists
        if (!std::filesystem::exists(dndPath)) {
            std::cout << "Failed: path doesn't exist\n";
            return false;
        }

        // Check .dnd extension
        if (std::filesystem::path(dndPath).extension() != ".dnd") {
            std::cout << "Failed: wrong extension - got " << std::filesystem::path(dndPath).extension() << "\n";
            return false;
        }


        // Check project.json exists
        std::string projectJsonPath = dndPath + "/project.json";
        if (!std::filesystem::exists(projectJsonPath)) {
            std::cout << "Failed: no project.json\n";
            return false;
        }

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
        if (!data["metadata"].contains("version")) return false;
        if (!data["metadata"].contains("author"))  return false;

        return true;
    }
}