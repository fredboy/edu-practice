cmake_minimum_required(VERSION 3.12)
project(edu_practice C)

set(CMAKE_C_STANDARD 11)
set(SOURCES src/main/lists.h src/main/utils.h)

add_executable(edu_practice src/main/main.c  ${SOURCES})
add_executable(edu_practice_test src/test/main.c ${SOURCES})
target_include_directories(edu_practice_test PRIVATE thirdparty src/main)
target_link_libraries(edu_practice m)
target_link_libraries(edu_practice ncursesw)
target_link_libraries(edu_practice_test m)
