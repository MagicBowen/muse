cmake_minimum_required(VERSION 2.8)

project(promise_dsl)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -g -std=c++1y")
endif()

set(MUSE_ROOT /Users/wangbo/codes/muse)
set(ANTLR_CPP_RUNTIME /Users/wangbo/codes/antlr/antlr4-cpp-runtime-macos)

include_directories("${MUSE_ROOT}/code/include"
                    "${ANTLR_CPP_RUNTIME}/antlr4-runtime")

link_directories("${ANTLR_CPP_RUNTIME}/lib"
                 "${MUSE_ROOT}/project/build/src")                  

file(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(promise_dsl ${all_files})

target_link_libraries(promise_dsl muse antlr4-runtime)
