#include "graph_api_serv.hxx"
#include "../Excp/shader_compile_failed_excp.hxx"

namespace Graph::GraphApiServ
{
    GLIndividualRes createADynVbo(GLuint size) {
		auto vbo = makeBuffer();
		glGenBuffers(1, &vbo);
		/* GL_BIND_ARR_BUFFER(vbo, BEGIN()); */
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		return vbo;
	}

    GLIndividualRes createAVao(GLuint index, GLint size, GLenum type, GLboolean isNormalized, GLsizei stride, const GLvoid *pointer) {
        auto vao = makeVertexArray();
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(index, size, type, isNormalized, stride, pointer);
    }

    std::string getShaderInfoLog(GLResView shader) {
		GLint totalLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &totalLength);
		std::string logs;
		logs.resize(totalLength);
		glGetShaderInfoLog(shader, totalLength, NULL, &logs[0]);

		// 移除末尾的 \n\0
		logs.pop_back();
		logs.pop_back();

		std::shared_ptr<std::string> a{ new std::string() };
		
		return logs;
	}

    GLIndividualRes createShader(const std::string& src, const GLenum shaderType) {
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

    GLIndividualRes createGLShadersProg(const std::string& vertShaderSrc, const std::string& fragShaderSrc) {
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

    GLIndividualRes createGLShadersProgByFile(const std::filesystem::path vertShaderSrcFile, const std::filesystem::path fragShaderSrcFile) {
		return createGLShadersProg(
			Essentials::File::read(vertShaderSrcFile),
			Essentials::File::read(fragShaderSrcFile)
		);
	}
}

