#这里是我的opengl学习笔记
一、opengl环境搭建
GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文、定义窗口参数以及处理用户输入
GLAD用来自动获取OPENGL的底层函数地址
GLM是数学计算库，用来进行坐标计算等
流程：GLFW创建窗口 → GLAD加载OpenGL函数 → GLM做3D坐标运算 → OpenGL渲染画面
<img width="935" height="697" alt="1" src="https://github.com/user-attachments/assets/d248b093-2d91-4d5b-be7d-2e1129857ef4" />
