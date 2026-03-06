//
// Created by Terrarizer on 04/03/2026.
//

#include "Matrix4.h"

#include <cmath>

namespace dndMath {
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

        float r = angle * (M_PI / 180.0f); // convert degrees to radians
        float c = cos(r);
        float s = sin(r);
        float t = 1.0f - c;

        Vector3 a = vec.normalized();

        result.m[0][0] = t * a.x * a.x + c;
        result.m[0][1] = t * a.x * a.y - s * a.z;
        result.m[0][2] = t * a.x * a.z + s * a.y;

        result.m[1][0] = t * a.x * a.y + s * a.z;
        result.m[1][1] = t * a.y * a.y + c;
        result.m[1][2] = t * a.y * a.z - s * a.x;

        result.m[2][0] = t * a.x * a.z - s * a.y;
        result.m[2][1] = t * a.y * a.z + s * a.x;
        result.m[2][2] = t * a.z * a.z + c;

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
        return {};
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
}
