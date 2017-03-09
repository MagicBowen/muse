
cmake_minimum_required(VERSION 2.8)

project(muse)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -g -std=c++1y")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include"
                    "${CMAKE_CURRENT_SOURCE_DIR}/deps/rapidjson/include")

add_subdirectory("src")

if(GTEST_ROOT)
    add_subdirectory("test")
endif()

install(DIRECTORY include/muse DESTINATION include)
