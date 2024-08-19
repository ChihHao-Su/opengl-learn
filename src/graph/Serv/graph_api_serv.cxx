#include "graph_api_serv.hxx"
#include "../Excp/shader_compile_failed_excp.hxx"

namespace Graph::GraphApiServ {
	std::string getShaderInfoLog(OpenGL::GLIndividualRes& shader)
	{
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

	void compileShader(GLResHolderconst std::string& src, const GLenum shaderType)
	{
		auto shader = OpenGL::makeShader(glCreateShader(shaderType));
		UNSAFE(
			auto shaderSrcCStr = src.c_str();
			glShaderSource(shader, 1, &shaderSrcCStr, nullptr);
		)
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			throw ShaderCompileFailedExcp{
				format("Compiling shader failed: {}", getShaderInfoLog(shader))
			};
		}
		return shader;
	}

	OpenGL::GLIndividualRes createGlShadersProgram(const std::string& vertShaderSrc, const std::string& fragShaderSrc)
	{
		OpenGL::GLIndividualRes newVertexShader;
		OpenGL::GLIndividualRes newFragShader;

		newVertexShader = compileShader(vertShaderSrc, GL_VERTEX_SHADER);
		newFragShader = compileShader(fragShaderSrc, GL_FRAGMENT_SHADER);

		auto newScreenProgram = OpenGL::makeProgram(glCreateProgram());
		glAttachShader(newScreenProgram, newVertexShader);
		glAttachShader(newScreenProgram, newFragShader);
		glLinkProgram(newScreenProgram);
		glValidateProgram(newScreenProgram);

		return newScreenProgram;
	}
}

