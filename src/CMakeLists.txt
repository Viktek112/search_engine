cmake_minimum_required(VERSION 3.23)

add_executable(search_engine_exe engine.cpp main.cpp)
target_include_directories(search_engine_exe PUBLIC src)