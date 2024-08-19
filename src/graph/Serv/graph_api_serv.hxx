#ifndef GRAPH_API_SERV_HXX
#define GRAPH_API_SERV_HXX

#include "../3rdparty_wrapper/opengl.hxx"

namespace Graph::GraphApiServ {
	std::string getShaderInfoLog(OpenGL::GLIndividualRes& shader);
	void compileShader(const std::string& src, const GLenum shaderType);
	OpenGL::GLIndividualRes createGlShadersProgram(
		const std::string& vertShaderSrc,
		const std::string& fragShaderSrc
	);
}

#endif