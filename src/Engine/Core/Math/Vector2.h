//
// Created by Terrarizer on 22/01/2026.
//

#ifndef DNDCREATOR_VECTOR2_H
#define DNDCREATOR_VECTOR2_H

namespace dndMath {
    struct Vector2 {
        float x, y;

        constexpr Vector2() : x(0.0f), y(0.0f) {}

        explicit constexpr Vector2(const float _x, const float _y) : x(_x), y(_y) {}

        Vector2 operator+(const Vector2 &other) const {
            return Vector2(other.x + x, other.y + y);
        }

        Vector2 operator-(const Vector2 &other) const {
            return Vector2(other.x - x, other.y - y);
        }

        Vector2 operator*(const float scalar) const {
            return Vector2(scalar * x, scalar * y);
        }
    };

    inline Vector2 operator*(const float scalar, const Vector2 &vector) {
        return vector * scalar;
    }
}


#endif //DNDCREATOR_VECTOR2_H