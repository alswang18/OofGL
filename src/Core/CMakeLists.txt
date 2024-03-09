# Set the project name
project (AppCore)

# Add a library with the above sources
add_library(${PROJECT_NAME} calc.cpp)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

# target link vendor/glfw
target_link_libraries(${PROJECT_NAME}
    vendor::glfw
    vendor::glad
)

add_library(core::rendering ALIAS ${PROJECT_NAME})
