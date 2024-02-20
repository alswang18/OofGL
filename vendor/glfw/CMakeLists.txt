project(GLFW)

# Create GLFW library interface
add_library(GLFW STATIC IMPORTED)

set_target_properties(GLFW PROPERTIES
  IMPORTED_LOCATION 
  ${PROJECT_SOURCE_DIR}/lib/glfw3.lib
)

# Promote the imported target to global visibility
set_target_properties(GLFW PROPERTIES
  IMPORTED_GLOBAL TRUE
)

# Set up include directories
target_include_directories(GLFW INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Alias for vendor::glfw
add_library(vendor::glfw ALIAS GLFW)
