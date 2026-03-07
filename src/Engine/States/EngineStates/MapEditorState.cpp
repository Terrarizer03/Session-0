//
// Created by Terrarizer on 06/03/2026.
//

#include "MapEditorState.h"

#include <iostream>

#include "../../Renderer/OpenGLRenderer/GLShader.h"
#include "../../Core/Loaders/Loader.h"
#include "GLFW/glfw3.h"

bool MapEditorState::initialize() {
    std::cout << "MapEditorState initialized" << std::endl;
    // TEST
    m_camera = { {2.0f, 2.0f, 3.0f} };
    float aspect = static_cast<float>(1200) / static_cast<float>(900);
    m_camera.setPerspective(45.0f, aspect, 0.1f, 100.0f);

    Transform transform;
    const auto shader = std::make_shared<GLShader>("assets/Shaders/cube_default.vert", "assets/Shaders/cube_default.frag");
    const auto mesh = std::make_shared<Mesh>(dndAssetLoader::loadOBJ("assets/Models/cube_default.obj"));

    Material material;
    material.shader = shader;
    material.color = dndMath::Vector4(0.5f, 0.9f, 1.0f, 1.0f);

    SceneObject object = { mesh, transform, material, "Cube" };

    m_renderContext.camera = &m_camera;
    m_renderContext.lightDir = { 0.5f, 1.0f, 0.3f };
    m_projectContext.name = "Cube_test";
    m_projectContext.objects.push_back(object);

    return true;
}

void MapEditorState::handleInput(const IInput& input) {
    m_camera.yaw += input.getDeltaX() * SENSITIVITY;
    m_camera.pitch += input.getDeltaY() * SENSITIVITY;

    // Clamp pitch so m_camera doesn't flip upside down
    if (m_camera.pitch > 89.0f) m_camera.pitch = 89.0f;
    if (m_camera.pitch < -89.0f) m_camera.pitch = -89.0f;

    m_camera.updateFront();
    dndMath::Vector3 side = m_camera.front.cross(m_camera.up).normalized();

    if (input.getKey(GLFW_KEY_W))
        m_camera.position += m_camera.front * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_S))
        m_camera.position -= m_camera.front * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_A))
        m_camera.position -= side * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_D))
        m_camera.position += side * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_Q))
        m_camera.position -= m_camera.up * CAMERA_SPEED;
    if (input.getKey(GLFW_KEY_E))
        m_camera.position += m_camera.up * CAMERA_SPEED;
}

void MapEditorState::update(float deltaTime) const {

}

void MapEditorState::render(IRenderer* renderer) const {
    for (const SceneObject& object : m_projectContext.objects) {
        renderer->draw(*object.mesh, object.transform, object.material, m_renderContext);
    }
}

void MapEditorState::cleanup() const {

}

MapEditorState::~MapEditorState() {
    MapEditorState::cleanup();
}

