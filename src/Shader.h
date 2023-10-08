#pragma once

#include <glad/glad.h>
#include <GLFW//glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

class Shader {
public:
    enum ShaderType {
        Vertex = 0,
        Fragment = 1
    };

    struct ShaderSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    static Shader Create(const std::string &shaderPath);

    void Use() const;
    void Set4f(const std::string &string, float a, float b, float c, float d) const;

private:
    unsigned int id;
    explicit Shader(unsigned int id);
};
