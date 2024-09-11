# 本目錄代碼來源於 dear imgui docking 分支。

cmake_minimum_required(VERSION 3.5)
project(dear_imgui_gl3_glfwbackend LANGUAGES CXX)

find_package(glfw3 CONFIG REQUIRED)

add_library(dear_imgui_gles2_glfwbackend_no_gl_loader SHARED
    src/imgui.cpp
    src/imgui_demo.cpp
    src/imgui_draw.cpp
    src/imgui_tables.cpp
    src/imgui_widgets.cpp
    src/backends/imgui_impl_opengl3.cpp
    src/backends/imgui_impl_glfw.cpp
)


target_include_directories(dear_imgui_gles2_glfwbackend_no_gl_loader PUBLIC src src/backends)

target_link_libraries(dear_imgui_gles2_glfwbackend_no_gl_loader PUBLIC glfw glad2_gles30)

add_dependencies(dear_imgui_gles2_glfwbackend_no_gl_loader glad2_gles30)

set_target_properties(dear_imgui_gles2_glfwbackend_no_gl_loader PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

target_compile_definitions(dear_imgui_gles2_glfwbackend_no_gl_loader PUBLIC
    IMGUI_IMPL_OPENGL_ES2
    IMGUI_IMPL_OPENGL_LOADER_CUSTOM
)
