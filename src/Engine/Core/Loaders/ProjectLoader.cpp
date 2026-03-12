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
#include "../Project/ProjectDefaults.h"
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

        if (!file.is_open()) {
            std::cout << "Failed to open file: " << dndPath + "/project.json" << std::endl;
            return {};
        }

        if (file.peek() == std::ifstream::traits_type::eof())
            return {}; // TODO: Change this to an error that says "This file is empty."

        nlohmann::json data;

        try {
            data = nlohmann::json::parse(file);
        } catch (const nlohmann::json::exception& e) {
            std::cout << "Failed to parse" << dndPath << ": " << e.what() << std::endl;
            return {}; // TODO: Change this to an error that says "Could not parse file."
        }

        projectInfo.name = data.value("name", "Unnamed");

        if (data.contains("metadata")) {
            projectInfo.version = data["metadata"].value("version", "X.X");
            projectInfo.author = data["metadata"].value("author", "Unnamed");
            projectInfo.timeCreated = data["metadata"].value("timeCreated", "Unknown");
            projectInfo.timeModified = data["metadata"].value("timeModified", "Unknown");
        }

        projectInfo.mapPaths = data.value("mapPaths", std::unordered_map<std::string, std::string>{});
        for (auto &path: projectInfo.mapPaths | std::views::values)
            path = dndPath + "/" + path;

        projectInfo.characterPaths = data.value("characterPaths", std::unordered_map<std::string, std::string>{});
        for (auto &path: projectInfo.characterPaths | std::views::values)
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
            std::cout << "Map not found: " << mapName << std::endl;
            std::cout << "Available maps:\n";
            for (const auto &key: projectInfo.mapPaths | std::views::keys)
                std::cout << "  '" << key << "'\n";
            return {};
        }

        std::string mapFolder = it->second;
        std::string mapPath = mapFolder + "/map.json";
        // Example: "my_campaign.dnd/maps/Tavern/map.json"

        MapData mapData;

        std::ifstream file(mapPath);

        if (!file.is_open()) {
            std::cout << "Failed to open file: " << mapPath << std::endl;
            return {};
        }

        nlohmann::json data;

        try {
            data = nlohmann::json::parse(file);
        } catch (const nlohmann::json::exception& e) {
            std::cout << "Failed to parse" << mapPath << ": " << e.what() << std::endl;
            return {}; // TODO: Change this to an error that says "Could not parse file."
        }

        mapData.name = data.value("name", "Unnamed");

        std::cout << "Map name: " << mapData.name << std::endl;
        std::cout << "Contains objects: " << data.contains("objects") << std::endl;
        if (data.contains("objects"))
            std::cout << "Object count: " << data["objects"].size() << std::endl;

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


    void saveMapData(const MapData& mapData, const std::string& mapPath) {
        /*
         * Take in map data and save it to its map.json file.
         */
    }

    bool createProject(const std::string& name, const std::string& author) {
        /**
         * Quick outline in Project Creation:
         *
         * Take the name and pass it. Check if it exists first, if not then create the folder.
         * In the folder create a project.json that has default values. Once created, populate it with
         * folders (maps/, models/, characters/, campaign_rules/, and audio/) that have their own .json files.
         */

        // TODO: Sanitize the name more (get rid of symbols and add a limit)
        // 1. Sanitize the string so it's more predictable.
        std::string sanitizedFolderName = name;
        std::ranges::transform(sanitizedFolderName, sanitizedFolderName.begin(),
                               [](const unsigned char c){ return std::tolower(c); });
        std::ranges::replace(sanitizedFolderName, ' ', '_');
        auto [first, last] = std::ranges::remove_if(sanitizedFolderName, [](char c) {
            return std::string("/\\?%*:|\"<>").find(c) != std::string::npos;
        });
        sanitizedFolderName.erase(first, last);

        // 2. Make the project by adding the .dnd extension.
        const std::filesystem::path dndFolder = std::filesystem::path(EngineSettings::getInstance().projectPath) / (sanitizedFolderName + ".dnd");

        try {
            if (!std::filesystem::create_directories(dndFolder)) {
                std::cout << "File already exists!" << std::endl;
                return false; // TODO: Change this to a UI error when making the project
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cout << "Failed in creating project: " << e.what() << std::endl;
            return false;
        }

        // 3. Write the project.json file for the project
        std::filesystem::path projectJsonPath = dndFolder / "project.json";
        nlohmann::json projectJson = dndProjectDefaults::createDefaultProjectJson(name, author);

        std::ofstream file(projectJsonPath);
        if (file.is_open()) {
            file << std::setw(4) << projectJson << std::endl;
            file.close();
            std::cout << "JSON file created successfully" << std::endl;
        } else {
            std::cerr << "Error: Could not open file for writing: " << projectJsonPath << std::endl;
            return false;
        }

        // 4. Create folders and populate them with .json files.
        for (const std::string& folder : dndProjectDefaults::defaultFolders) {
            std::filesystem::create_directories(dndFolder / folder);
            if (folder == "maps" || folder == "campaign_rules" || folder == "characters")
                continue;
            // TODO: Create .json files in each (dndFolder / folder)
        }

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
            std::cout << "Failed: wrong extension - got " << std::filesystem::path(dndPath).extension() << std::endl;
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