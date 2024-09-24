#ifndef GRAPH_API_SERV_HXX
#define GRAPH_API_SERV_HXX

#include "../3rdparty_wrapper/opengl.hxx"

namespace Graph::GraphApiServ {
	using namespace Graph::OpenGL;

	GLIndividualRes createADynVbo(GLuint size);

    GLIndividualRes createAVao(GLuint index, GLint size, GLenum type, GLboolean isNormalized, GLsizei stride, const GLvoid *pointer);

	std::string getShaderInfoLog(GLResView shader);

	GLIndividualRes createShader(const std::string& src, const GLenum shaderType);

	GLIndividualRes createGLShadersProg(
		const std::string& vertShaderSrc,
		const std::string& fragShaderSrc
	);

	GLIndividualRes createGLShadersProgByFile(
		const std::filesystem::path vertShaderSrcFile,
		const std::filesystem::path fragShaderSrcFile
	);
}

#endif
