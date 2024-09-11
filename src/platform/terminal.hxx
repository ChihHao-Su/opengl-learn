#ifndef TERMINAL_HPP
#define TERMINAL_HPP

namespace Platform::Terminal {
	void initDefaultSetting();

	/**
	* @brief Set charset to UTF-8.
	*/
	void initCharset();

	/**
	* @brief Disable buffering.
	* This is for GUI program. GUI programs doesn't wait for
	* user's console input, this will have an adverse impact on
	* buffering, which will not flush stdout / stderr's content
	* on the terminal.
	*/
	void disableBuffering();
};

#endif // !TERMINAL_HPP
