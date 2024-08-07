#include "opengl.hxx"
using namespace Essentials;


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


namespace OpenGL {

	const char* glsl_version = "#version 100";

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

	GLRes::GLRes(GLuint& data, std::function<void(GLuint)> deleter)
		: data(data), deleter(deleter) { }

	GLRes::GLRes(GLRes&& other) {
		this->data = other.data;
		this->deleter = other.deleter;
		other.data = 0;
		other.deleter = nullptr;
	}
	GLRes::GLRes() {
		this->data = 0;
	}
	GLRes::operator GLuint()
	{
		return data;
	}
	GLuint* GLRes::operator&()
	{
		return &data;
	}
	GLRes& GLRes::operator =(GLRes&& other) noexcept {

		if(this->deleter)
			deleter(data);

		this->data = other.data;
		this->deleter = other.deleter;
		other.data = 0;
		other.deleter = nullptr;
		return *this;
	}
	GLRes::~GLRes()
	{
		if(this->deleter)
			deleter(data);
	}

	void swap(GLRes& lhs, GLRes& rhs)
	{
		std::swap(lhs.data, rhs.data);
		std::swap(lhs.deleter, rhs.deleter);
	}

	GLRes makeShader(GLuint shader)
	{
		return GLRes{
			shader,
			[](auto shader) {
				if(shader != 0)
					glDeleteShader(shader);
			}
		};
	}

	GLRes makeBuffer(GLuint buffer) {
		return GLRes{
			buffer,
			[](auto buffer) {
				if(buffer != 0)
					glDeleteBuffers(1, &buffer);
			}
		};
	}

	GLRes makeTexture(GLuint texture) {
		return GLRes{
			texture,
			[](auto texture) {
				if (texture != 0)
					glDeleteTextures(1, &texture);
			}
		};
	}

	GLRes makeRenderBuffer(GLuint renderBuffer) {
		return GLRes{
			renderBuffer,
			[](auto renderBuffer) {
				if (renderBuffer != 0)
					glDeleteRenderbuffers(0, &renderBuffer);
			}
		};
	}

	GLRes makeFrameBuffer(GLuint frameBuffer)
	{
		return GLRes{
			frameBuffer,
			[](auto frameBuffer) {
				if(frameBuffer != 0)
					glDeleteFramebuffers(1, &frameBuffer);
			}
		};
	}

	GLRes makeProgram(GLuint program) {
		return GLRes{
			program,
			[](auto program) {
				if (program != 0)
					glDeleteProgram(program);
			}
		};
	}

	GLRes makeVertexArray(GLuint vertexArray) {
		return GLRes{
			vertexArray,
			[](auto vertexArray) {
				if (vertexArray != 0)
					glDeleteVertexArrays(1, &vertexArray);
			}
		};
	}

	void clearErrs() {
		while(glGetError() != GL_NO_ERROR);
	}
	void outErrs(std::ostream stream) {
		while(GLenum err = glGetError() != GL_NO_ERROR) {
			stream << "[OpenGL Error] " << err << '\n';
		}
	}
};
