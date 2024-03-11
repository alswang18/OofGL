cmake_minimum_required(VERSION 3.26)

project(OofGL)
set(CMAKE_CXX_STANDARD 17)

# only declare fetch content if we are the root project
include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

add_subdirectory(src/Core)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)

add_subdirectory(src/App)
