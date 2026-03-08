//
// Created by Terrarizer on 08/03/2026.
//

#ifndef DNDCREATOR_PROJECTLOADER_H
#define DNDCREATOR_PROJECTLOADER_H
#include "../Rendering Math/ProjectContext.h"

namespace dndProjectLoader {
    ProjectContext loadProject(const std::string& path);
    std::string saveProject(/* const ProjectContext */ const std::string& path);
}


#endif //DNDCREATOR_PROJECTLOADER_H