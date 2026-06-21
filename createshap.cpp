#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// 窗口尺寸变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 处理键盘输入函数
void processInput(GLFWwindow* window);
// 窗口设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// 顶点着色器源码
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// 片段着色器源码
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
int main()
{
    // glfw：初始化并配置窗口
    // ------------------------------
    glfwInit();
    // 设置OpenGL主版本号为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // 设置OpenGL次版本号为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw：创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    // 判断窗口是否创建失败
    if (window == NULL)
    {
        std::cout << "创建GLFW窗口失败" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 将当前窗口设置为OpenGL上下文
    glfwMakeContextCurrent(window);
    // 绑定窗口尺寸变化回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad：加载所有OpenGL函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "初始化GLAD失败" << std::endl;
        return -1;
    }


    // 构建并编译着色器程序
    // 创建顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 传入着色器源码
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译顶点着色器
    glCompileShader(vertexShader);
    // 检查着色器编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "错误::着色器::顶点着色器编译失败\n" << infoLog << std::endl;
    }
    // 创建片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // 检查片段着色器编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "错误::着色器::片段着色器编译失败\n" << infoLog << std::endl;
    }
    // 创建着色器程序并链接两个着色器
    unsigned int shaderProgram = glCreateProgram();
    // 将顶点着色器附加到程序
    glAttachShader(shaderProgram, vertexShader);
    // 将片段着色器附加到程序
    glAttachShader(shaderProgram, fragmentShader);
    // 链接着色器程序
    glLinkProgram(shaderProgram);
    // 检查链接错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "错误::着色器程序::链接失败\n" << infoLog << std::endl;
    }
    // 链接完成后删除原始着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 设置顶点数据、缓冲对象，并配置顶点属性
    // 矩形四个顶点坐标
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // 右上角
         0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f,  // 左下角
        -0.5f,  0.5f, 0.0f   // 左上角
    };
    // 索引数组，用两个三角形拼成矩形，索引从0开始
    unsigned int indices[] = {
        0, 1, 3,  // 第一个三角形
        1, 2, 3   // 第二个三角形
    };
    // 声明顶点数组对象、顶点缓冲对象、元素索引缓冲对象
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // 先绑定VAO，再绑定设置顶点缓冲，最后配置顶点属性
    glBindVertexArray(VAO);

    // 绑定顶点缓冲并上传顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 绑定索引缓冲并上传索引数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 配置顶点属性解析规则：第0号属性，每个顶点3个浮点数，不标准化，步长3个float，偏移0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // 启用0号顶点属性
    glEnableVertexAttribArray(0);

    // 可以解绑顶点缓冲，glVertexAttribPointer已经记录了对应的VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 注意：当前VAO激活时不要解绑EBO，索引缓冲会被VAO保存
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // 可以解绑VAO，避免后续操作意外修改当前VAO，一般非必要不手动解绑
    glBindVertexArray(0);


    // 取消注释此行可切换为线框模式绘制多边形
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 渲染主循环
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 处理输入
        // -----
        processInput(window);

        // 渲染指令
        // ------
        // 设置清屏背景色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用编译好的着色器程序
        glUseProgram(shaderProgram);
        // 绑定顶点数组对象
        glBindVertexArray(VAO);
        // 使用索引缓冲绘制三角形，一共6个索引
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // 无需每次循环解绑VAO
        // glBindVertexArray(0);

        // glfw：交换前后帧缓冲，轮询窗口IO事件（按键、鼠标等）
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 程序结束后释放所有缓冲资源
   
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw：终止，释放所有窗口资源
  
    glfwTerminate();
    return 0;
}

// 处理所有输入：检测本帧按键状态并响应

void processInput(GLFWwindow* window)
{
    // 按下ESC键关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw：窗口尺寸被系统或用户修改时自动调用此回调

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 同步视口大小与窗口尺寸；高分屏宽高会大于设置数值
    glViewport(0, 0, width, height);
}