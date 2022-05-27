cmake_minimum_required(VERSION 3.15)

project(basic-redis-cli LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic-errors)

target_link_libraries(${PROJECT_NAME} PRIVATE hiredis)
