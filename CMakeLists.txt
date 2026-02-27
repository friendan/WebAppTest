cmake_minimum_required(VERSION 3.10)
project(WebAppTest)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported build types" FORCE)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/build" CACHE PATH "Install prefix" FORCE)
add_subdirectory(WebApp)



