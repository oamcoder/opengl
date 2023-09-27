#pragma once

#include <glad/glad.h>
#include <GLFW//glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace ShaderManager {
    enum ShaderType {
        Vertex = 0,
        Fragment = 1
    };

    struct ShaderSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    unsigned int CreateShaderProgram(const std::string& shaderPath);
}
