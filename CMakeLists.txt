cmake_minimum_required(VERSION 4.1)
project(DnDCreator)

# GLFW
add_subdirectory(external/glfw)

# glad
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# include OpenGL on each platform
find_package(OpenGL REQUIRED)

add_executable(DnDCreator
        main.cpp
        src/Engine/Core/DnDEngine.cpp
        src/Engine/Core/DnDEngine.h
        src/Engine/Renderer/IRenderer.h
        src/Engine/Window/IWindow.h
        src/Engine/UI/UIManager.cpp
        src/Engine/UI/UIManager.h
        src/Engine/Window/GLFWWindow/GLFWWindow.cpp
        src/Engine/Window/GLFWWindow/GLFWWindow.h
)

target_include_directories(DnDCreator PRIVATE
        external/glad/include
        external/glfw/include
)

target_link_libraries(DnDCreator
        glfw
        glad
        OpenGL::GL
)
