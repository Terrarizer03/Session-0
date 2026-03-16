#include "Engine/ZeroEngine.h"
#include "Engine/Core/Loaders/EngineSettings.h"

int main() {
    ZeroEngine Engine(EngineSettings::getInstance().windowWidth, EngineSettings::getInstance().windowHeight);

    if (!Engine.initialize()) return -1;
    Engine.run();

    return 0;
}
