cmake_minimum_required(VERSION 3.0.0)
project(tr++ VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

file(GLOB TARGET_SRC "./src/*.cpp" )

add_executable(tr++ ${TARGET_SRC})