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

    dndMath::Matrix4 model = dndMath::Matrix4::identity();
    dndMath::Matrix4 view = camera.getViewMatrix();
    dndMath::Matrix4 projection = dndMath::Matrix4::perspective(45.0f, aspect, 0.1f, 100.0f);

    dndMath::Matrix4 mvp = projection * view * model;

    const GLShader shader("assets/Shaders/cube_default.vert", "assets/Shaders/cube_default.frag");
    const Mesh mesh = dndAssetLoader::loadOBJ("assets/Models/cube_default.obj");

    const float cameraSpeed = 0.1f;

    while (!window->shouldClose()) {
        renderer->clearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT);

        input->update();

        float sensitivity = 0.1f;
        camera.yaw += input->getDeltaX() * sensitivity;
        camera.pitch += input->getDeltaY() * sensitivity;

        // Clamp pitch so camera doesn't flip upside down
        if (camera.pitch > 89.0f) camera.pitch = 89.0f;
        if (camera.pitch < -89.0f) camera.pitch = -89.0f;

        camera.updateFront();
        dndMath::Vector3 right = camera.front.cross(camera.up).normalized();

        if (input->getKey(GLFW_KEY_W))
            camera.position += camera.front * cameraSpeed;
        if (input->getKey(GLFW_KEY_S))
            camera.position -= camera.front * cameraSpeed;
        if (input->getKey(GLFW_KEY_A))
            camera.position -= right * cameraSpeed;
        if (input->getKey(GLFW_KEY_D))
            camera.position += right * cameraSpeed;

        view = camera.getViewMatrix();
        mvp = projection * view * model;

        shader.Bind();
        shader.SetUniformMatrix4fv("uModel", model);
        shader.SetUniformVec3("uLightDir", dndMath::Vector3(0.5f, 1.0f, 0.3f));
        shader.SetUniformMatrix4fv("uMVP", mvp);
        mesh.draw();

        window->pollEvents();
        window->swapBuffers();
    }
}
