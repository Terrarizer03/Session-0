//
// Created by Terrarizer on 16/03/2026.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include "ProjectDefaults.h"
#include "Core/Loaders/EngineSettings.h"
#include "Core/Loaders/ProjectLoader.h"
#include "Core/Utilities/helpers.h"

std::vector<std::string> zeroProjectDefaults::defaultFolders = { "maps", "characters", "campaign_rules", "audio" };

nlohmann::json zeroProjectDefaults::createDefaultProjectJson(const std::string& name, const std::string& author) {
    nlohmann::json data;

    std::string dateStr = zeroHelpers::getCurrentTime();

    data["name"] = name;
    data["metadata"]["version"] = EngineSettings::getInstance().version;
    data["metadata"]["author"] = author;
    data["metadata"]["timeCreated"] = dateStr;
    data["metadata"]["timeModified"] = dateStr;
    data["mapPaths"] = std::unordered_map<std::string, std::string>{};
    data["characterPaths"] = std::unordered_map<std::string, std::string>{};
    data["rules"] = std::unordered_map<std::string, std::string>{};

    return data;
}

ProjectInfo zeroProjectDefaults::createDefaultMap(const std::string& mapName, const std::string& projectFile) {
        /*
         * Basic outline for map creation
         *
         * create the map folder, add the map.json file to it,
         * add the folders, and rewrite project.json's mapPaths to add
         * the path of the map folder.
         */

        // 1. Define the needed paths
        const std::filesystem::path projectPath = std::filesystem::path(EngineSettings::getInstance().projectPath) / projectFile; // Example: "C:/Users/NICO/Documents/SessionZero/Projects/project_name.zero"
        const std::filesystem::path projectJsonPath = std::filesystem::path(EngineSettings::getInstance().projectPath) / projectFile / "project.json"; // Example: "C:/Users/NICO/Documents/SessionZero/Projects/project_name.zero"
        const std::filesystem::path mapPath = projectPath / "maps" / mapName; // Example: "C:/Users/NICO/Documents/SessionZero/Projects/project_name.zero/maps/Tavern"
        const std::filesystem::path mapJsonPath = mapPath / "map.json"; // Example: C:/Users/NICO/Documents/SessionZero/Projects/project_name.zero/maps/Tavern/map.json"

        // 2. Create the map
        try {
            std::filesystem::create_directories(mapPath);
            std::filesystem::create_directories(mapPath / "models");
            std::filesystem::create_directories(mapPath / "shaders");
        } catch (const std::filesystem::filesystem_error& e) {
            std::cout << "Failed in creating map: " << e.what() << std::endl;
            return {};
        }

        // 3. Initialize the .json
        nlohmann::json mapData;

        mapData["name"] = mapName;
        mapData["objects"] = nlohmann::json::array();

        // 4. Create the map.json file
        std::ofstream map(mapJsonPath);
        if (map.is_open()) {
            map << std::setw(4) << mapData << std::endl;
            map.close();
            std::cout << "JSON file created successfully" << std::endl;
        } else {
            std::cerr << "Error: Could not open file for writing: " << mapData << std::endl;
            return {};
        }

        // 5. Copy everything in project.json into projectConfig
        nlohmann::json projectConfig;
        std::ifstream inFile(projectJsonPath);
        if (inFile.is_open()) {
            inFile >> projectConfig;
            inFile.close();
        } else {
            std::cerr << "Could not read project.json to update it!" << std::endl;
            return {};
        }

        // 6. Initialize the needed change to the project.json file
        projectConfig["mapPaths"][mapName] = "maps/" + mapName;

        // 7. Write the updated project data back to disk
        std::ofstream outFile(projectJsonPath);
        if (outFile.is_open()) {
            outFile << std::setw(4) << projectConfig << std::endl;
            outFile.close();
            std::cout << "Project and Map files updated successfully." << std::endl;
        }

        return zeroProjectLoader::loadProject(projectPath.string());
    }