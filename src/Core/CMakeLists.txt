cmake_minimum_required(VERSION 3.26)

# Set the project name
project (AppCore)

# Add a library with the above sources
add_library(${PROJECT_NAME} window.cpp)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# target link
target_link_libraries(${PROJECT_NAME}
    vendor::glfw
    vendor::glad
    vendor::imgui
    glm::glm
)

add_library(core::rendering ALIAS ${PROJECT_NAME})
