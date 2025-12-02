#
#   Core
#


set(SOURCES
    vendor/stb/stb_image.h
    vendor/stb/stb_image.cpp
    Source/Core/Renderer/Renderer.hpp
    Source/Core/Renderer/Renderer.cpp
    Source/Core/Renderer/Shader.hpp
    Source/Core/Renderer/Shader.cpp
    Source/Core/ColorPalette.hpp
    Source/Core/ColorPalette.cpp
    Source/Core/Application.hpp
    Source/Core/Application.cpp
    Source/Core/Window.hpp
    Source/Core/Window.cpp
    Source/Core/Layer.hpp
    Source/Core/Layer.cpp
    Source/Core/Event.hpp
)


add_library(Core STATIC)


target_sources(Core PRIVATE ${SOURCES})


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)


target_link_libraries(Core glad)
target_link_libraries(Core glfw)
target_link_libraries(Core glm)

target_include_directories(Core PUBLIC "Source" "vendor/stb")
