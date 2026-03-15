//
// Created by Terrarizer on 08/03/2026.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>
#include "../Utilities/parseMaterial.h"
#include "../Utilities/parseTransform.h"
#include "ProjectLoader.h"
#include "AssetLoader.h"
#include "../Project/ProjectDefaults.h"
#include "nlohmann/json.hpp"

namespace zeroProjectLoader {
    ProjectInfo loadProject(const std::string& zeroPath) {
        /*
         * This check will probably never be used since this function will only be
         * called when loading a valid project. Still good to have it tho just in case
         */
        if (!std::filesystem::exists(zeroPath))
            return {}; // TODO: Change this to an error that visually shows in-engine

        ProjectInfo projectInfo;

        std::ifstream file(std::filesystem::path(zeroPath) / "project.json");

        if (!file.is_open()) {
            std::cout << "Failed to open file: " << zeroPath + "/project.json" << std::endl;
            return {};
        }

        if (file.peek() == std::ifstream::traits_type::eof())
            return {}; // TODO: Change this to an error that says "This file is empty."

        nlohmann::json data;

        try {
            data = nlohmann::json::parse(file);
        } catch (const nlohmann::json::exception& e) {
            std::cout << "Failed to parse" << zeroPath << ": " << e.what() << std::endl;
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
            path = zeroPath + "/" + path;

        projectInfo.characterPaths = data.value("characterPaths", std::unordered_map<std::string, std::string>{});
        for (auto &path: projectInfo.characterPaths | std::views::values)
            path = zeroPath + "/" + path;

        projectInfo.rules = data.value("rules", std::unordered_map<std::string, std::string>{}); // Maybe add the zeroPath to these too.

        return projectInfo;
    }

    void saveProject(const ProjectInfo& info, const std::string& zeroPath) {

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
        std::filesystem::path mapPath = std::filesystem::path(mapFolder) / "map.json";
        // Example: "my_campaign.zero/maps/Tavern/map.json"

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

                if (obj.contains("UUID")) {
                    sceneObj.UUID = obj["UUID"];
                }
                else {
                    sceneObj.UUID = generateUUID();
                    mapData.isDirty = true;
                }

                // mesh field is a path string
                if (!obj.contains("mesh")) continue;
                std::string meshPath = obj["mesh"].get<std::string>();

                std::string fullMeshPath = mapFolder + "/" + meshPath;
                // Example: "my_campaign.zero/maps/Tavern/models/table.obj"

                sceneObj.mesh = std::make_shared<Mesh>(std::move(zeroAssetLoader::loadOBJ(fullMeshPath)));

                if (obj.contains("material")) {
                    /*
                     * Not sure if mapFolder being passed is a hack, but the helper does need
                     * the base path... So I guess not, it's 10pm I have to sleep tho
                     */
                    sceneObj.material = zeroHelper::parseMaterial(obj["material"], mapFolder);
                }

                if (obj.contains("transform")) {
                    sceneObj.transform = zeroHelper::parseTransform(obj["transform"]);
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

    std::string createProject(const std::string& name, const std::string& author) {
        /*
         * Quick outline in Project Creation:
         *
         * Take the name and pass it. Check if it exists first, if not then create the folder.
         * In the folder create a project.json that has default values. Once created, populate it with
         * folders (maps/, models/, characters/, campaign_rules/, and audio/) that have their own .json files.
         */

        // 1. Sanitize the string so it's more predictable.
        std::string sanitizedFolderName = name;
        std::ranges::transform(sanitizedFolderName, sanitizedFolderName.begin(),
                               [](const unsigned char c){ return std::tolower(c); });
        std::ranges::replace(sanitizedFolderName, ' ', '_');
        auto [first, last] = std::ranges::remove_if(sanitizedFolderName, [](char c) {
            return std::string("/\\?%*:|\"<>").find(c) != std::string::npos;
        });
        sanitizedFolderName.erase(first, last);

        // 2. Make the project by adding the .zero extension.
        const std::filesystem::path zeroFolder = std::filesystem::path(EngineSettings::getInstance().projectPath) / (sanitizedFolderName + ".zero");

        try {
            if (!std::filesystem::create_directories(zeroFolder)) {
                std::cout << "File already exists!" << std::endl;
                return "false"; // TODO: Change this to a UI error when making the project
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cout << "Failed in creating project: " << e.what() << std::endl;
            return "false";
        }

        // 3. Write the project.json file for the project
        std::filesystem::path projectJsonPath = zeroFolder / "project.json";
        nlohmann::json projectJson = zeroProjectDefaults::createDefaultProjectJson(name, author);

        std::ofstream file(projectJsonPath);
        if (file.is_open()) {
            file << std::setw(4) << projectJson << std::endl;
            file.close();
            std::cout << "JSON file created successfully" << std::endl;
        } else {
            std::cerr << "Error: Could not open file for writing: " << projectJsonPath << std::endl;
            return "false";
        }

        // 4. Create folders and populate them with .json files.
        for (const std::string& folder : zeroProjectDefaults::defaultFolders) {
            std::filesystem::create_directories(zeroFolder / folder);
            if (folder == "maps" || folder == "campaign_rules" || folder == "characters")
                continue;
            // TODO: Create .json files in each (zeroFolder / folder)
        }

        return zeroFolder.string();
    }

    bool isValidProject(const std::string& zeroPath) {
        // Check folder exists
        if (!std::filesystem::exists(zeroPath)) {
            std::cout << "Failed: path doesn't exist\n";
            return false;
        }

        // Check .zer extension
        if (std::filesystem::path(zeroPath).extension() != ".zero") {
            std::cout << "Failed: wrong extension - got " << std::filesystem::path(zeroPath).extension() << std::endl;
            return false;
        }


        // Check project.json exists
        std::string projectJsonPath = zeroPath + "/project.json";
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

    std::string generateUUID() {
        /*
         * Basic outline in generating a UUID
         *
         * Create a random string of numbers, randomize those to string,
         * have it be an exactly 32~ character string, and preface it with "zro".
         * Example output: "zro-a3f2b1c4-9e7d4f2a-b8c1d4e5-f6a7b8c9"
         */

        // Preface value
        std::string preface = "zro-";

        // 1. Create random integers
        static std::random_device rd;
        static std::mt19937 gen(rd());

        // 2. Turn it to hexadecimal
        std::stringstream UUID;
        for (int i = 0; i < 4; i++) {
            UUID << std::setfill('0') << std::setw(8) << std::hex << gen();
            if (i < 3) {
                UUID << "-";
            }
        }

        // return the UUID
        return preface + UUID.str();
    }
}