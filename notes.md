#这里是我的opengl学习笔记

一、opengl环境搭建

GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文、定义窗口参数以及处理用户输入

GLAD用来自动获取OPENGL的底层函数地址

GLM是数学计算库，用来进行坐标计算等

流程：GLFW创建窗口 → GLAD加载OpenGL函数 → GLM做3D坐标运算 → OpenGL渲染画面

搭建环境：复制了提供的thirdparty文件夹，用cmake配置环境

<img width="935" height="697" alt="1" src="https://github.com/user-attachments/assets/d248b093-2d91-4d5b-be7d-2e1129857ef4" />

二、创建窗口

opengl使用双缓冲，一个缓冲用于输出，一个缓冲用于存储之后一个画面内容，通过交换缓冲使得画面切换丝滑

代码顺序：

// 渲染循环

while(!glfwWindowShouldClose(window))

{
    
    // 输入
    
    processInput(window);

    // 渲染指令
    
    ...

    
    // 检查并调用事件，交换缓冲
    
    glfwPollEvents();
    
    glfwSwapBuffers(window);

}

以下是创建一个持续存在的窗口代码实践：

<img width="529" height="467" alt="2" src="https://github.com/user-attachments/assets/4cc64bd8-2834-4db5-a56f-9b520e38812f" />

<img width="647" height="368" alt="3" src="https://github.com/user-attachments/assets/f363cdda-a16f-47ef-aa4a-852770b83a66" />

效果如下图：

 

 














<img width="477" height="362" alt="4" src="https://github.com/user-attachments/assets/78591260-abaf-4466-af98-09e093e6dd7d" />

三、创建三角形
