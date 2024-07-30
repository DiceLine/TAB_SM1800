
cmake_minimum_required(VERSION 3.12.4 FATAL_ERROR)

project(TAB_SM1800 VERSION 0.0.1)

set(SOURCE main.cpp AssemblerCM1800.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
