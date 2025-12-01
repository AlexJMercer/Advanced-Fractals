#
#   App
#


set(SOURCES
    Source/Fractals2.cpp
    Source/FractalLayer.hpp
    Source/FractalLayer.cpp
)


add_executable(App)


target_sources(App PRIVATE ${SOURCES})


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})


add_compile_definitions(
    GLFW_INCLUDE_NONE
)


target_link_libraries(App Core)

target_include_directories(App PRIVATE Source)


set_target_properties(App PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/App"
)   