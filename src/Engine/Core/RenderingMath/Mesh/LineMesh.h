//
// Created by Terrarizer on 21/03/2026.
//

#ifndef SESSIONZERO_LINEMESH_H
#define SESSIONZERO_LINEMESH_H
#include <vector>
#include "glad/glad.h"
#include "Core/Math/Vector/Vector3/Vector3.h"

class LineMesh {
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    int m_VertexCount = 0;
public:
    LineMesh(const std::vector<zeroMath::Vector3>& points);
    ~LineMesh();
    void draw() const;

    // Non-copyable
    LineMesh(const LineMesh&) = delete;
    LineMesh& operator=(const LineMesh&) = delete;

    // Movable
    LineMesh(LineMesh&& other) noexcept;
    LineMesh& operator=(LineMesh&& other) noexcept;
};


#endif //SESSIONZERO_LINEMESH_H