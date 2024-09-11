#ifndef PANIC_HXX
#define PANIC_HXX

#include "def.hxx"
#include <sstream>
#include <format>
#include <tuple>
#include <source_location>
#include <boost/stacktrace.hpp>
#include "excp.hxx"

namespace Essentials {
	template <class... Args>
	struct PanicFormat {
		template <class T>
		consteval PanicFormat(    // note: consteval is what allows for compile-time checking of the
			const T& s,            //       format string
			std::source_location loc = std::source_location::current()) noexcept
			: fmt{ s }, loc{ loc } {}

		std::format_string<Args...> fmt;
		std::source_location loc;
	};

	[[noreturn]] void panicImpl(const char* s) noexcept;

	
	template <class... Args>
	FUNC_CLASS panic
	{
		[[noreturn]] panic(
			const Excp::RuntimeExcp& reason,
			// std::type_identity_t is needed to prevent deduction.
			PanicFormat<std::type_identity_t<Args>...> fmt,
			Args &&...args
		) {
			auto prompt = std::format(
				"終止：{}，位於文件 {}:{}，調用棧：\n",
				std::format(fmt.fmt, std::forward<Args>(args)...),
				fmt.loc.file_name(),
				fmt.loc.line()
			);

			std::stringstream ss;
			ss << prompt;
			ss << boost::stacktrace::stacktrace()
			   << "因爲：" << descExcp(reason) << '\n';

			std::string msg = ss.str();
			panicImpl(msg.c_str()); // print msg and abort
		}

		[[noreturn]] panic(
			// std::type_identity_t is needed to prevent deduction.
			PanicFormat<std::type_identity_t<Args>...> fmt,
			Args &&...args
		) {
			auto prompt = std::format(
				"終止：{}，位於文件 {}:{}，調用棧：\n",
				std::format(fmt.fmt, std::forward<Args>(args)...),
				fmt.loc.file_name(),
				fmt.loc.line()
			);

			std::stringstream ss;
			ss << prompt;
			ss << boost::stacktrace::stacktrace() << '\n';

			std::string msg = ss.str();
			panicImpl(msg.c_str()); // print msg and abort
		}
	};
	
};
#endif // !PANIC_HXX
