
set(PROJECT_NAME "test_muse")

project(${PROJECT_NAME})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
                    "${GTEST_ROOT}/include")

link_directories("${GTEST_ROOT}/lib")                  

file(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(${PROJECT_NAME} ${all_files})

target_link_libraries(${PROJECT_NAME} muse gtest)
