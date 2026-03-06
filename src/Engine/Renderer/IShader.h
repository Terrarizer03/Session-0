//
// Created by Terrarizer on 04/03/2026.
//

#ifndef DNDCREATOR_ISHADER_H
#define DNDCREATOR_ISHADER_H
#include <string>
#include "../Core/Math/Matrix/Matrix4.h"

struct IShader {
    virtual ~IShader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void SetUniformMatrix4fv(const std::string& name, const dndMath::Matrix4& matrix) const = 0;
    virtual void SetUniformVec3(const std::string& name, const dndMath::Vector3& vector) const = 0;
};

#endif //DNDCREATOR_ISHADER_H