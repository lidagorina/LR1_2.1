cmake_minimum_required(VERSION 3.10)
project(dbms CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(dbms
    UI/main.cpp
    core/array.cpp
    core/flist.cpp
    core/dlist.cpp
    core/stack.cpp
    core/queue.cpp
    core/tree.cpp
)

target_compile_options(dbms PRIVATE -Wall -Wextra)
