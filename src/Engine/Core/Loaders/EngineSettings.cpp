//
// Created by Terrarizer on 08/03/2026.
//

#include <fstream>
#include <iostream>
#include <filesystem>
#include "EngineSettings.h"

#include "nlohmann/json.hpp"

void EngineSettings::load(const std::string &path) {
    isLoaded = true;

    if (!std::filesystem::exists(path)) {
        save(path);
        return;
    }

    std::ifstream file(path);

    if (file.peek() == std::ifstream::traits_type::eof()) {
        save(path); // file exists but empty, write defaults
        return;
    }

    nlohmann::json data;

    try {
        data = nlohmann::json::parse(file);
    } catch (const nlohmann::json::exception& e) {
        std::cout << "Failed to parse engineSettings.json: " << e.what() << "\n";
        save(path); // malformed, overwrite with defaults
        return;
    }

    windowWidth = data.value("windowWidth", 1920);
    windowHeight = data.value("windowHeight", 1080);
    vsyncEnabled = data.value("vsyncEnabled", true);
    debugMode = data.value("debugMode", false);
    fov = data.value("fov", 45.0f);
    nearPlane = data.value("nearPlane", 0.1f);
    farPlane = data.value("farPlane", 1000.0f);
    projectPath = data.value("projectPaths", "C:/Users/NICO/Documents/SessionZero/Projects"); // TODO: Change this
    version = data.value("version", std::string("1.0"));
}

void EngineSettings::save(const std::string &path) {
    nlohmann::json data;
    data["windowWidth"] = windowWidth;
    data["windowHeight"] = windowHeight;
    data["vsyncEnabled"] = vsyncEnabled;
    data["debugMode"] = debugMode;
    data["fov"] = fov;
    data["nearPlane"] = nearPlane;
    data["farPlane"] = farPlane;
    data["projectPath"] = projectPath;
    data["version"] = version;

    std::ofstream file(path);
    file << data.dump(4);
}