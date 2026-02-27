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



# 定义顶级目录变量（自定义名称，语义更清晰）
set(ROOT_PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(ROOT_PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR})

# 引入子工程
add_subdirectory(WebApp)

# 引用主工程定义的顶级目录变量，语义更明确
message(STATUS "顶级源码目录：${ROOT_PROJECT_SOURCE_DIR}")

