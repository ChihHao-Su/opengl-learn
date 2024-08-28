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
#include <variant>
#include <optional>
#include <any>

#include <boost/container/static_vector.hpp>

#include <gsl/span>

#include <glad/gles2.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <essentials/def.hxx>
#include <essentials/excp.hxx>
#include <essentials/panic.hxx>
#include <essentials/file.hxx>
//#include <essentials/ref.inl>
#include <essentials/platform/terminal.hxx>
#include <essentials/memory/static_obj_holder.hxx>
#include <essentials/memory/static_obj_ref.hxx>

#include "subsys.h"

template<class T>
struct tag_t { using type = T; };

template<class F>
struct deduce_return_t {
	F f;
	template<class T>
	operator T()&& { return std::forward<F>(f)(tag_t<T>{}); }
};
template<class F>
deduce_return_t(F&&) -> deduce_return_t<F>;

template<class...Args>
auto construct_from(Args&&... args) {
	return deduce_return_t{ [&](auto ret) {
	  using R = typename decltype(ret)::type;
	  return R{ std::forward<Args>(args)... };
	} };
}


#endif // STDAFX_H
