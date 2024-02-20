cmake_minimum_required(VERSION 3.28)

project(OofGL)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/Core)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(src/App)
