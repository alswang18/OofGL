cmake_minimum_required(VERSION 3.26)

project(OofGL)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  # Use Debug libraries
  message(STATUS "Building in Debug mode. Using /MTd.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")  # Multi-threaded Debug
else()
  message(STATUS "Building in Release mode. Using /MT.")
  # Use Release libraries
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")  # Multi-threaded Release
endif()

# add vendor to the include directories
message(STATUS "Adding vendor directories")
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/glm)
message(STATUS "Adding vendor directories DONE")

# use resource files from res
message(STATUS "Adding resources")
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
cmake_path(SET RESOURCE_DIR "${CMAKE_BINARY_DIR}/res")
cmake_path(SET SHADER_DIR "${RESOURCE_DIR}/shaders")
add_definitions(-DRESOURCE_DIR="${RESOURCE_DIR}")
add_definitions(-DSHADER_DIR="${SHADER_DIR}")


# add the core and app directories
message(STATUS "Adding subdirectories")
add_subdirectory(src/Core)
add_subdirectory(src/App)
message(STATUS "Adding subdirectories DONE")
