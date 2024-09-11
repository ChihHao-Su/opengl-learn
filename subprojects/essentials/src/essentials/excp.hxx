#ifndef EXCP_HXX
#define EXCP_HXX

#include <string>
#include <stdexcept>

namespace Essentials::Excp {

	class RuntimeExcp : public std::runtime_error {
	private:
		std::string stackTrace;
	public:
		RuntimeExcp(const std::string& msg);
		std::string getStackTrace() const;
		
	};

	std::string descExcp(const std::exception &ex);
	std::string descExcp(const RuntimeExcp& ex);
	void showExcpAndAbort(const std::exception& ex);
	void showExcpAndAbort(const RuntimeExcp& ex);
}


#define PROCESS_UNHANDLED_EXCP \
	catch(const Essentials::Excp::RuntimeExcp &ex) { \
		Essentials::Excp::showExcpAndAbort(ex); \
	} \
	catch (const std::exception& ex) { \
		Essentials::Excp::showExcpAndAbort(ex); \
	}

#define PANIC_ON_EXCP(excpClass, ...) \
	catch(const excpClass& e) { \
		panic(e, __VA_ARGS__); \
	}

#define WARP_EXCP(excpClassToCatch, newExcp) \
	catch([[maybe_unused]] const excpClassToCatch& e) { \
		std::throw_with_nested(newExcp); \
	}

#define TRY_EVAL(expr, ...) \
	[&] { \
		try { \
			return expr; \
		} __VA_ARGS__\
	}()


#endif