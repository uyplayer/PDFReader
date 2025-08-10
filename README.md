

# PDF阅读器

这是一个简单的PDF查看器，使用Qt和C++编写。

## 安装

请确保你的系统已经安装了Qt库，然后使用Qt Creator打开并构建项目。

## 使用

运行程序，然后使用菜单栏上的"打开"按钮来打开一个PDF文件。


## Todo list
- [x] 读取PDF文件
- [x] 显示PDF文件
- [x] 书签
- [x] 缩放
- [x] 加密PDF文件


## Clion 配置
### 修改toolchain
- File -> Settings -> Build, Execution, Deployment -> Toolchains
- toolchain 修改为指定QT安装目录下tools对应的编译环境或者其他编译环境
### 修改cmake 
- File -> Settings -> Build, Execution, Deployment -> CMake
### 修改CMakelist.txt
- CMAKE_PREFIX_PATH 修改为指定QT安装目录下对应QT类库和源码（比如D:/software/Qt/6.7.2/mingw_64）
### 设置环境变量
- QT安装目录下对应QT类库和源码下bin目录添加到环境变量（比如D:\software\Qt\6.7.2\mingw_64\bin）


## 加密解密工具

(加密解密工具)[https://github.com/uyplayer/PDFEncrypter]
