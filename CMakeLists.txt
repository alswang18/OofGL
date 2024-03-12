cmake_minimum_required(VERSION 3.26)

project(OofGL)
set(CMAKE_CXX_STANDARD 17)

# only declare fetch content if we are the root project
# this fetches glm, a gl math library
include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 		1.0.1 #refs/tags/1.0.1
)

message(STATUS "Making glm available")
FetchContent_MakeAvailable(glm)
message(STATUS "Fetching glm DONE")

# add vendor to the include directories
message(STATUS "Adding vendor directories")
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
message(STATUS "Adding vendor directories DONE")

# add the core and app directories
message(STATUS "Adding subdirectories")
add_subdirectory(src/Core)
add_subdirectory(src/App)
add_subdirectory(res/shaders)
message(STATUS "Adding subdirectories DONE")
