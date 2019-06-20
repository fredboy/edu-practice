cmake_minimum_required(VERSION 3.14)
project(study_practice C)

set(CMAKE_C_STANDARD 11)
set(SOURCES src/main/lists.h src/main/utils.h)

add_executable(study_practice src/main/main.c  ${SOURCES} src/main/utils.h)
add_executable(study_practice_test src/test/main.c ${SOURCES})
target_include_directories(study_practice_test PRIVATE thirdparty src/main)
target_link_libraries(study_practice m)
target_link_libraries(study_practice_test m)