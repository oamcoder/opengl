#include "ShaderManager.h"

static ShaderManager::ShaderSource loadShader(const std::string &shaderPath) {
    std::ifstream stream(shaderPath);
    std::string content;
    ShaderManager::ShaderType type;
    std::stringstream stringStream[2];
    while (std::getline(stream, content)) {
        if (content.find("#glsl") != std::string::npos) {
            if (content.find("vertex") != std::string::npos) {
                type = ShaderManager::ShaderType::Vertex;
            } else if (content.find("fragment") != std::string::npos) {
                type = ShaderManager::ShaderType::Fragment;
            }
        } else {
            stringStream[static_cast<int>(type)] << content << "\n";
        }
    }
    return {stringStream[0].str(), stringStream[1].str()};
}

static unsigned int compileShader(unsigned int type, const std::string &source) {
    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (GL_FALSE == success) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *message = static_cast<char *>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << "shader" << std::endl;
        std::cout << message << std::endl;
    }
    return shader;
}

unsigned int ShaderManager::CreateShaderProgram(const std::string &shaderPath) {
    ShaderManager::ShaderSource source = loadShader(shaderPath);
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, source.VertexSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    //TODO: ERROR HANDLE

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}