//
// Created by Terrarizer on 16/03/2026.
//

#include <chrono>
#include <string>
#include <format>
#include "helpers.h"

#include <iostream>

#include "../../Renderer/OpenGLRenderer/GLShader.h"

Material zeroHelpers::parseMaterial(const nlohmann::json &mat, const std::string &basePath) {
    Material material;

    if (mat.contains("color")) {
        auto& c = mat["color"];
        material.color = { c[0], c[1], c[2], c[3] };
    }

    if (mat.contains("shader")) {
        material.fragmentPath = mat["shader"]["fragment"].get<std::string>();
        material.vertexPath = mat["shader"]["vertex"].get<std::string>();

        std::string vert = resolvePath(material.vertexPath, basePath);
        std::string frag = resolvePath(material.fragmentPath, basePath);

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

std::string zeroHelpers::resolvePath(const std::string& meshPath, const std::string& mapFolder) {
    if (meshPath.starts_with("assets/")) {
        return meshPath;
    }

    return mapFolder + "/" + meshPath;
}

std::string zeroHelpers::generateUniqueName(const std::string& baseName, const MapData& mapData) {
    std::string candidate = baseName;
    int count = 1;
    bool exists = true;

    while (exists) {
        exists = false;
        for (const auto& obj : mapData.objects) {
            if (obj.name == candidate) {
                candidate = baseName + " (" + std::to_string(count) + ")";
                count++;
                exists = true;
                break;
            }
        }
    }

    return candidate;
}
