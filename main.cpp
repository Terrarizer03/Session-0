#include "src/Engine/DnDEngine.h"

int main() {
    DnDEngine Engine;

    if (!Engine.initialize()) return -1;
    Engine.run();

    return 0;
}