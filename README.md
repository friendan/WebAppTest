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


# 匹配当前目录下所有.cpp文件，存入变量SRCS
file(GLOB SRCS "*.cpp")
# 匹配当前目录下所有.h文件，存入变量 HEADERS
file(GLOB HEADERS "*.h")

# 递归匹配当前目录及所有子目录下的.cpp文件
file(GLOB_RECURSE SRCS "*.cpp")
# 递归匹配当前目录及所有子目录下的.h文件
file(GLOB_RECURSE HEADERS "*.h")

# 也可以指定具体目录递归匹配（更精准，推荐）
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")


# 匹配src目录下的.cpp，include目录下的.h（非递归）
file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

# 匹配多个目录的文件（用分号分隔）
file(GLOB SRCS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
)

# 排除特定文件（比如排除test.cpp）
file(GLOB_RECURSE SRCS "*.cpp")
list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/test.cpp")

cmake_minimum_required(VERSION 3.10)
project(WebAppTest LANGUAGES CXX)

# ========== 第一步：递归获取所有源文件/头文件（指定目录） ==========
# 递归获取src目录下的所有.cpp/.c文件
file(GLOB_RECURSE ALL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
# 递归获取include目录下的所有.h/.hpp文件
file(GLOB_RECURSE ALL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

# 合并所有文件（可选：头文件加入后VS中才会显示）
set(ALL_FILES ${ALL_SOURCES} ${ALL_HEADERS})

# ========== 第二步：核心 - 按目录结构为VS设置分组 ==========
foreach(FILE ${ALL_FILES})
    # 1. 获取文件相对于工程根目录的相对路径
    file(RELATIVE_PATH REL_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${FILE})
    
    # 2. 提取文件所在的目录（作为VS分组名）
    get_filename_component(FILE_DIR ${REL_FILE_PATH} DIRECTORY)
    
    # 3. 替换路径分隔符：将Linux/macOS的"/"换成VS分组的"\"
    string(REPLACE "/" "\\" FILE_DIR_VS ${FILE_DIR})
    
    # 4. 设置VS分组（如果目录为空，归为"根目录"，避免平铺）
    if(FILE_DIR_VS STREQUAL "")
        set(FILE_DIR_VS "根目录")
    endif()
    
    # 5. 为文件分配分组
    source_group(${FILE_DIR_VS} FILES ${FILE})
endforeach()

# ========== 常规编译配置 ==========
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成可执行文件（使用分组后的文件）
add_executable(${PROJECT_NAME} ${ALL_FILES})

# 包含头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 一键按目录分组（推荐CMake 3.16+使用）
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})
































