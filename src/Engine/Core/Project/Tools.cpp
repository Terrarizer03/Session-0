//
// Created by Terrarizer on 16/03/2026.
//

#include <filesystem>
#include "Tools.h"
#include <iostream>
#include "Renderer/OpenGLRenderer/GLShader.h"
#include "Core/Loaders/AssetLoader.h"
#include "Core/Loaders/ProjectLoader.h"
#include "Core/Utilities/helpers.h"

void zeroTools::addPrimitive(MapData &mapData, Primitive primitive) {
    // 1. Generate the scene object
    SceneObject obj;

    switch (primitive) {
        case Primitive::CUBE:
            std::cout << "spawning cube \n";
            obj.mesh = zeroAssetLoader::getOrLoadMesh("assets/Models/cube_default.obj", mapData.assetCache);
            obj.name = zeroHelpers::generateUniqueName("Cube", mapData);
            obj.meshPath = "assets/Models/cube_default.obj";
            break;
        case Primitive::SPHERE:
            std::cout << "spawning sphere \n";
            obj.mesh = zeroAssetLoader::getOrLoadMesh("assets/Models/sphere_default.obj", mapData.assetCache);
            obj.name = zeroHelpers::generateUniqueName("Sphere", mapData);
            obj.meshPath = "assets/Models/sphere_default.obj";
            break;
        case Primitive::PLANE:
            std::cout << "spawning plane \n";
            obj.mesh = zeroAssetLoader::getOrLoadMesh("assets/Models/plane_default.obj", mapData.assetCache);
            obj.name = zeroHelpers::generateUniqueName("Plane", mapData);
            obj.meshPath = "assets/Models/plane_default.obj";
            break;
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

void zeroTools::deleteObject(MapData &mapData, const std::string& objUUID) {
    // This is actually fucking hilarious, my first iteration of this function made it so this deletes the
    // object in the JSON rewriting the JSON file and everything, I am such a fucking idiot.

    // 1. Get rid of the object with the given UUID from mapData
    auto it = std::find_if(mapData.objects.begin(), mapData.objects.end(),
        [&](const SceneObject& obj) {
            return obj.getUUID() == objUUID;
        });

    // 2. Erase the found object and set mapData's isDirty to true
    if (it != mapData.objects.end()) {
        mapData.objects.erase(it);
        mapData.isDirty = true;

        std::cout << "Deleted object UUID " << objUUID << " from memory\n";
    }
}