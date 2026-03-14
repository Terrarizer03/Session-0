//
// Created by Terrarizer on 08/03/2026.
//

#ifndef SESSIONZERO_ENGINESETTINGS_H
#define SESSIONZERO_ENGINESETTINGS_H
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
    int windowWidth = 1920;
    int windowHeight = 1080;
    bool vsyncEnabled = true;
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    std::string projectPath = "C:/Users/NICO/Documents/SessionZero/Projects"; // TODO: Don't hardcode this
    std::string version = "0.0.1";

    void load(const std::string& path);
    void save(const std::string& path);
};

#endif //SESSIONZERO_ENGINESETTINGS_H