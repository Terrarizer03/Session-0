#include "src/Engine/DnDEngine.h"

int main() {
    DnDEngine Engine(1200, 900);

    if (!Engine.initialize()) return -1;
    Engine.run();

    return 0;
}