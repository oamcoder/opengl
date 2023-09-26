#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace GLFW {
    extern GLFWwindow *window;

    bool Init();

    void MainLoop();
}
