//
// Created by Terrarizer on 08/03/2026.
//

#ifndef DNDCREATOR_ENGINESETTINGS_H
#define DNDCREATOR_ENGINESETTINGS_H
#include <string>

class EngineSettings {
    EngineSettings() {
        load("engineSettings.json");
    };
public:
    // Non-copyable, non-movable
    EngineSettings(const EngineSettings&) = delete;
    EngineSettings& operator=(const EngineSettings&) = delete;
    EngineSettings(EngineSettings&&) = delete;
    EngineSettings& operator=(EngineSettings&&) = delete;

    static EngineSettings& getInstance() {
        static EngineSettings instance;
        return instance;
    }

    // Default Settings
    int windowWidth = 1200;
    int windowHeight = 600;
    bool vsyncEnabled = true;
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    std::string projectPath = "C:/Users/NICO/Documents/D&D Creator/Projects"; // TODO: Don't hardcode this

    void load(const std::string& path);
    void save(const std::string& path);
};

#endif //DNDCREATOR_ENGINESETTINGS_H