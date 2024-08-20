#ifndef GRAPH_API_SERV_HXX
#define GRAPH_API_SERV_HXX

#include "../3rdparty_wrapper/opengl.hxx"

namespace Graph::GraphApiServ {
	using namespace Graph::OpenGL;
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