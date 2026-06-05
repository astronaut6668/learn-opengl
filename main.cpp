#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}//回调函数，窗口大小改变时调用
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}//输入处理函数，检查用户是否按下了ESC键，如果按下了就把窗口的关闭属性设置为true



int main()
{
	//这4行代码是创建一个窗口的标准代码
	glfwInit();//初始化GLFW库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置版本是opengl的3.3版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用opengl的核心模式

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	//生成一个窗口，宽800，长600，名字是LearnOpenGL，最后两个参数暂时没用
	//生成的对象是GLFWwindow类型的指针
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//程序结束前需要调用glfwTerminate函数来释放GLFW占用的内存
		return -1;
	}
	glfwMakeContextCurrent(window);
	//把这个window窗口设置为当前线程的主上下文，之后所有的OpenGL调用都会作用于这个窗口。


	//GLAD初始化必需代码
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		//glfwGetProcAddress：GLFW 工具，专门去显卡驱动里查某个 OpenGL 函数在哪。
		//(GLADloadproc)：格式转换，让 GLAD 能用这个查询函数。
		//gladLoadGLLoader(...)：GLAD 循环调用上面的查询，一次性加载全部 OpenGL 函数。
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	glViewport(0, 0, 800, 600);//设置视口，告诉OpenGL渲染窗口的大小，前两个参数是视口左下角的坐标，后两个参数是视口的宽和高
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	//回调函数，窗口大小改变时调用
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);
		//渲染
		glClearColor(0.5f, 0.5f, 0.7f, 0.5f);//设置清空屏幕所用的颜色，参数是RGBA四个分量，范围是0.0到1.0
		glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲，使用glClearColor设置的颜色来清空窗口
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwWindowShouldClose：检查GLFW是否被要求退出，返回值非零时退出循环
	//glfwSwapBuffers：交换颜色缓冲
	//glfwPollEvents：检查有没有触发什么事件（比如键盘输入、鼠标移动等），更新窗口状态，并调用对应的回调函数
	glfwTerminate();
}