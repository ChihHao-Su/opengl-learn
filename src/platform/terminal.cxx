#include "terminal.hxx"
#include <cstdio>

void Platform::Terminal::initDefaultSetting() {
	initCharset();
	disableBuffering();
}

#ifdef WIN32
static const int winUTF8CodePageId = 65001;
void Platform::Terminal::initCharset()
{
	SetConsoleOutputCP(winUTF8CodePageId);
}

#elif defined(unix) || defined(__APPLE__)
void Platform::Terminal::initCharset()
{
	// NOP
}

#else
#error "Unsupported platform."
#endif

void Platform::Terminal::disableBuffering() {
	setvbuf(stdout, NULL, _IONBF, 0);
}
