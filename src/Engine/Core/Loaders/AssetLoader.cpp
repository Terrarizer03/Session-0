//
// Created by Terrarizer on 05/03/2026.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "AssetLoader.h"
#include "../RenderingMath/Vertex.h"
#include "../RenderingMath/Face.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"


namespace zeroAssetLoader {

    Mesh loadOBJ(const std::string& path) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

        if (!warn.empty()) std::cout << "OBJ Warning: " << warn << "\n";
        if (!err.empty())  std::cout << "OBJ Error: "   << err  << "\n";
        if (!err.empty())  return { {}, {} }; // bail on error TODO: Make a UI warning

        std::vector<Vertex> vertices;
        std::vector<Face> faces;

        for (auto& shape : shapes) {
            unsigned int base = vertices.size();

            for (auto& index : shape.mesh.indices) {
                Vertex v;

                // Position - always exists
                v.position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };

                // Normal - might not exist
                if (index.normal_index >= 0) {
                    v.normal = {
                        attrib.normals[3 * index.normal_index + 0],
                        attrib.normals[3 * index.normal_index + 1],
                        attrib.normals[3 * index.normal_index + 2]
                    };
                } else {
                    v.normal = { 0.0f, 1.0f, 0.0f }; // default up normal
                }

                // UV - might not exist
                if (index.texcoord_index >= 0) {
                    v.uv = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        attrib.texcoords[2 * index.texcoord_index + 1]
                    };
                } else {
                    v.uv = { 0.0f, 0.0f };
                }

                v.color = { 1.0f, 1.0f, 1.0f, 1.0f };
                vertices.push_back(v);
            }

            for (int i = 0; i + 2 < static_cast<int>(shape.mesh.indices.size()); i += 3) {
                faces.push_back({
                    base + static_cast<unsigned int>(i),
                    base + static_cast<unsigned int>(i + 1),
                    base + static_cast<unsigned int>(i + 2)
                });
            }
        }

        return { vertices, faces };
    }

    std::string readFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cout << "Failed to open shader file: " << path << "\n";
            return "";
        }
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

}
