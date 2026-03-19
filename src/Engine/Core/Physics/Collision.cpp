//
// Created by Terrarizer on 18/03/2026.
//

#include "Collision.h"

bool zeroPhysics::rayIntersectsAABB(const Ray& ray, const AABB& box, float& outDistance) {
    float txmin = (box.min.x - ray.origin.x) / ray.direction.x;
    float txmax = (box.max.x - ray.origin.x) / ray.direction.x;

    if (txmin > txmax) std::swap(txmin, txmax);

    float tymin = (box.min.y - ray.origin.y) / ray.direction.y;
    float tymax = (box.max.y - ray.origin.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((txmin > tymax) || (tymin > txmax)) return false;

    if (tymin > txmin) txmin = tymin;
    if (tymax < txmax) txmax = tymax;

    float tzmin = (box.min.z - ray.origin.z) / ray.direction.z;
    float tzmax = (box.max.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((txmin > tzmax) || (tzmin > txmax)) return false;

    if (tzmin > txmin) txmin = tzmin;
    if (tzmax < txmax) txmax = tzmax;

    outDistance = txmin;
    return txmin >= 0;
}
