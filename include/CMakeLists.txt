cmake_minimum_required(VERSION 3.23)

add_executable(search_engine_inc engine.h)
target_include_directories(search_engine_inc PUBLIC include)