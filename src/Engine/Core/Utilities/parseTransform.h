//
// Created by Terrarizer on 09/03/2026.
//

#ifndef SESSIONZERO_PARSETRANSFORM_H
#define SESSIONZERO_PARSETRANSFORM_H
#include "nlohmann/json.hpp"
#include "../RenderingMath/Transform.h"

namespace zeroHelper {
    inline Transform parseTransform(const nlohmann::json& trans) {
        Transform transform;

        if (trans.contains("position")) {
            auto& c = trans["position"];
            transform.position = { c[0], c[1], c[2] };
        }

        if (trans.contains("rotation")) {
            auto& c = trans["rotation"];
            transform.rotation = { c[0], c[1], c[2] };
        }

        if (trans.contains("scale")) {
            auto& c = trans["scale"];
            transform.scale = { c[0], c[1], c[2] };
        }

        return transform;
    }
}

#endif //SESSIONZERO_PARSETRANSFORM_H