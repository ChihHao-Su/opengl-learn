#include "graph_api_serv.hxx"
#include "../Excp/shader_compile_failed_excp.hxx"

namespace Graph::GraphApiServ {
	std::string getShaderInfoLog(GLResView shader)
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

	GLIndividualRes createShader(const std::string& src, const GLenum shaderType)
	{
		auto shader = OpenGL::makeShader(glCreateShader(shaderType));
		UNSAFE_PRONE(
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

	GLIndividualRes createGLShadersProg(const std::string& vertShaderSrc, const std::string& fragShaderSrc)
	{
		GLIndividualRes newVertexShader;
		GLIndividualRes newFragShader;

		newVertexShader = createShader(vertShaderSrc, GL_VERTEX_SHADER);
		newFragShader = createShader(fragShaderSrc, GL_FRAGMENT_SHADER);

		auto newScreenProgram = makeProgram(glCreateProgram());
		glAttachShader(newScreenProgram, newVertexShader);
		glAttachShader(newScreenProgram, newFragShader);
		glLinkProgram(newScreenProgram);
		glValidateProgram(newScreenProgram);

		return newScreenProgram;
	}

	GLIndividualRes createGLShadersProgByFile(const std::filesystem::path vertShaderSrcFile, const std::filesystem::path fragShaderSrcFile)
	{
		return createGLShadersProg(
			Essentials::File::read(vertShaderSrcFile),
			Essentials::File::read(fragShaderSrcFile)
		);
	}
}

