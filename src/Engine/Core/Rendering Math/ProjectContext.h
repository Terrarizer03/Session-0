//
// Created by Terrarizer on 06/03/2026.
//

#ifndef DNDCREATOR_PROJECTCONTEXT_H
#define DNDCREATOR_PROJECTCONTEXT_H
#include <vector>
#include "SceneObject.h"

struct ProjectContext {
    std::string name;
    std::vector<SceneObject> objects;
};

#endif //DNDCREATOR_PROJECTCONTEXT_H