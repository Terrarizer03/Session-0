//
// Created by Terrarizer on 21/01/2026.
//

#include <iostream>
#include "glad/glad.h"
#include "DnDEngine.h"
#include "Core/Input/GLFWInput/GLFWInput.h"
#include "Core/Loaders/Loader.h"
#include "Core/Nodes/Camera.h"
#include "Core/Rendering Math/Mesh/Mesh.h"
#include "Renderer/OpenGLRenderer/GLRenderer.h"
#include "Window/GLFWWindow/GLFWWindow.h"
#include "Renderer/OpenGLRenderer/GLShader.h"

bool DnDEngine::initialize() {

    window = std::make_unique<GLFWWindow>();
    if (!window || !window->initialize() || !window->createWindow(window_width, window_height, "D&D Creator")) {
        std::cout << "Failed to initialize window \n";
        return false;
    }

    window->setVSync(true); // For now, stick with this as true

    renderer = std::make_unique<GLRenderer>();
    if (!renderer || !renderer->initialize()) {
        std::cout << "Failed to initialize renderer \n";
        return false;
    }

    GLFWwindow* handle = static_cast<GLFWWindow*>(window.get())->getHandle();
    input = std::make_unique<GLFWInput>(handle);

    glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    renderer->setViewport(0, 0, window_width, window_height);

    return true;
}

void DnDEngine::run() const {

    Camera camera(dndMath::Vector3(2.0f, 2.0f, 3.0f)); // 3 units back from origin
    float aspect = static_cast<float>(window_width) / static_cast<float>(window_height);
    camera.setPerspective(45.0f, aspect, 0.1f, 100.0f);

    RenderContext context;
    context.camera = &camera;
    context.lightDir = { 0.5f, 1.0f, 0.3f };

    Transform transform;
    std::unique_ptr<IShader> shader = std::make_unique<GLShader>("assets/Shaders/cube_default.vert", "assets/Shaders/cube_default.frag");
    const Mesh mesh = dndAssetLoader::loadOBJ("assets/Models/cube_default.obj");

    Material material;
    material.shader = shader.get();
    material.color = dndMath::Vector4(0.5f, 0.9f, 1.0f, 1.0f);

    constexpr float cameraSpeed = 0.1f;
    constexpr float sensitivity = 0.1f;

    while (!window->shouldClose()) {
        renderer->clearColor(0.07f, 0.13f, 0.17f, 1.0f);

        float time = glfwGetTime();
        input->update();

        camera.yaw += input->getDeltaX() * sensitivity;
        camera.pitch += input->getDeltaY() * sensitivity;

        // Clamp pitch so camera doesn't flip upside down
        if (camera.pitch > 89.0f) camera.pitch = 89.0f;
        if (camera.pitch < -89.0f) camera.pitch = -89.0f;

        camera.updateFront();
        dndMath::Vector3 side = camera.front.cross(camera.up).normalized();

        if (input->getKey(GLFW_KEY_W))
            camera.position += camera.front * cameraSpeed;
        if (input->getKey(GLFW_KEY_S))
            camera.position -= camera.front * cameraSpeed;
        if (input->getKey(GLFW_KEY_A))
            camera.position -= side * cameraSpeed;
        if (input->getKey(GLFW_KEY_D))
            camera.position += side * cameraSpeed;
        if (input->getKey(GLFW_KEY_Q))
            camera.position -= camera.up * cameraSpeed;
        if (input->getKey(GLFW_KEY_E))
            camera.position += camera.up * cameraSpeed;

        context.lightDir = {
            std::sin(time) * 1.0f,  // orbits left and right
            1.0f,              // always slightly above
            std::cos(time) * 1.0f // orbits front and back
        };
        renderer->draw(mesh, transform, material, context);

        window->pollEvents();
        window->swapBuffers();
    }
}
