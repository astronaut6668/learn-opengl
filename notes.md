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


三、创建图形

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

顶点输入：

OpenGL 仅处理 x/y/z 在-1到+1范围内的三维坐标，该区间叫标准化设备坐标 NDC，区间外图形直接裁剪丢弃

NDC 特点：原点在屏幕中心，Y 轴向上；经视口变换后转为屏幕像素坐标，送入光栅化

z 轴代表深度，用于遮挡判断，数值控制物体前后显示

顶点数据需在顶点着色器处理后输出 NDC 坐标才可见

顶点数据存储：VBO 顶点缓冲对象

作用：在 GPU 显存存放批量顶点数据，减少 CPU-GPU 频繁传输，提升效率

使用流程：

  glGenBuffers 生成唯一缓冲 ID

  glBindBuffer(GL_ARRAY_BUFFER, VBO) 绑定顶点缓冲目标

  glBufferData 将 CPU 顶点数组拷贝至显存

数据读写模式（第四个参数）

  GL_STATIC_DRAW：数据几乎不变

  GL_DYNAMIC_DRAW：数据频繁修改

  GL_STREAM_DRAW：每帧都更新数据
  
顶点着色器（GLSL）

现代 OpenGL 渲染必须配置顶点 + 片段着色器，使用 GLSL 语言编写编译。

基础顶点着色器结构：

#version 330 core 声明版本与核心模式

layout(location=0) in vec3 aPos 定义顶点输入属性，location 编号用于 CPU 绑定数据

内置输出 gl_Position(vec4)，顶点最终输出坐标，3D 坐标需补 w=1.0 转为四维向量

顶点着色器

  现代 OpenGL 渲染必须搭配顶点、片段两套着色器，采用类 C 的 GLSL 语言编写，程序运行时编译生效
  
  着色器开头标注版本，用 in 接收顶点坐标输入，内置输出变量存储变换后的四维顶点坐标，三维坐标需补充第四分量
  
  核心作用：处理顶点空间坐标，转换为可视范围内的标准化设备坐标；图形坐标、色彩都依靠 GLSL 向量类型承载
  
着色器编译链接步骤

  分别创建顶点、片段着色器对象，载入代码源码并编译，可打印日志排查编译报错。片段着色器通过 out 输出像素色彩，色彩由红、绿、蓝、透明度四项数值组成
  
  创建着色器程序，挂载两类着色器后执行链接，校验无误后激活程序使用，链接完成可清理原始着色器对象
  
顶点数据对接

  通过专用函数告诉显卡如何解析缓冲里的顶点数据，设定数据结构、间隔与起始偏移，配置完成后开启对应顶点属性通道
  
三种缓冲对象

  VBO 顶点缓冲：存放全部顶点数据，上传至显存，降低 CPU 与显卡的数据传输损耗
  
  VAO 顶点数组对象：缓存整套顶点配置、关联的顶点缓冲与索引缓冲；核心模式强制使用，物体渲染只需绑定对应 VAO，不用重复配置参数
  
  EBO 索引缓冲：存储顶点绘制顺序，复用重复顶点，减少冗余数据，绑定 VAO 时会一并记录索引缓冲状态
  
两种绘制方式

  无索引绘制：直接按顶点缓冲的顺序绘图
  
  索引绘制：读取索引缓冲里的顶点顺序绘图，适合网格、矩形这类存在共用顶点的模型
  
生成图形示例：

<img width="600" height="470" alt="hellotriangle" src="https://github.com/user-attachments/assets/5270ab72-d204-4a4c-b043-c6f20e519655" />



<img width="404" height="318" alt="1" src="https://github.com/user-attachments/assets/f79704ce-367f-4cc2-baab-302ce533386f" />



四、着色器

着色器基础

  着色器是运行在 GPU 上的小程序，对应渲染管线单独阶段，功能仅为输入转换输出；各个着色器互相独立，只能依靠输入、输出变量传递数据

  使用 GLSL 语言编写，语法近似 C 语言，原生内置向量、矩阵相关运算

  标准书写框架：首行声明版本，依次定义 in 输入、out 输出、uniform 全局变量，main 为固定执行入口
  
