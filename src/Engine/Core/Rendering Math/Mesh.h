//
// Created by Terrarizer on 01/02/2026.
//

#ifndef DNDCREATOR_MESH_H
#define DNDCREATOR_MESH_H
#include <vector>
#include "Face.h"
#include "Vertex.h"
#include "glad/glad.h"

class Mesh {
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    int m_IndexCount = 0;
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    Mesh(const std::vector<Vertex> &vertices, const std::vector<Face> &faces);
    ~Mesh();
    void _upload();
    void draw() const;
};

#endif //DNDCREATOR_MESH_H