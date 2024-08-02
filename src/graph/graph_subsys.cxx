#include "graph_subsys.hxx"
#include "Excp/shader_compile_failed_excp.hxx"

using namespace std;
using namespace Essentials;

IMPL_SYBSYS(Graph)
{
	OpenGL::GLRes screenProgram;
	OpenGL::GLRes screenFb;
	OpenGL::GLRes masterSceneScreenFb;
	OpenGL::GLRes slaveSceneScreenFb;

	IMPL_SYBSYS_INIT_FUNC() {
		reloadMainScreenGlProgram();
	}

	IMPL_SUBSYS_INTERNAL
	{
		OpenGL::GLRes createScreenGPUProgram() {
			return createGlShadersProgram(
				File::read("res/screen_shader.vert"),
				File::read("res/screen_shader.frag")
			);
		}
	};

	void reloadMainScreenGlProgram() {
		screenProgram = SUBSYS_INTERNAL::createScreenGPUProgram();
	}

	OpenGL::GLRes createGlShadersProgram(
			const std::string &vertShaderSrc,
			const std::string &fragShaderSrc
	) {
		OpenGL::GLRes newVertexShader;
		OpenGL::GLRes newFragShader;

		newVertexShader = compileShader(vertShaderSrc, GL_VERTEX_SHADER);
		newFragShader = compileShader(fragShaderSrc, GL_FRAGMENT_SHADER);

		auto newScreenProgram = OpenGL::makeProgram(glCreateProgram());
		glAttachShader(newScreenProgram, newVertexShader);
		glAttachShader(newScreenProgram, newFragShader);
		glLinkProgram(newScreenProgram);
		glValidateProgram(newScreenProgram);

		return newScreenProgram;
	}

	string getShaderInfoLog(OpenGL::GLRes &shader) {
		GLint totalLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &totalLength);
		std::string logs;
		logs.resize(totalLength);
		glGetShaderInfoLog(shader, totalLength, NULL, &logs[0]);

		// 移除末尾的 \n\0
		logs.pop_back();
		logs.pop_back();

		return logs;
	}


	OpenGL::GLRes compileShader(const std::string &src, const GLenum shaderType) {
		auto shader = OpenGL::makeShader(glCreateShader(shaderType));
		UNSAFE(
			auto shaderSrcCStr = src.c_str();
			glShaderSource(shader, 1, &shaderSrcCStr, nullptr);
		)
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			throw ShaderCompileFailedExcp {
				format("Compiling shader failed: {}", getShaderInfoLog(shader))
			};
		}
		return shader;
	}
}