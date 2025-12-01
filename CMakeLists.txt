#
#   Main
#

cmake_minimum_required(VERSION 3.10)


project(Fractals2 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Dependencies
include(Dependencies.cmake)


# Projects
add_subdirectory(Core)
add_subdirectory(App)











# cmake_minimum_required(VERSION 3.20)
# project(Fractals2 LANGUAGES CXX CUDA)

# # Set C++ and CUDA standards
# set(CMAKE_CUDA_STANDARD 14)
# set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# # Specify CUDA architectures
# set(CMAKE_CUDA_ARCHITECTURES 75)


# # Fetch GLEW
# include(FetchContent)
# FetchContent_Declare(
#     glew
#     GIT_REPOSITORY https://github.com/nigels-com/glew.git
#     GIT_TAG        master
# )
# FetchContent_MakeAvailable(glew)


# # SFML configuration
# set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")

# find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
# find_package(OpenGL REQUIRED)


# # Set executables
# file(GLOB SOURCE_FILES src/*.cpp src/*.cu)

# # Add executable
# add_executable(Fractals2 ${SOURCE_FILES})


# # Link SFML and OpenGL libraries
# # target_include_directories(Fractals2 PRIVATE ${SFML_INCLUDE_DIR})
# target_link_libraries(Fractals2 PRIVATE
#     sfml-system sfml-window sfml-graphics
#     OpenGL::GL
#     cudart
# )


# if (TARGET glew_static)
#     target_link_libraries(Fractals2 PRIVATE glew_static)
# elseif (TARGET libglew_static)
#     target_link_libraries(Fractals2 PRIVATE libglew_static)
# elseif (TARGET GLEW::GLEW)
#     target_link_libraries(Fractals2 PRIVATE GLEW::GLEW)
# endif()

# # Enable separable compilation for CUDA
# set_target_properties(Fractals2 PROPERTIES
#     CUDA_SEPARABLE_COMPILATION ON
# )

# # MSVC-specific options
# # if(MSVC)
# #     target_compile_options(Fractals2 PRIVATE
# #         $<$<COMPILE_LANGUAGE:CUDA>:-Xcompiler="/EHsc /W0 /O2">
# #     )
# # endif()
