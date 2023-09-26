#include "GLManager.h"

int main() {
    if (!GLFW::Init()) {
        std::cout << "OpenGL init Failed" << std::endl;
        return -1;
    }
    GLFW::MainLoop();
    return 0;
}