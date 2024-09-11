# 客制化 GLAD2，不可用其餘來源的 GLAD2 替換。

cmake_minimum_required(VERSION 3.5)
project(glad2_gles30 LANGUAGES C)

add_library(glad2_gles30 SHARED
	src/gles2.c
	src/egl.c
)

target_include_directories(glad2_gles30 PUBLIC
	include
)

target_compile_definitions(glad2_gles30
	PRIVATE
	GLAD_API_CALL_EXPORT_BUILD
	PUBLIC
	GLAD_API_CALL_EXPORT
)