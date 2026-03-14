//
// Created by Terrarizer on 22/01/2026.
//

#ifndef SESSIONZERO_VECTOR2_H
#define SESSIONZERO_VECTOR2_H

namespace zeroMath {
    struct Vector2 {
        float x, y;

        constexpr Vector2() : x(0.0f), y(0.0f) {}

        constexpr Vector2(const float _x, const float _y) : x(_x), y(_y) {}

        Vector2 operator+(const Vector2 &other) const {
            return { other.x + x, other.y + y };
        }

        Vector2 operator-(const Vector2 &other) const {
            return { other.x - x, other.y - y };
        }

        Vector2 operator*(const float scalar) const {
            return { scalar * x, scalar * y };
        }
        
        Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
    };

    inline Vector2 operator*(const float scalar, const Vector2 &vector) {
        return vector * scalar;
    }
}


#endif //SESSIONZERO_VECTOR2_H