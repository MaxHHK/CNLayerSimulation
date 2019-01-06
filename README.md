# Computer Network Simulation
## 功能描述
## 开发环境
macOS，Mojave，10.14
## 运行环境
Unix内核的操作系统，推荐shel台宽度大于150，高度大于40
## 项目结构简介
- main.cpp，主函数文件
- cnformat.h，数据格式头文件
- apue.h，myerror.h，文件读写相关头文件
- _socket_.cpp，_socket_.hpp，自封装socket
- interface.cpp，interface.hpp，应用程序、协议封装解析界面
- processIP.cpp，processIP.hpp，封装解析IP数据包
- processMac.cpp，processMac.hpp，封装解析MAC帧
- processTCP.cpp，processTCP.hpp，封装解析TCP数据包
- Shell.cpp，Shell.hpp，个人shell台，用于控制程序流程
- TCPDestination.cpp，TCPDestination.hpp，TCP协议模拟的接收方
- TCPSource.cpp，TCPSource.hpp，TCP协议模拟的发送方
- tool.cpp，tool.hpp，小工具空间
- Window.cpp，Window.hpp，窗口绘制
## 使用方法
### 编译
gcc main.c -o CNSimulation
### 运行
- ./CNSimulation [-local]
- 带参数为本地回环测试
1. 客户端和服务端输入自动运行间隔时间，若为0表示手动
2. 客户端输入用户名、密码、Client / Server
3. 客户端输入邮件信息和附件路径
4. 客户端开始模拟封装
5. 客户端配合服务端开始模拟TCP协议
6. 服务端模拟解析
7. 服务端显示邮件和附件
