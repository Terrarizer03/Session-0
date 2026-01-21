#include "src/Engine/Core/DnDEngine.h"

int main() {
    DnDEngine Engine;

    if (!Engine.Initialize()) return -1;
    if (!Engine.Run()) return -1;
    if (!Engine.Exit()) return -1;

    // if (!glfwInit()) return -1;
    //
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //
    // GLFWwindow* window = glfwCreateWindow(800, 600, "D&D Creator", nullptr, nullptr);
    // glfwMakeContextCurrent(window);
    //
    // if (!gladLoadGL()) {
    //     std::cerr << "Failed to init glad\n";
    //     return -1;
    // }
    //
    // std::cout << "OpenGL " << glGetString(GL_VERSION) << " loaded\n";
    //
    // glViewport(0, 0, 800, 600);
    //
    // glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //
    // while (!glfwWindowShouldClose(window)) {
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }
    //
    // glfwTerminate();


    return 0;
}