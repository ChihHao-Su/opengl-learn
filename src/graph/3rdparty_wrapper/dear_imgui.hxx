#ifndef DEAR_IMGUI_HXX
#define DEAR_IMGUI_HXX

namespace DImGui {

	class Guard {
	public:
		~Guard();
	};

	Guard initWithGLFW(GLFWwindow &win);
}

#endif // !DEAR_IMGUI_HXX