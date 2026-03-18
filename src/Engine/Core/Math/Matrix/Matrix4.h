//
// Created by Terrarizer on 22/01/2026.
//

#ifndef SESSIONZERO_MATRIX4_H
#define SESSIONZERO_MATRIX4_H
#include "../Vector/Vector4.h"
#include "../Vector/Vector3/Vector3.h"

namespace zeroMath {

    struct Matrix4 {
        float m[4][4];

        Matrix4() = default;

        static Matrix4 identity();
        static Matrix4 translate(const Vector3& vec);
        static Matrix4 scale(const Vector3& vec);
        static Matrix4 rotate(float angle, const Vector3& vec);

        static Matrix4 perspective(float fov, float aspect, float near, float far);
        static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
        static Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

        Matrix4 operator*(const Matrix4& other) const;
        Vector4 operator*(const Vector4& vec) const;
        Vector3 operator*(const Vector3& vec) const;


        [[nodiscard]] Matrix4 transpose() const;
        [[nodiscard]] Matrix4 inverse() const;

        [[nodiscard]] const float* data() const { return &m[0][0]; }
    };
}


#endif //SESSIONZERO_MATRIX4_H