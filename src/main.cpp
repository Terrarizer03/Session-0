#include "Engine/ZeroEngine.h"
#include "Engine/Core/Loaders/EngineSettings.h"
#include <iostream>
#include <filesystem>

int main() {
    std::cout << "Starting..." << std::endl;
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;
    ZeroEngine Engine(EngineSettings::getInstance().windowWidth, EngineSettings::getInstance().windowHeight);

    if (!Engine.initialize()) return -1;
    Engine.run();

    return 0;
}
