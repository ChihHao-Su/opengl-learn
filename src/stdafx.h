#ifndef STDAFX_H
#define STDAFX_H

// Platform dependented headers
#ifdef WIN32
#include <windows.h>
#endif

#include <cstdio>
#include <functional>
#include <iostream>
#include <print>
#include <utility>
#include <optional>

#include <glad/gles2.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <essentials/def.hxx>
#include <essentials/excp.hxx>
#include <essentials/panic.hxx>
#include <essentials/file.hxx>
#include <essentials/ref.inl>
#include <essentials/platform/terminal.hxx>

#include "subsys.h"


#endif // STDAFX_H
