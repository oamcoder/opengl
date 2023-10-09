#include "Shader.h"

static const std::string CommentStr = "//";

void checkError(unsigned int type, unsigned int shader, unsigned int shaderType) {
    int success;
    type == GL_COMPILE_STATUS ?
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success) :
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (GL_FALSE == success) {
        int length;
        type == GL_COMPILE_STATUS ?
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length) :
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *message = static_cast<char *>(alloca(length * sizeof(char)));
        type == GL_COMPILE_STATUS ?
        glGetShaderInfoLog(shader, length, &length, message) :
        glGetProgramInfoLog(shader, length, &length, message);
        if (type == GL_COMPILE_STATUS) {
            std::cout << "Failed to compile "
                      << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
                      << "shader" << std::endl;
            std::cout << message << std::endl;
        } else {
            std::cout << "Link error: " << message << std::endl;
        }
    }
}

Shader::ShaderSource loadShader(const std::string &shaderPath) {
    std::ifstream stream(shaderPath);
    std::string content;
    Shader::ShaderType type;
    std::stringstream stringStream[2];
    while (std::getline(stream, content)) {
        if (content.find("#glsl") != std::string::npos) {
            if (content.find("vertex") != std::string::npos) {
                type = Shader::ShaderType::Vertex;
            } else if (content.find("fragment") != std::string::npos) {
                type = Shader::ShaderType::Fragment;
            }
        } else {
            if (content.substr(0, 2) != CommentStr)
                stringStream[static_cast<int>(type)] << content << "\n";
        }
    }
    return {stringStream[0].str(), stringStream[1].str()};
}

unsigned int compileShader(unsigned int type, const std::string &source) {
    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    checkError(GL_COMPILE_STATUS, shader, type);
    return shader;
}

Shader Shader::Create(const std::string &shaderPath) {
    Shader::ShaderSource source = loadShader(shaderPath);
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, source.VertexSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.FragmentSource);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    checkError(GL_LINK_STATUS, program, 0);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return Shader(program);
}

void Shader::Use() const {
    glUseProgram(this->id);
}

void Shader::Set4f(const std::string &name, float a, float b, float c, float d) const {
    glUniform4f(glGetUniformLocation(this->id, name.c_str()), a, b, c, d);
}

Shader::Shader(unsigned int id) : id(id) {}


