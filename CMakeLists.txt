cmake_minimum_required(VERSION 4.1)
project(DnDCreator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW
add_subdirectory(external/glfw)

# glad
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# include OpenGL on each platform
find_package(OpenGL REQUIRED)

add_executable(DnDCreator
        src/main.cpp
        src/Engine/DnDEngine.cpp
        src/Engine/DnDEngine.h
        src/Engine/Renderer/IRenderer.h
        src/Engine/Window/IWindow.h
        src/Engine/UI/UIManager.cpp
        src/Engine/UI/UIManager.h
        src/Engine/Window/GLFWWindow/GLFWWindow.cpp
        src/Engine/Window/GLFWWindow/GLFWWindow.h
        src/Engine/Renderer/OpenGLRenderer/GLRenderer.cpp
        src/Engine/Renderer/OpenGLRenderer/GLRenderer.h
        src/Engine/Core/Math/Vector/Vector3/Vector3.h
        src/Engine/Core/Math/Vector/Vector2.h
        src/Engine/Core/Math/Matrix/Matrix4.h
        "src/Engine/Core/Rendering Math/Vertex.h"
        "src/Engine/Core/Rendering Math/Mesh/Mesh.h"
        "src/Engine/Core/Rendering Math/Face.h"
        src/Engine/Core/Nodes/Camera.h
        src/Engine/Core/Input/IInput.h
        src/Engine/Core/Math/Vector/Vector4.h
        src/Engine/Renderer/IShader.h
        src/Engine/Renderer/OpenGLRenderer/GLShader.h
        src/Engine/Renderer/OpenGLRenderer/GLShader.cpp
        src/Engine/Core/Math/Vector/Vector3/Vector3.cpp
        src/Engine/Core/Math/Matrix/Matrix4.cpp
        "src/Engine/Core/Rendering Math/Mesh/Mesh.cpp"
        src/Engine/Core/Loaders/AssetLoader.cpp
        src/Engine/Core/Loaders/AssetLoader.h
        src/Engine/Core/Input/GLFWInput/GLFWInput.h
        src/Engine/States/IState.h
        src/Engine/States/StateManager.cpp
        src/Engine/States/StateManager.h
        src/Engine/States/EngineStates/MapEditorState.cpp
        src/Engine/States/EngineStates/MapEditorState.h
        "src/Engine/Core/Rendering Math/Transform.h"
        "src/Engine/Core/Rendering Math/SceneObject.h"
        "src/Engine/Core/Rendering Math/Material.h"
        "src/Engine/Core/Rendering Math/RenderContext.h"
        src/Engine/States/EngineStates/ProjectManagerState.cpp
        src/Engine/States/EngineStates/ProjectManagerState.h
        src/Engine/Core/Loaders/ProjectLoader.cpp
        src/Engine/Core/Loaders/ProjectLoader.h
        src/Engine/Core/Loaders/EngineSettings.cpp
        src/Engine/Core/Loaders/EngineSettings.h
        src/Engine/Core/Project/ProjectInfo.h
        src/Engine/Core/Project/MapData.h
        src/Engine/Core/Utilities/toLower.h
)

target_include_directories(DnDCreator PRIVATE
        external/glad/include
        external/glfw/include
        external/tinyobjloader/include
        external/nlohmann/include
)

target_link_libraries(DnDCreator
        glfw
        glad
        OpenGL::GL
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
