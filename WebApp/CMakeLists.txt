project(WebApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SRCS "*.h" "*.cpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS})
add_executable(WebApp ${SRCS})
target_include_directories(WebApp PRIVATE ${CMAKE_SOURCE_DIR}/libhv/include)
target_link_libraries(WebApp hv_static)
