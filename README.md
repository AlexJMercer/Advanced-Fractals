<h1 align="center">🌿 Advanced Fractals</h1>


## Introduction

This is the repository for **Advanced Fractals**, the next step from my previous Fractal project. The entire system has been built from the ground up to be properly modular, extensible and maintainable.

This project has been highly inspired by the [`C++ Architecture`](https://www.youtube.com/watch?v=rUxZ5N77M5E&pp=ygUXdGhlIGNoZXJubyBhcmNoaXRlY3R1cmU%3D) series on YouTube by TheCherno. This project and the learning experience that came with it would not have been possible without his excellent content.



## Features and Capabilities

- **Modular Design**: As learnt from TheCherno's architecture series, the project is structured cleanly into an App, and a Core module. The application module handles the front-end user interactable components, while the core module handles the back-end logic and computations.

- **Layer System**: The project implements a working layer system, that allows the application to have multiple layers, each with their own functionality and rendering capabilities. In my case, only a single fractal layer and a control layer have been implemented.

- **OpenGL support**: No more direct interfacing with the GPU through low-level APIs, such as CUDA, which was used in the previous project. Instead, a high-level abstraction through OpenGL is used to directly make use of the rendering and graphics pipeline.



## Pre-requisites

- This project uses GLM, GLFW, GLAD. These libraries are included in `Dependencies.cmake`, and they're automatically downloaded and built when you build the project using CMake.

- Additionally, the `Core/vendor` folder should contain the stb_image library and the ImGui library. These are not included in the repository due to size constraints.



## How to Build

A root `CMakeLists.txt` file is provided to build the entire project. Individual `CMakeLists.txt` files are present in both the `App` and `Core` directories to build the respective modules.

1. Clone the repository : 
    ```sh
        git clone https://github.com/AlexJMercer/Advanced-Fractals.git
        cd Advanced-Fractals
    ```
2. Generate build files : 
    ```sh
        cmake -S . -B build -G "Visual Studio 17 2022"
    ```
3. Build the project : 
    ```sh
        cmake --build build --config Release
    ```



## Run the Application:

Now you can use: `build\App\Release\App.exe App\Data\<GLSL File\>` to run the application with a custom fragment shader file. If no file is provided, the screen is black by default.
