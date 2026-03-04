//
// Created by Terrarizer on 04/03/2026.
//

#ifndef DNDCREATOR_GLSHADER_H
#define DNDCREATOR_GLSHADER_H
#include "../IShader.h"
#include "glad/glad.h"

class GLShader : public IShader {
public:
    GLShader(const char* vertexSrc, const char* fragmentSrc);
    void Bind() const override;
    void Unbind() const override;
    void SetUniform(const std::string&, const dndMath::Matrix4&) override;

    ~GLShader() override;
private:
    GLuint m_RendererID = 0;
    static void CompileShader(const char& vertexSrc, const char& fragmentSrc);
};

#endif //DNDCREATOR_GLSHADER_H