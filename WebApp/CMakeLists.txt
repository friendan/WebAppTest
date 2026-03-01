project(WebApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(WebApp main.cpp)
target_include_directories(WebApp PRIVATE ${CMAKE_SOURCE_DIR}/libhv/include)
target_link_libraries(WebApp hv_static)
