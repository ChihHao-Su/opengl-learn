#include "opengl.hxx"
using namespace Essentials;


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


namespace Graph::OpenGL {

	const char* glsl_version = "#version 100";

	void clearErrs() {
		while (glGetError() != GL_NO_ERROR);
	}
	void outErrs(std::ostream stream) {
		while (GLenum err = glGetError() != GL_NO_ERROR) {
			stream << "[OpenGL Error] " << err << '\n';
		}
	}

	GLFWWindowBox createGLWindow()
	{
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
			panic("GLFW 初始化失敗！");

		// OpenGL ES 3.0 初期化
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window with graphics context
		GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
		if (window == nullptr)
			panic("glfwCreateWindow 失敗！");
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync

		int version = gladLoadGLES2(glfwGetProcAddress);
		std::print("GLAD: GL {}.{} loaded.\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

		return GLFWWindowBox{ window, [](auto window) {
			glfwDestroyWindow(window);
			glfwTerminate();
		} };
	}

	GLIndividualRes::GLIndividualRes(GLuint& data, std::function<void(GLuint)> deleter)
		: data(data), deleter(deleter) { }

	/*GLIndividualRes::GLIndividualRes(GLIndividualRes&& other) {
		this->data = other.data;
		this->deleter = other.deleter;
		other.data = 0;
		other.deleter = nullptr;
	}*/
	GLIndividualRes::GLIndividualRes() {
		this->data = 0;
	}
	GLIndividualRes::operator GLuint()
	{
		return data;
	}
	GLuint* GLIndividualRes::operator&()
	{
		return &data;
	}
	GLIndividualRes& GLIndividualRes::operator =(GLIndividualRes&& other) noexcept {

		if(this->deleter)
			deleter(data);

		this->data = other.data;
		this->deleter = other.deleter;
		other.data = 0;
		other.deleter = nullptr;
		return *this;
	}
	GLIndividualRes::~GLIndividualRes()
	{
		if(this->deleter)
			deleter(data);
	}

	void swap(GLIndividualRes& lhs, GLIndividualRes& rhs)
	{
		std::swap(lhs.data, rhs.data);
		std::swap(lhs.deleter, rhs.deleter);
	}

	GLIndividualRes makeShader(GLuint shader)
	{
		return GLIndividualRes{
			shader,
			[](auto shader) {
				if(shader != 0)
					glDeleteShader(shader);
			}
		};
	}

	GLIndividualRes makeBuffer(GLuint buffer) {
		return GLIndividualRes{
			buffer,
			[](auto buffer) {
				if(buffer != 0)
					glDeleteBuffers(1, &buffer);
			}
		};
	}

	GLIndividualRes makeTexture(GLuint texture) {
		return GLIndividualRes{
			texture,
			[](auto texture) {
				if (texture != 0)
					glDeleteTextures(1, &texture);
			}
		};
	}

	GLIndividualRes makeRenderBuffer(GLuint renderBuffer) {
		return GLIndividualRes{
			renderBuffer,
			[](auto renderBuffer) {
				if (renderBuffer != 0)
					glDeleteRenderbuffers(0, &renderBuffer);
			}
		};
	}

	GLIndividualRes makeFrameBuffer(GLuint frameBuffer)
	{
		return GLIndividualRes{
			frameBuffer,
			[](auto frameBuffer) {
				if(frameBuffer != 0)
					glDeleteFramebuffers(1, &frameBuffer);
			}
		};
	}

	GLIndividualRes makeProgram(GLuint program) {
		return GLIndividualRes{
			program,
			[](auto program) {
				if (program != 0)
					glDeleteProgram(program);
			}
		};
	}

	GLIndividualRes makeVertexArray(GLuint vertexArray) {
		return GLIndividualRes{
			vertexArray,
			[](auto vertexArray) {
				if (vertexArray != 0)
					glDeleteVertexArrays(1, &vertexArray);
			}
		};
	}

	∃GLResView::∃GLResView(GLIndividualRes& res)
		: getGLRawRes([&res]() -> GLuint { return res; })
	{
	}

	∃GLResView::operator GLuint()
	{
		return getGLRawRes();
	}

	∃GLResHolder::∃GLResHolder(GLIndividualRes&& res)
		: getGLRawRes([res = std::move(res)]() mutable -> GLuint { return res; })
	{ }

	∃GLResHolder::operator GLuint()
	{
		return getGLRawRes();
	}
};
