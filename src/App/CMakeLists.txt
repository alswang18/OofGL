project(OofGLApp)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the static library from subproject1 using its alias sub::lib1
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME} PRIVATE
    core::rendering
)

# make sure to exclude the debug version msvcrt is what we want for release
if(CMAKE_BUILD_TYPE MATCHES "Debug")
  # Ignore the non debug libraries
    message(STATUS "Building in Debug mode. Not ignoring debug libraries.")
else()
  message(STATUS "Building in Release mode.")
  # Ignore the debug libraries
  target_link_options(${PROJECT_NAME} PRIVATE "/NODEFAULTLIB:MSVCRTD")
endif()
