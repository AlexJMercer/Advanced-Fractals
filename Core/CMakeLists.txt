#
#   Core
#


set(SOURCES
    vendor/stb/stb_image.h
    vendor/stb/stb_image.cpp
    vendor/imgui/backends/imgui_impl_glfw.h
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.h
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/imgui/imgui_internal.h
    vendor/imgui/imgui.h
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imstb_rectpack.h
    vendor/imgui/imstb_textedit.h
    vendor/imgui/imstb_truetype.h

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


target_sources(Core PRIVATE 
    ${SOURCES}
)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)


target_link_libraries(Core glad)
target_link_libraries(Core glfw)
target_link_libraries(Core glm)
# target_link_libraries(Core imgui)

target_include_directories(Core PUBLIC 
    "Source"
    "vendor/stb"
    "vendor/imgui"
    "vendor/imgui/backends"
)

# target_include_directories(imgui PRIVATE 
#     ${imgui_SOURCE_DIR}
#     ${imgui_SOURCE_DIR}/backends
# )
