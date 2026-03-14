//
// Created by Terrarizer on 01/02/2026.
//

#ifndef SESSIONZERO_MESH_H
#define SESSIONZERO_MESH_H
#include <vector>
#include "../Face.h"
#include "../Vertex.h"
#include "glad/glad.h"

class Mesh {
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    int m_IndexCount = 0;

    void upload();
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<Face>& faces);
    ~Mesh();

    void draw() const;

    // Non-copyable
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    // Movable
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
};

#endif //SESSIONZERO_MESH_H