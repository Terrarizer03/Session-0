target_sources(DnDCreator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/DnDEngine.cpp)

add_subdirectory(Core)
add_subdirectory(Renderer)
add_subdirectory(States)
add_subdirectory(UI)
add_subdirectory(Window)