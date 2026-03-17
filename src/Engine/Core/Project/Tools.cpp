//
// Created by Terrarizer on 16/03/2026.
//

#include <filesystem>
#include "Tools.h"
#include "ProjectDefaults.h"
#include "../../Renderer/OpenGLRenderer/GLShader.h"
#include "../Loaders/AssetLoader.h"
#include "../Loaders/ProjectLoader.h"
#include "../Utilities/helpers.h"

void zeroTools::addPrimitive(MapData &mapData, Primitive primitive) {
    // 1. Generate the scene object
    SceneObject obj;

    switch (primitive) {
        case Primitive::CUBE:
            obj.mesh = zeroAssetLoader::getOrLoadMesh("assets/Models/cube_default.obj", mapData.assetCache);
            obj.name = zeroHelpers::generateUniqueName("Cube", mapData);
            obj.meshPath = "assets/Models/cube_default.obj";
        case Primitive::SPHERE:
            obj.mesh = zeroAssetLoader::getOrLoadMesh("assets/Models/sphere_default.obj", mapData.assetCache);
            obj.name = zeroHelpers::generateUniqueName("Sphere", mapData);
            obj.meshPath = "assets/Models/sphere_default.obj";
        case Primitive::PLANE:
            obj.mesh = zeroAssetLoader::getOrLoadMesh("assets/Models/plane_default.obj", mapData.assetCache);
            obj.name = zeroHelpers::generateUniqueName("Plane", mapData);
            obj.meshPath = "assets/Models/plane_default.obj";
    }

    obj.UUID = zeroProjectLoader::generateUUID();
    obj.transform.position = { 0.0f, 0.0f, 0.0f };
    obj.transform.rotation = { 0.0f, 0.0f, 0.0f };
    obj.transform.scale = { 1.0f, 1.0f, 1.0f };
    obj.material.color = { 1.0f, 1.0f, 1.0f, 1.0f };

    obj.material.fragmentPath = "assets/Shaders/default.frag";
    obj.material.vertexPath = "assets/Shaders/default.vert";
    obj.material.shader = std::make_shared<GLShader>(obj.material.vertexPath.c_str(), obj.material.fragmentPath.c_str());

    // 2. Add sceneObject to mapData and set isDirty to true
    mapData.objects.push_back(obj);
    if (!mapData.isDirty)
        mapData.isDirty = true;
}