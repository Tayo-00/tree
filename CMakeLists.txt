cmake_minimum_required(VERSION 3.10.0)
project(tr++ VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

file(GLOB TARGET_SRC "./src/*.cpp" )
file(GLOB TARGET_SUBFOLDERS "./src/*/*.cpp" )

add_executable(tr++ ${TARGET_SRC} ${TARGET_SUBFOLDERS})
target_include_directories(tr++ PRIVATE "./include")
target_compile_options(tr++ PRIVATE -O3 -Wall)