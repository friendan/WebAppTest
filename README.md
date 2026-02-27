# WebAppTest
WebAppTest
project(WebApp LANGUAGES CXX)

${PROJECT_NAME}
${PROJECT_SOURCE_DIR}
${PROJECT_BINARY_DIR}

CMAKE_CURRENT_SOURCE_DIR	当前 CMakeLists.txt 所在的目

message(STATUS "顶级源码目录：${CMAKE_SOURCE_DIR}")
message(STATUS "顶级构建目录：${CMAKE_BINARY_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/include)
set(RESOURCE_FILE ${CMAKE_SOURCE_DIR}/resources/config.json)


set(CMAKE_INSTALL_PREFIX "C:/Program Files/${PROJECT_NAME}" CACHE PATH "Install prefix" FORCE)

# 定义顶级目录变量（自定义名称，语义更清晰）
set(ROOT_PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(ROOT_PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR})

# 引入子工程
add_subdirectory(WebApp)

# 引用主工程定义的顶级目录变量，语义更明确
message(STATUS "顶级源码目录：${ROOT_PROJECT_SOURCE_DIR}")

cmake_minimum_required(VERSION 3.10)

# ========== 设置配置类型 ==========
# 1. 定义支持的配置类型（Debug/Release/RelWithDebInfo/MinSizeRel）
# 顺序决定默认优先级，建议包含常用的4种
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "Supported build types" FORCE)

# 2. （可选）为多配置生成器设置默认配置（VS默认是Debug，可修改）
# 设置VS启动时的默认配置为Release
set(CMAKE_DEFAULT_BUILD_TYPE "Release" CACHE STRING "Default build type" FORCE)


# （补充）单配置生成器（Makefile）的默认编译类型
# 若未通过-DCMAKE_BUILD_TYPE指定，默认用Release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type for single-config generators" FORCE)
endif()

add_subdirectory(WebApp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE WebAppLib)

# 用CMAKE_BINARY_DIR指定可执行文件输出到 build/bin 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 静态库/动态库输出到 build/lib 目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)























