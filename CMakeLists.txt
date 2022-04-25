#CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

#指定项目名称
project(Tinyhttpd)

# 添加源文件列表
aux_source_directory(. DIR_SRC)


# 打印编译目录和项目目录路径
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})
# 生成可执行文件
ADD_EXECUTABLE(Tinyhttpd ${DIR_SRC})
