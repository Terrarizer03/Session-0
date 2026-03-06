//
// Created by Terrarizer on 04/03/2026.
//

#ifndef DNDCREATOR_GLSHADER_H
#define DNDCREATOR_GLSHADER_H
#include "../IShader.h"
#include "glad/glad.h"

class GLShader : public IShader {
public:
    GLShader(const char* vertexPath, const char* fragmentPath);
    void Bind() const override;
    void Unbind() const override;
    void SetUniformMatrix4fv(const std::string& name, const dndMath::Matrix4& matrix) const override;
    void SetUniformVec3(const std::string &name, const dndMath::Vector3 &vector) const override;

    ~GLShader() override;
private:
    GLuint m_RendererID = 0;
    static GLuint CompileShader(const char* vertexSrc, const char* fragmentSrc);
};

#endif //DNDCREATOR_GLSHADER_H