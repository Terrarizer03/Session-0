//
// Created by Terrarizer on 09/03/2026.
//

#ifndef DNDCREATOR_MAPDATA_H
#define DNDCREATOR_MAPDATA_H
#include <string>
#include <vector>
#include "../RenderingMath/SceneObject.h"

struct MapData {
    std::string name;
    std::vector<SceneObject> objects;
    bool isDirty = false;
};

#endif //DNDCREATOR_MAPDATA_H