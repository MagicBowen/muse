
set(PROJECT_NAME "muse")

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(${PROJECT_NAME} STATIC ${all_files})

install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)
