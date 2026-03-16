//
// Created by Terrarizer on 16/03/2026.
//

#include <chrono>
#include <string>
#include <format>
#include "helpers.h"
#include "../../Renderer/OpenGLRenderer/GLShader.h"

Material zeroHelpers::parseMaterial(const nlohmann::json &mat, const std::string &basePath) {
    Material material;

    if (mat.contains("color")) {
        auto& c = mat["color"];
        material.color = { c[0], c[1], c[2], c[3] };
    }

    if (mat.contains("shader")) {
        std::string vert = basePath + "/" + mat["shader"]["vertex"].get<std::string>();
        std::string frag = basePath + "/" + mat["shader"]["fragment"].get<std::string>();

        // TODO: Add a "default" check that uses default shaders provided by the engine
        material.shader = std::make_shared<GLShader>(vert.c_str(), frag.c_str());
    }

    return material;
}

Transform zeroHelpers::parseTransform(const nlohmann::json &trans) {
    Transform transform;

    if (trans.contains("position")) {
        auto& c = trans["position"];
        transform.position = { c[0], c[1], c[2] };
    }

    if (trans.contains("rotation")) {
        auto& c = trans["rotation"];
        transform.rotation = { c[0], c[1], c[2] };
    }

    if (trans.contains("scale")) {
        auto& c = trans["scale"];
        transform.scale = { c[0], c[1], c[2] };
    }

    return transform;
}

std::string zeroHelpers::toLower(const std::string& str) {
    std::string result = str;
    std::ranges::transform(result, result.begin(), ::tolower);
    return result;
}

std::string zeroHelpers::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto today = std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(now)};

    std::string dateStr = std::format("{}-{:02}-{:02}",
                              static_cast<int>(today.year()),
                              static_cast<unsigned>(today.month()),
                              static_cast<unsigned>(today.day())
                          );
    return dateStr;
}
