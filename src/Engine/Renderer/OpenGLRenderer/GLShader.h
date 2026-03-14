//
// Created by Terrarizer on 04/03/2026.
//

#ifndef DNDCREATOR_GLSHADER_H
#define DNDCREATOR_GLSHADER_H
#include "../IShader.h"
#include "glad/glad.h"
#include "../../Core/Math/Vector/Vector4.h"


class GLShader : public IShader {
public:
    GLShader(const char* vertexPath, const char* fragmentPath);
    void bind() const override;
    void unbind() const override;
    void setUniformMatrix4fv(const std::string& name, const zeroMath::Matrix4& matrix) const override;
    void setUniformVec3(const std::string& name, const zeroMath::Vector3& vector) const override;
    void setUniformVec4(const std::string& name, const zeroMath::Vector4& vector) const override;

    ~GLShader() override;
private:
    GLuint m_RendererID = 0;
    static GLuint CompileShader(const char* vertexSrc, const char* fragmentSrc);
};

#endif //DNDCREATOR_GLSHADER_H