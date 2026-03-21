//
// Created by Terrarizer on 05/03/2026.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "AssetLoader.h"
#include "Core/RenderingMath/Vertex.h"
#include "Core/RenderingMath/Face.h"

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
            std::cout << "Failed to open file at: " << std::filesystem::absolute(path) << "\n";
            return "";
        }
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    std::shared_ptr<Mesh> getOrLoadMesh(const std::string& path, AssetCache& meshCache) {
        // Find mesh in asset cache
        auto it = meshCache.loaded_meshes.find(path);
        if (it != meshCache.loaded_meshes.end()) {
            return it->second;
        }

        // if the mesh doesn't exist in the cache, load, cache, and return it.
        auto mesh = std::make_shared<Mesh>(loadOBJ(path));

        for (const auto& v : mesh->vertices) {
            mesh->localExtentsMin.x = std::min(mesh->localExtentsMin.x, v.position.x);
            mesh->localExtentsMin.y = std::min(mesh->localExtentsMin.y, v.position.y);
            mesh->localExtentsMin.z = std::min(mesh->localExtentsMin.z, v.position.z);
            mesh->localExtentsMax.x = std::max(mesh->localExtentsMax.x, v.position.x);
            mesh->localExtentsMax.y = std::max(mesh->localExtentsMax.y, v.position.y);
            mesh->localExtentsMax.z = std::max(mesh->localExtentsMax.z, v.position.z);
        }

        meshCache.loaded_meshes[path] = mesh;
        return mesh;
    }
}
