//
// Created by Terrarizer on 21/03/2026.
//

#include "LineMesh.h"

LineMesh::LineMesh(const std::vector<zeroMath::Vector3> &points) {
    m_VertexCount = static_cast<int>(points.size());

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(zeroMath::Vector3), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(zeroMath::Vector3), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

LineMesh::~LineMesh() {
    if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO);
    if (m_VBO != 0) glDeleteBuffers(1, &m_VBO);
}

void LineMesh::draw() const {
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_LINES, 0 , m_VertexCount);
    glBindVertexArray(0);
}

LineMesh::LineMesh(LineMesh&& other) noexcept
    : m_VAO(other.m_VAO), m_VBO(other.m_VBO), m_VertexCount(other.m_VertexCount) {
    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_VertexCount = 0;
}

LineMesh& LineMesh::operator=(LineMesh&& other) noexcept {
    if (this != &other) {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        m_VAO = other.m_VAO;
        m_VBO = other.m_VBO;
        m_VertexCount = other.m_VertexCount;

        other.m_VAO = 0;
        other.m_VBO = 0;
        other.m_VertexCount = 0;
    }
    return *this;
}