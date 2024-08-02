cmake_minimum_required(VERSION 3.5)
project(essentials LANGUAGES CXX)

find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_library(essentials SHARED
	"src/essentials/panic.cxx"
	"src/essentials/file.cxx"
	"src/essentials/excp.cxx"
	"src/essentials/platform/terminal.cxx"
 "src/essentials/ref.ixx")

target_include_directories(essentials PUBLIC
	src
)

target_link_libraries(essentials PUBLIC
	Boost::boost
	Microsoft.GSL::GSL
)

set_target_properties(essentials PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)

#  Config boost_stacktrace backend
if(UNIX)
	target_compile_definitions(essentials PUBLIC
		BOOST_STACKTRACE_USE_ADDR2LINE
	)
endif()

include(GNUInstallDirs)
install(TARGETS essentials
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
