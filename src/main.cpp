#include "Engine/DnDEngine.h"
#include "Engine/Core/Loaders/EngineSettings.h"
#include "Engine/Core/Loaders/ProjectLoader.h"

int main() {
    DnDEngine Engine(EngineSettings::getInstance().windowWidth, EngineSettings::getInstance().windowHeight);

    if (!Engine.initialize()) return -1;
    Engine.run();

    return 0;
}
