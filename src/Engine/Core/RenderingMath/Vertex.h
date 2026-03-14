//
// Created by Terrarizer on 01/02/2026.
//

#ifndef SESSIONZERO_VERTEX_H
#define SESSIONZERO_VERTEX_H
#include "../Math/Vector/Vector3/Vector3.h"
#include "../Math/Vector/Vector2.h"
#include "../Math/Vector/Vector4.h"

struct Vertex {
    zeroMath::Vector3 position, normal;
    zeroMath::Vector2 uv;
    zeroMath::Vector4 color;

    Vertex()
        : position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f ,0.0f), uv(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f, 0.0f) {}

    Vertex(const zeroMath::Vector3& _position, const zeroMath::Vector3& _normal, const zeroMath::Vector2& _uv, const zeroMath::Vector4& _color)
        : position(_position), normal(_normal), uv(_uv), color(_color) {}

    // --------------------- Vertex Methods ---------------------
    void setPosition(const zeroMath::Vector3 &_position) {
        this->position = _position;
    }

    void setNormal(const zeroMath::Vector3 &_normal) {
        this->normal = _normal;
    }

    void setUV(const zeroMath::Vector2 &_uv) {
        this->uv = _uv;
    }

    void setColor(const zeroMath::Vector4 &_color) {
        this->color = _color;
    }
};

#endif //SESSIONZERO_VERTEX_H