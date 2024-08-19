cmake_minimum_required(VERSION 3.26)
project(imgui_glfw_learn LANGUAGES CXX)

## pre. Options
option(VS_IDE "Enable Visual Studio IDE experience improvement" OFF)

## 0. Language specification #################
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## 0.0. Compilers settings
# MSVC: Enable :
# - multithread compiling,
# - utf-8 source file decoding,
# - standard preprocessor behaviour
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/MP>" "$<$<C_COMPILER_ID:MSVC>:/utf-8>" "$<$<C_COMPILER_ID:MSVC>:/Zc:preprocessor>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/MP>" "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>" "$<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>")

## 1. Dependencies ###########################
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
add_subdirectory(subprojects/essentials/)
add_subdirectory(thirdparty/glad2_gles3/)
add_subdirectory(thirdparty/dear_imgui/)

## 2. Executable target ############################
add_executable(imgui_glfw_learn
	src/stdafx.cpp
	"src/main.cxx"
	"src/graph/3rdparty_wrapper/opengl.cxx"
	"src/graph/3rdparty_wrapper/dear_imgui.cxx"
	"src/graph/Pojo/vertex.cxx"
 "src/graph/rendering/irenderer_itfc.cxx" "src/graph/rendering/irenderer_variant.cxx" "src/graph/rendering/simple_2d_geo_renderer.cxx" "src/graph/Serv/graph_api_serv.cxx")

target_precompile_headers(imgui_glfw_learn PRIVATE src/stdafx.h)

target_link_libraries(imgui_glfw_learn PRIVATE
	dear_imgui_gles2_glfwbackend_no_gl_loader
	glad2_gles30
	glfw
	OpenGL::GL
	Microsoft.GSL::GSL
	essentials
)

add_dependencies(imgui_glfw_learn essentials glad2_gles30 dear_imgui_gles2_glfwbackend_no_gl_loader)

## 3. IDE experience improvement
if(${VS_IDE})
	include("cmake/ide_xp/visual_studio.cmake")
	enable_vs_guideline_checker(imgui_glfw_learn essentials)
endif()

## 4. Post-build actions #####################
# 4.0. Windows: Copy all dlls to executable's build folder.
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_custom_command(TARGET imgui_glfw_learn POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:imgui_glfw_learn> $<TARGET_FILE_DIR:imgui_glfw_learn>
		COMMAND_EXPAND_LISTS
	)
endif()
# 4.1. Copy all resources folder into executable's build folder.
add_custom_target(copy_assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_CURRENT_SOURCE_DIR}/res $<TARGET_FILE_DIR:imgui_glfw_learn>/res
	COMMAND_EXPAND_LISTS
)
add_dependencies(imgui_glfw_learn copy_assets)


## 5. Install ################################
include(GNUInstallDirs)
install(TARGETS imgui_glfw_learn
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