GLSL 数据类型

  基础单值：bool、float、double、int、uint

  向量：分为 vecn、bvecn、ivecn、uvecn、dvecn，n 代表 2/3/4 个分量，绘图场景最常用 vecn 存储坐标、色彩

  向量操作：可用 x/y/z/w、r/g/b/a、s/t/p/q 读取分量；支持分量重组语法；支持多个向量拼接构造新向量

in 输入与 out 输出

  顶点着色器输入叫做顶点属性，接收 CPU 通过 VBO 传入的顶点数据，搭配 layout (location) 标记序号，方便 CPU 绑定；硬件存在顶点属性数量上限，可调用 glGetIntegerv 查询 GL_MAX_VERTEX_ATTRIBS

  着色器间数据传递规则：前一级着色器定义 out 变量，后一级定义同名、同类型 in 变量，程序链接阶段自动完成数据互通

  片段着色器强制需要 vec4 类型 out 输出颜色，缺少输出会导致画面全黑或全白

Uniform 全局变量

  核心特性

    全局生效：一套着色器程序内所有着色器均可访问

    数值持久：赋值后保持不变，直到 CPU 主动更新

    数据流向：CPU 单向传递数据至 GPU 着色器

  完整使用流程

    在 GLSL 着色器内声明 uniform 变量

    CPU 调用 glGetUniformLocation 查询该变量的位置索引

    激活着色器程序 glUseProgram 后，调用 glUniform 系列函数赋值

    glUniform 函数依靠后缀区分数据类型：f 浮点、i 整型、ui 无符号整型、数字 + f 多浮点、fv 浮点数组

    注意事项：声明后全程未使用的 uniform 会被编译器自动剔除，查询位置会返回 - 1，引发程序错误

    适用场景：控制整体模型统一颜色、运行时间、变换矩阵等全局参数

多顶点属性（坐标 + 顶点自带色彩）

  顶点数组可混合存放多组属性，单个顶点依次存储坐标、RGB 颜色等多类数据

  CPU 配置顶点属性依靠 glVertexAttribPointer，两个关键参数

    步长 stride：单个顶点全部数据的总字节大小

    偏移 offset：当前属性距离顶点数据起始位置的字节距离

    配置完成后调用 glEnableVertexAttribArray 开启对应属性通道

  片段插值原理：光栅化阶段对三角形内部所有片段做线性插值，顶点设置的不同颜色会平滑渐变混合，形成过渡色彩画面

封装 Shader 工具类

  设计目的：简化重复的源码读取、编译、链接、错误打印、uniform 赋值流程

  核心能力

    构造函数接收顶点、片段着色器文件路径，通过文件流读取硬盘上的着色器源码

    自动执行 glCreateShader、glShaderSource、glCompileShader 编译着色器

    创建着色器程序 ID，执行 glAttachShader、glLinkProgram 链接

    调用 glGetShaderiv、glGetShaderInfoLog 捕获编译错误，glGetProgramiv、glGetProgramInfoLog 捕获链接错误

    封装 use 方法执行 glUseProgram 激活程序

    封装 setBool、setInt、setFloat 等接口，内部自动查询 uniform 位置并赋值

    使用方式：创建 Shader 对象传入着色器文件路径，渲染循环中调用 use 激活，调用 set 系列方法修改全局 uniform 参数

核心概念区分

  顶点属性：每个顶点独有数据，从 VBO 传入顶点着色器，各顶点数值可互不相同

  Uniform：全局共用数据，整个绘制物体共用同一套数值

  in/out：着色器之间的数据传输通道，同名同类型变量自动匹配

  片段插值：光栅化自动平滑混合三角形内所有片段的输入数据
  
示例：

<img width="600" height="470" alt="image" src="https://github.com/user-attachments/assets/535c6428-9f3c-4dc2-a0c4-07e6dd9a190b" />

