#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "3rdparty_wrapper/opengl.hxx"

DECL_SYBSYS(Graph)
{
	extern OpenGL::GLRes mainScreenGlProgram;
	extern OpenGL::GLRes mainScreenFb;
	extern OpenGL::GLRes masterSceneScreenFb;
	extern OpenGL::GLRes slaveSceneScreenFb;
	
	enum class Fb {
		
	};

	DECL_SYBSYS_INIT_FUNC();

	void reloadMainScreenGlProgram();

	std::string getShaderInfoLog(OpenGL::GLRes &shader);
	OpenGL::GLRes compileShader(const std::string &src, const GLenum shaderType);
	OpenGL::GLRes createGlShadersProgram(
		const std::string & vertShaderSrc,
		const std::string & fragShaderSrc
	);
};

#endif
