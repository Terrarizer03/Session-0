//
// Created by Terrarizer on 01/02/2026.
//

#ifndef DNDCREATOR_VERTEX_H
#define DNDCREATOR_VERTEX_H
#include "../Math/Vector/Vector3/Vector3.h"
#include "../Math/Vector/Vector2.h"
#include "../Math/Vector/Vector4.h"

struct Vertex {
    dndMath::Vector3 position, normal;
    dndMath::Vector2 uv;
    dndMath::Vector4 color;

    Vertex()
        : position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f ,0.0f), uv(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f, 0.0f) {}

    Vertex(const dndMath::Vector3& _position, const dndMath::Vector3& _normal, const dndMath::Vector2& _uv, const dndMath::Vector4& _color)
        : position(_position), normal(_normal), uv(_uv), color(_color) {}

    // --------------------- Vertex Methods ---------------------
    void setPosition(const dndMath::Vector3 &_position) {
        this->position = _position;
    }

    void setNormal(const dndMath::Vector3 &_normal) {
        this->normal = _normal;
    }

    void setUV(const dndMath::Vector2 &_uv) {
        this->uv = _uv;
    }

    void setColor(const dndMath::Vector4 &_color) {
        this->color = _color;
    }
};

#endif //DNDCREATOR_VERTEX_H