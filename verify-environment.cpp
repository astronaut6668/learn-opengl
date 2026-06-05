#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

int main()
{
    // 验证GLFW
    if (!glfwInit())
    {
        std::cout << " GLFW初始化失败" << std::endl;
        return -1;
    }

    // 验证GLM
    glm::vec3 testVec(1.0f, 2.0f, 3.0f);
    std::cout << " GLM正常，x=" << testVec.x << std::endl;

    // 创建窗口
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* win = glfwCreateWindow(800, 600, "OpenGL环境测试", nullptr, nullptr);
    if (!win)
    {
        std::cout << " 窗口创建失败" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    // 验证GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << " GLAD加载失败" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << " GLFW+GLAD+GLM 全部环境配置成功！" << std::endl;

    // 消息循环
    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
