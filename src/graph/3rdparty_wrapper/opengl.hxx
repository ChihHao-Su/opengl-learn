#ifndef OPENGL_HXX
#define OPENGL_HXX

#define GL_BIND_ARR_BUFFER(buffer, actions) \
	glBindBuffer(GL_ARRAY_BUFFER, buffer); \
	actions \
	glBindBuffer(GL_ARRAY_BUFFER, 0)

#define GL_BIND_VERT_ARR(vertArr, actions) \
	glBindVertexArray(vertArr); \
	actions \
	glBindVertexArray(0)

#define GL_BIND_FRAME_BUFFER(buffer, actions) \
	glBindFramebuffer(GL_FRAMEBUFFER, buffer); \
	actions \
	glBindFramebuffer(GL_FRAMEBUFFER, 0)

#define GL_BIND_TEXTURE(textureType, texture, actions) \
	glBindTexture(textureType, texture); \
	actions; \
	glBindTexture(textureType, 0)

#define GL_BIND_RENDER_BUFFER(buffer, actions) \
	glBindRenderbuffer(GL_RENDERBUFFER, buffer); \
	actions \
	glBindRenderbuffer(GL_RENDERBUFFER, 0)

#define BEGIN(...) __VA_ARGS__

/**
 * Poor encapsulation to OpenGL resources.
 */
namespace OpenGL {
	using GLFWWindowBox = Box<GLFWwindow, std::function<void(GLFWwindow*)>>;

	class GLRes {
	private:
		GLuint data;
		std::function<void(GLuint)> deleter;
	public:
	GLRes();
		GLRes(GLuint &data, std::function<void(GLuint)> deleter);
	GLRes(GLRes&& other);
		operator GLuint();
		GLuint* operator &();
	GLRes& operator =(const GLRes& other) = delete;
	GLRes& operator =(GLRes&& other);
		~GLRes();
	};

	GLRes makeShader(GLuint shader = 0);

	GLRes makeBuffer(GLuint buffer = 0);

	GLRes makeTexture(GLuint texture = 0);

	GLRes makeRenderBuffer(GLuint renderBuffer = 0);

	GLRes makeFrameBuffer(GLuint frameBuffer = 0);

	GLRes makeProgram(GLuint program = 0);

	GLRes makeVertexArray(GLuint vertexArray = 0);

	extern const char* glsl_version;

	GLFWWindowBox createGLWindow();

	void clearErrs();

}

#endif // !OPENGL_HXX
