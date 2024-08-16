using namespace std;
using namespace Essentials;

#include "graph/std_3d_vertices_based_graph_obj.hxx"
#include "graph/graph_subsys.hxx"
#include "graph/3rdparty_wrapper/dear_imgui.hxx"



void start() {
	auto glWin = OpenGL::createGLWindow();

	INIT_SUBSYS(Graph);

	SUBSYS(Graph)::emplaceGraphObjToMasterScene(
		std::in_place_type<Graph::Std3DVerticesBasedGraphObj>
	);

	while (!glfwWindowShouldClose(glWin.get())) {
		// Poll and handle events (inputs, window resize, etc.)
		//
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		SUBSYS(Graph)::onFrame();
	}
}

int main()
{
	((void(*)())nullptr)();	// FIXME:

	Platform::Terminal::initDefaultSetting();
	cout << "Hello World!\n";

	try { 
		start();
	}
	PROCESS_UNHANDLED_EXCP;

	return 0;
}