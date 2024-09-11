#include "panic.hxx"

#include <iostream>

[[noreturn]] void Essentials::panicImpl(const char* s) noexcept
{
	std::fputs(s, stderr);
	std::abort();
}
