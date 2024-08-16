#include "graph/3rdparty_wrapper/opengl.hxx"
#include "graph/3rdparty_wrapper/dear_imgui.hxx"

using namespace std;
using namespace Essentials;


pair<OpenGL::GLIndividualRes, OpenGL::GLIndividualRes> createScreenVertexs () {
	static GLfloat vertexs[] = {
		 // Coords     // texCoords
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,

		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};

	auto screenVertexArray = OpenGL::makeVertexArray();
	glGenVertexArrays(1, &screenVertexArray);
	GL_BIND_VERT_ARR(screenVertexArray, BEGIN(
		auto screenVertexBuffer = OpenGL::makeBuffer();
		glGenBuffers(1, &screenVertexBuffer);
		GL_BIND_ARR_BUFFER(screenVertexBuffer, BEGIN(
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(2 * sizeof(GLfloat)));
		));
	));
	return { std::move(screenVertexBuffer), std::move(screenVertexArray) };
}



pair<OpenGL::GLIndividualRes, OpenGL::GLIndividualRes> initScreenFbAndTexture() {
	// Init screen texture
	auto screenFrameBuffer = OpenGL::makeFrameBuffer();
	glGenFramebuffers(1, &screenFrameBuffer);
	GL_BIND_FRAME_BUFFER(screenFrameBuffer, BEGIN(
		// generate texture
		auto screenTexture = OpenGL::makeTexture();
		glGenTextures(1, &screenTexture);
		GL_BIND_TEXTURE(GL_TEXTURE_2D, screenTexture, BEGIN(
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
		));
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);


		// 永久存在
		static auto renderBuffer = OpenGL::makeRenderBuffer();
		glGenRenderbuffers(1, &renderBuffer);
		GL_BIND_RENDER_BUFFER(renderBuffer, BEGIN(
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, 800, 600);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
		));
		

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			panic("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	
	));

	return { std::move(screenFrameBuffer), std::move(screenTexture) };
}

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void drawUI() {
	ImGuiIO& io = ImGui::GetIO();

	// Our state
	static bool show_demo_window = true;
	static bool show_another_window = false;

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		//ImGUI：
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

}

void renderUIToScreenFb(GLFWwindow& win, OpenGL::GLIndividualRes &screenFrameBuffer) {
	// Rendering
	GL_BIND_FRAME_BUFFER(screenFrameBuffer, BEGIN(
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(&win, &display_w, &display_h);
		glViewport(0, 0, 800, 600);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glDisable(GL_DEPTH_TEST);

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		GLFWwindow * backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
		//glfwSwapBuffers(&win);
	));
}

void paintScreenTextureOnScreen(GLFWwindow& win, OpenGL::GLIndividualRes& screenTexture, OpenGL::GLIndividualRes& screenVertexArray, OpenGL::GLIndividualRes& screenGPUProg) {

	int display_w, display_h;
	glfwGetFramebufferSize(&win, &display_w, &display_h);

	// glViewport(0, 0, 800, 600);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(screenGPUProg);
	GL_BIND_VERT_ARR(screenVertexArray, BEGIN(
		GL_BIND_TEXTURE(GL_TEXTURE_2D, screenTexture, BEGIN(
			glDrawArrays(GL_TRIANGLES, 0, 6);
		));
	));

	glfwSwapBuffers(&win);
}


void start() {
	/*auto glWin = OpenGL::createGLWindow();
	auto imGuiGuard = DImGui::initWithGLFW(*glWin);

	auto screenGPUProg = createScreenGPUProgram();
	auto [screenVertexBuffer, screenVertexArray] = createScreenVertexs();
	auto [screenFb, screenTexture] = initScreenFbAndTexture();
	//initScreenQuad();

	while (!glfwWindowShouldClose(glWin.get())) {
		// Poll and handle events (inputs, window resize, etc.)
		//
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		drawUI();
		renderUIToScreenFb(*glWin, screenFb);
		paintScreenTextureOnScreen(*glWin, screenTexture, screenGPUProg, screenVertexArray);
	}*/
}

int main()
{
	Platform::Terminal::initDefaultSetting();
	cout << "Hello World!\n"
		<< "漢字漢字\n";

	try {
		start();
	}
	PROCESS_UNHANDLED_EXCP;

	return 0;
}
