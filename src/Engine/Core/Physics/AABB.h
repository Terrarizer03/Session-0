//
// Created by Terrarizer on 18/03/2026.
//

#ifndef SESSIONZERO_AABB_H
#define SESSIONZERO_AABB_H
#include "../Math/Vector/Vector3/Vector3.h"
#include "../RenderingMath/Ray.h"

namespace zeroPhysics {
    struct AABB {
        zeroMath::Vector3 min;
        zeroMath::Vector3 max;
    };

    bool rayIntersectsAABB(const Ray& ray, const AABB& aabb, float& outDistance);
}



#endif //SESSIONZERO_AABB_H