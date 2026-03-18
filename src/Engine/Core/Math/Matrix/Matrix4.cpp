//
// Created by Terrarizer on 04/03/2026.
//

#include "Matrix4.h"

#include <cmath>

namespace zeroMath {
    Matrix4 Matrix4::identity() {
        Matrix4 result = {};
        result.m[0][0] = 1.0f;
        result.m[1][1] = 1.0f;
        result.m[2][2] = 1.0f;
        result.m[3][3] = 1.0f;
        return result;
    }

    Matrix4 Matrix4::translate(const Vector3& vec) {
        Matrix4 result = identity();
        result.m[0][3] = vec.x;
        result.m[1][3] = vec.y;
        result.m[2][3] = vec.z;
        return result;
    }

    Matrix4 Matrix4::scale(const Vector3& vec) {
        Matrix4 result = identity();
        result.m[0][0] = vec.x;
        result.m[1][1] = vec.y;
        result.m[2][2] = vec.z;
        return result;
    }

    Matrix4 Matrix4::rotate(float angle, const Vector3& vec) {
        Matrix4 result = identity();

        float M_PI = 3.1415926535f;
        const auto R = static_cast<float>(angle * (M_PI / 180.0f)); // convert degrees to radians
        const float C = std::cos(R);
        const float S = std::sin(R);
        const float T = 1.0f - C;

        const Vector3 A = vec.normalized();

        result.m[0][0] = T * A.x * A.x + C;
        result.m[0][1] = T * A.x * A.y - S * A.z;
        result.m[0][2] = T * A.x * A.z + S * A.y;

        result.m[1][0] = T * A.x * A.y + S * A.z;
        result.m[1][1] = T * A.y * A.y + C;
        result.m[1][2] = T * A.y * A.z - S * A.x;

        result.m[2][0] = T * A.x * A.z - S * A.y;
        result.m[2][1] = T * A.y * A.z + S * A.x;
        result.m[2][2] = T * A.z * A.z + C;

        return result;
    }

    Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far) {
        Matrix4 result = {};

        float r = fov * (3.14159265f / 180.0f); // degrees to radians
        float f = 1.0f / std::tan(r / 2.0f);         // focal length

        result.m[0][0] = f / aspect;
        result.m[1][1] = f;
        result.m[2][2] = (far + near) / (near - far);
        result.m[2][3] = (2.0f * far * near) / (near - far);
        result.m[3][2] = -1.0f;

        return result;
    }

    Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far) {
        return {}; // TODO: finish this function maybe lmao
    }

    Matrix4 Matrix4::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
        Vector3 forward = (target - eye).normalized();
        Vector3 right   = forward.cross(up).normalized();
        Vector3 cameraUp = right.cross(forward);

        Matrix4 result = identity();

        result.m[0][0] =  right.x;
        result.m[0][1] =  right.y;
        result.m[0][2] =  right.z;
        result.m[0][3] = -right.dot(eye);

        result.m[1][0] =  cameraUp.x;
        result.m[1][1] =  cameraUp.y;
        result.m[1][2] =  cameraUp.z;
        result.m[1][3] = -cameraUp.dot(eye);

        result.m[2][0] = -forward.x;
        result.m[2][1] = -forward.y;
        result.m[2][2] = -forward.z;
        result.m[2][3] =  forward.dot(eye);

        result.m[3][3] =  1.0f;

        return result;
    }

    Matrix4 Matrix4::operator*(const Matrix4& other) const {
        Matrix4 result = {};

        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result.m[row][col] =
                    m[row][0] * other.m[0][col] +
                    m[row][1] * other.m[1][col] +
                    m[row][2] * other.m[2][col] +
                    m[row][3] * other.m[3][col];
            }
        }

        return result;
    }

    Vector4 Matrix4::operator*(const Vector4 &vec) const {
        return {
            (m[0][0]*vec.x) + (m[0][1]*vec.y) + (m[0][2]*vec.z) + (m[0][3]*vec.w),
            (m[1][0]*vec.x) + (m[1][1]*vec.y) + (m[1][2]*vec.z) + (m[1][3]*vec.w),
            (m[2][0]*vec.x) + (m[2][1]*vec.y) + (m[2][2]*vec.z) + (m[2][3]*vec.w),
            (m[3][0]*vec.x) + (m[3][1]*vec.y) + (m[3][2]*vec.z) + (m[3][3]*vec.w)
            };
        }

    Vector3 Matrix4::operator*(const Vector3& v) const {
        float x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
        float y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
        float z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
        float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];

        if (w != 0.0f) {
            x /= w;
            y /= w;
            z /= w;
        }

        return { x, y, z };
    }

    [[nodiscard]] Matrix4 Matrix4::transpose() const {
        Matrix4 result;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = m[j][i];
            }
        }

        return result;
    }

    [[nodiscard]] Matrix4 Matrix4::inverse() const {
        // Thank god for AI bruh, I ain't writing this out LMAO
        Matrix4 inv;
        float invOut[16];
        const float* mat = &m[0][0];

        invOut[0] = mat[5]  * mat[10] * mat[15] -
                    mat[5]  * mat[11] * mat[14] -
                    mat[9]  * mat[6]  * mat[15] +
                    mat[9]  * mat[7]  * mat[14] +
                    mat[13] * mat[6]  * mat[11] -
                    mat[13] * mat[7]  * mat[10];

        invOut[4] = -mat[4]  * mat[10] * mat[15] +
                     mat[4]  * mat[11] * mat[14] +
                     mat[8]  * mat[6]  * mat[15] -
                     mat[8]  * mat[7]  * mat[14] -
                     mat[12] * mat[6]  * mat[11] +
                     mat[12] * mat[7]  * mat[10];

        invOut[8] = mat[4]  * mat[9] * mat[15] -
                    mat[4]  * mat[11] * mat[13] -
                    mat[8]  * mat[5] * mat[15] +
                    mat[8]  * mat[7] * mat[13] +
                    mat[12] * mat[5] * mat[11] -
                    mat[12] * mat[7] * mat[9];

        invOut[12] = -mat[4]  * mat[9] * mat[14] +
                      mat[4]  * mat[10] * mat[13] +
                      mat[8]  * mat[5] * mat[14] -
                      mat[8]  * mat[6] * mat[13] -
                      mat[12] * mat[5] * mat[10] +
                      mat[12] * mat[6] * mat[9];

        invOut[1] = -mat[1]  * mat[10] * mat[15] +
                     mat[1]  * mat[11] * mat[14] +
                     mat[9]  * mat[2] * mat[15] -
                     mat[9]  * mat[3] * mat[14] -
                     mat[13] * mat[2] * mat[11] +
                     mat[13] * mat[3] * mat[10];

        invOut[5] = mat[0]  * mat[10] * mat[15] -
                    mat[0]  * mat[11] * mat[14] -
                    mat[8]  * mat[2] * mat[15] +
                    mat[8]  * mat[3] * mat[14] +
                    mat[12] * mat[2] * mat[11] -
                    mat[12] * mat[3] * mat[10];

        invOut[9] = -mat[0]  * mat[9] * mat[15] +
                     mat[0]  * mat[11] * mat[13] +
                     mat[8]  * mat[1] * mat[15] -
                     mat[8]  * mat[3] * mat[13] -
                     mat[12] * mat[1] * mat[11] +
                     mat[12] * mat[3] * mat[9];

        invOut[13] = mat[0]  * mat[9] * mat[14] -
                     mat[0]  * mat[10] * mat[13] -
                     mat[8]  * mat[1] * mat[14] +
                     mat[8]  * mat[2] * mat[13] +
                     mat[12] * mat[1] * mat[10] -
                     mat[12] * mat[2] * mat[9];

        invOut[2] = mat[1]  * mat[6] * mat[15] -
                    mat[1]  * mat[7] * mat[14] -
                    mat[5]  * mat[2] * mat[15] +
                    mat[5]  * mat[3] * mat[14] +
                    mat[13] * mat[2] * mat[7] -
                    mat[13] * mat[3] * mat[6];

        invOut[6] = -mat[0]  * mat[6] * mat[15] +
                     mat[0]  * mat[7] * mat[14] +
                     mat[4]  * mat[2] * mat[15] -
                     mat[4]  * mat[3] * mat[14] -
                     mat[12] * mat[2] * mat[7] +
                     mat[12] * mat[3] * mat[6];

        invOut[10] = mat[0]  * mat[5] * mat[15] -
                     mat[0]  * mat[7] * mat[13] -
                     mat[4]  * mat[1] * mat[15] +
                     mat[4]  * mat[3] * mat[13] +
                     mat[12] * mat[1] * mat[7] -
                     mat[12] * mat[3] * mat[5];

        invOut[14] = -mat[0]  * mat[5] * mat[14] +
                      mat[0]  * mat[6] * mat[13] +
                      mat[4]  * mat[1] * mat[14] -
                      mat[4]  * mat[2] * mat[13] -
                      mat[12] * mat[1] * mat[6] +
                      mat[12] * mat[2] * mat[5];

        invOut[3] = -mat[1] * mat[6] * mat[11] +
                     mat[1] * mat[7] * mat[10] +
                     mat[5] * mat[2] * mat[11] -
                     mat[5] * mat[3] * mat[10] -
                     mat[9] * mat[2] * mat[7] +
                     mat[9] * mat[3] * mat[6];

        invOut[7] = mat[0] * mat[6] * mat[11] -
                    mat[0] * mat[7] * mat[10] -
                    mat[4] * mat[2] * mat[11] +
                    mat[4] * mat[3] * mat[10] +
                    mat[8] * mat[2] * mat[7] -
                    mat[8] * mat[3] * mat[6];

        invOut[11] = -mat[0] * mat[5] * mat[11] +
                      mat[0] * mat[7] * mat[9] +
                      mat[4] * mat[1] * mat[11] -
                      mat[4] * mat[3] * mat[9] -
                      mat[8] * mat[1] * mat[7] +
                      mat[8] * mat[3] * mat[5];

        invOut[15] = mat[0] * mat[5] * mat[10] -
                     mat[0] * mat[6] * mat[9] -
                     mat[4] * mat[1] * mat[10] +
                     mat[4] * mat[2] * mat[9] +
                     mat[8] * mat[1] * mat[6] -
                     mat[8] * mat[2] * mat[5];

        float det = mat[0] * invOut[0] + mat[1] * invOut[4] + mat[2] * invOut[8] + mat[3] * invOut[12];

        if (det == 0.0f) {
            return Matrix4(); // return identity or zero depending on your design
        }

        det = 1.0f / det;

        for (int i = 0; i < 16; i++) {
            ((float*)inv.m)[i] = invOut[i] * det;
        }

        return inv;
    }
}
