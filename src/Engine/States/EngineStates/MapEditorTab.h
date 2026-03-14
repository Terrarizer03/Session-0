//
// Created by Terrarizer on 14/03/2026.
//

#ifndef SESSIONZERO_MAPEDITORTAB_H
#define SESSIONZERO_MAPEDITORTAB_H
#include <string>
#include "../../Core/Project/MapData.h"
#include "../../Core/Nodes/Camera.h"

struct MapEditorTab {
    std::string name;
    MapData mapData = {};
    Camera camera = { {0.0f, 0.0f, 3.0f} };
    bool isOpen = true;
};

#endif //SESSIONZERO_MAPEDITORTAB_H