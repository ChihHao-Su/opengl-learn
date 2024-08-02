#include "excp.hxx"

#include <sstream>
#include <format>
#include <iostream>
#include <boost/stacktrace.hpp>

namespace Essentials::Excp {
	std::string descExcp(const std::exception& ex)
	{
		std::stringstream msg;
		msg << ex.what();
		try {
			std::rethrow_if_nested(ex);
		} catch (const std::exception& nestedException) {
			msg << "，因爲："<< descExcp(ex) <<'\n';
		}

		return msg.str();
	}

	std::string descExcp(const RuntimeExcp& ex) {
		std::stringstream msg;
		msg << std::format("{}，調用棧： \n{}",
			ex.what(),
			ex.getStackTrace()
		);

		try {
			std::rethrow_if_nested(ex);
		} catch (const RuntimeExcp& ex) {
			msg << "\n，因爲："<< descExcp(ex) <<'\n';
		} catch (const std::exception& nestedException) {
			msg << "\n，因爲："<< descExcp(ex) <<'\n';
		}

		return msg.str();
	}
	void showExcpAndAbort(const std::exception& ex)
	{
		std::cerr << "發生異常："
			<< descExcp(ex)
			<< "\n";
		std::terminate();
	}

	void showExcpAndAbort(const RuntimeExcp& ex) {
		std::cerr << "發生異常："
			<< descExcp(ex)
			<< "\n";
		std::terminate();
	}

	RuntimeExcp::RuntimeExcp(const std::string& msg)
		: std::runtime_error{ msg }
	{ 
		std::stringstream ss;
		ss << boost::stacktrace::stacktrace();
		this->stackTrace = ss.str();
	}
	std::string RuntimeExcp::getStackTrace() const
	{
		return stackTrace;
	}
}
