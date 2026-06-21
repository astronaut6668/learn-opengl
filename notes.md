<img width="628" height="359" alt="image" src="https://github.com/user-attachments/assets/20d38524-4d7c-49ed-a0ab-d807f60b8021" />#这里是我的opengl学习笔记

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

顶点数组对象：VAO

顶点缓冲对象：VBO

元素缓冲对象：EBO 或 IBO

3D坐标转为2D坐标的处理过程是由OpenGL的图形渲染管线管理的

<img width="628" height="359" alt="pipeline" src="https://github.com/user-attachments/assets/cd2b32e1-8299-4058-bffc-04d561639ef1" />

顶点着色器：输入单个顶点，转换三维坐标、处理顶点属性，输出变换后的顶点

几何着色器（可选）：接收一组构成图元的顶点，可新增 / 修改顶点生成新图元

图元装配：收集输出顶点，按指定规则组装成三角形、线段等基础图元

光栅化：将图元转为屏幕像素片段，提前裁掉视口外片段以优化性能

片段着色器：以片段为输入，结合光照、纹理等数据计算像素最终颜色

深度 / 模板测试与混合：依据深度、透明度丢弃遮挡片段或混合颜色，输出屏幕最终像素


