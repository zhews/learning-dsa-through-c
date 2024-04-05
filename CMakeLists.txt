cmake_minimum_required(VERSION 3.28.3)
project(learning-dsa-through-c)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-Wall -Wextra -Werror -pedantic)

add_executable(linear_search linear_search.c)
add_executable(binary_search binary_search.c)
add_executable(two_crystal_balls two_crystal_balls.c)
add_executable(bubble_sort bubble_sort.c)
add_executable(queue queue.c)
add_executable(stack stack.c)
add_executable(array_list array_list.c)

target_link_libraries(two_crystal_balls m)
target_link_libraries(array_list m)
