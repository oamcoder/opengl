#include "GLManager.h"
#include "Shader.h"

GLFWwindow *GLFW::window;

static void init() {
    float vertices[] = {
            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0, 0.5f, 0.0f, 0.0f, 1.0f,
    };
    int indices[] = {
            0, 1, 2,
    };

    /** 核心渲染模式必须使用vao
     *  vao存储了对绑定vbo、ebo的操作
     */
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /** 位置属性 */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    /** 颜色属性 */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    /** 设置线框模式 */
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static void render(Shader shader) {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    /** 画数组 */
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    /** 画索引 */
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    /** uniform数据传输 */
//    auto timeValue = static_cast<float>(glfwGetTime());
//    auto greenValue = static_cast<float>(sin(timeValue) / 2.0f + 0.5f);
//    shader.Set4f("vertexColor", 0.9f, greenValue, 0.3f, 1.0f);
}

bool GLFW::Init() {
    /** 初始化glfw */
    if (!glfwInit()) {
        std::cout << "glfw init failed" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /** 创建窗口 */
    window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }
    /** 创建OpenGL上下文 */
    glfwMakeContextCurrent(window);
    /** 设置窗口大小变化回调 */
    glfwSetFramebufferSizeCallback(window, ([](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }));
    /** 加载glfw函数指针 */
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

void GLFW::MainLoop() {
    init();
    auto shader = Shader::Create("res/shader/base.glsl");
    shader.Use();
    while (!glfwWindowShouldClose(window)) {
        /** 渲染 */
        render(shader);
        /** 交换缓冲区 */
        glfwSwapBuffers(window);
        /** 轮询并处理事件 */
        glfwPollEvents();
    }
    glfwTerminate();
}

