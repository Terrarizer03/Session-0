cmake_minimum_required(VERSION 3.16)
project(DnDCreator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GLFW
add_subdirectory(external/glfw)

# glad
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# imgui
add_library(imgui
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        external/imgui/
        external/imgui/backends
        external/glfw/include
)

# OpenGL
find_package(OpenGL REQUIRED)

add_executable(DnDCreator)

add_subdirectory(src)

target_include_directories(DnDCreator PRIVATE
        external/glad/include
        external/glfw/include
        external/imgui/
        external/imgui/backends
        external/tinyobjloader/include
        external/nlohmann/include
)

target_link_libraries(DnDCreator
        glfw
        glad
        imgui
        OpenGL::GL
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})