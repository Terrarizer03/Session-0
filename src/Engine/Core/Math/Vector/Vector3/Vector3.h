//
// Created by Terrarizer on 22/01/2026.
//

#ifndef DNDCREATOR_VECTOR3_H
#define DNDCREATOR_VECTOR3_H

namespace zeroMath {
    struct Vector3 {
        float x, y, z;

        constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

        constexpr Vector3(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}

        // Operator Overloading
        Vector3 operator+(const Vector3 &other) const {
            return { x + other.x, y + other.y, z + other.z};
        }

        Vector3 operator-(const Vector3 &other) const {
            return { x - other.x, y - other.y, z - other.z };
        }

        Vector3 operator*(const float scalar) const {
            return {x * scalar, y * scalar, z * scalar };
        }

        Vector3& operator+=(const Vector3& other) {
            x += other.x; y += other.y; z += other.z;
            return *this;
        }

        Vector3& operator-=(const Vector3& other) {
            x -= other.x; y -= other.y; z -= other.z;
            return *this;
        }

        Vector3& operator*=(const float scalar) {
            x *= scalar; y *= scalar; z *= scalar;
            return *this;
        }

        // --------------------- Vector3 Methods ---------------------
        /**
         * Used to return the magnitude of the given vector.
         */
        [[nodiscard]] Vector3 normalized() const;
        [[nodiscard]] Vector3 cross(const Vector3 &other) const;
        [[nodiscard]] float dot(const Vector3 &other) const;
    };

    inline Vector3 operator*(const float scalar, const Vector3& vector) {
        return vector * scalar;
    }
}


#endif //DNDCREATOR_VECTOR3_H