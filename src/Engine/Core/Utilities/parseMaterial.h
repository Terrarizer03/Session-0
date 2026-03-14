//
// Created by Terrarizer on 09/03/2026.
//

#ifndef SESSIONZERO_PARSEMATERIAL_H
#define SESSIONZERO_PARSEMATERIAL_H
#include "nlohmann/json.hpp"
#include "../RenderingMath/Material.h"
#include "../../Renderer/OpenGLRenderer/GLShader.h"

namespace zeroHelper {
    inline Material parseMaterial(const nlohmann::json& mat, const std::string& basePath) {
        Material material;

        if (mat.contains("color")) {
            auto& c = mat["color"];
            material.color = { c[0], c[1], c[2], c[3] };
        }

        if (mat.contains("shader")) {
            std::string vert = basePath + "/" + mat["shader"]["vertex"].get<std::string>();
            std::string frag = basePath + "/" + mat["shader"]["fragment"].get<std::string>();

            // TODO: Add a "default" check that uses default shaders provided by the engine
            material.shader = std::make_shared<GLShader>(vert.c_str(), frag.c_str());
        }

        return material;
    }
}

#endif //SESSIONZERO_PARSEMATERIAL_H