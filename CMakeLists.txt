# CMake generates build instructions; this is the minimum supported CMake version.
cmake_minimum_required(VERSION 3.16)
# Name the project and enable C++ compilation without introducing a second application main.
project(DataVisualization VERSION 1.0 LANGUAGES CXX)
# Require standard C++17 rather than silently compiling with an older language mode.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Keep the language mode portable instead of relying on compiler-specific extensions.
set(CMAKE_CXX_EXTENSIONS OFF)
# Let CTest discover the test programs registered in the library subdirectory.
enable_testing()
# The real library, examples and test targets are defined below this directory.
add_subdirectory(DataVisualization)
