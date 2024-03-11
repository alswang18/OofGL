project(imgui)

add_library(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/src/imgui.cpp
    ${PROJECT_SOURCE_DIR}/src/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/src/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/src/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/src/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/src/imgui_impl_opengl3.cpp
    ${PROJECT_SOURCE_DIR}/src/imgui_tables.cpp
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
    vendor::glfw
)

add_library(vendor::imgui ALIAS imgui)