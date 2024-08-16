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
namespace Graph::OpenGL {
	using GLFWWindowBox = Box<GLFWwindow, std::function<void(GLFWwindow*)>>;

	extern const char* glsl_version;

	GLFWWindowBox createGLWindow();

	void clearErrs();

	class GLIndividualRes {
	private:
		GLuint data;
		std::function<void(GLuint)> deleter;
	public:
		GLIndividualRes();
		GLIndividualRes(GLuint &data, std::function<void(GLuint)> deleter);
		GLIndividualRes(GLIndividualRes&& other) = default;
		operator GLuint();
		GLuint* operator &();
		friend void swap(GLIndividualRes &lhs, GLIndividualRes &rhs);
		GLIndividualRes& operator =(const GLIndividualRes& other) = delete;
		GLIndividualRes& operator =(GLIndividualRes&& other) noexcept;
		~GLIndividualRes();
	};

	GLIndividualRes makeShader(GLuint shader = 0);

	GLIndividualRes makeBuffer(GLuint buffer = 0);

	GLIndividualRes makeTexture(GLuint texture = 0);

	GLIndividualRes makeRenderBuffer(GLuint renderBuffer = 0);

	GLIndividualRes makeFrameBuffer(GLuint frameBuffer = 0);

	GLIndividualRes makeProgram(GLuint program = 0);

	GLIndividualRes makeVertexArray(GLuint vertexArray = 0);

	


	template <std::size_t Nres>
	class GLArrRes {
	private:
		std::array<GLuint, Nres> data;
		std::function<void(std::array<GLuint, Nres> &)> deleter;
		bool initialized = false;

	public:
		// Constructor
		GLArrRes() = default;

		GLArrRes(
			const std::array<GLuint, Nres>& initData,
			std::function<void(std::array<GLuint, Nres>&)> deleter
		)
			: data(initData), deleter(deleter), initialized(true) {}

		// Move constructor
		GLArrRes(GLArrRes&& other) noexcept
			: data(std::move(other.data)), deleter(other.deleter), initialized(other.initialized) {
			other.initialized = false;
		}

		// Move assignment
		GLArrRes& operator=(GLArrRes&& other) noexcept {
			if (this == &other) 
				return *this;
			if (initialized) {
				deleter(data);
			}
			data = std::move(other.data);
			deleter = other.deleter;
			initialized = other.initialized;
			other.initialized = false;
		}

		// Deleted copy constructor and copy assignment operator
		GLArrRes(const GLArrRes&) = delete;
		GLArrRes& operator=(const GLArrRes&) = delete;

		// Destructor
		~GLArrRes() {
			if (initialized) {
				deleter(data);
			}
		}

		// Accessor for resources
		const std::array<GLuint, Nres>& getResources() const {
			return data;
		}

		// Accessor for a specific resource
		GLuint getResource(std::size_t index) const override {
			return data.at(index);
		}
	};


	class GLResHolder
	{
	private:
		std::move_only_function<GLuint()> getGLRawRes;
	public:
		template<std::size_t Nres>
		GLResHolder(Ref<GLArrRes<Nres>> arrRes, size_t index)
			: getGLRawRes([arrRes, index]() { return arrRes->getResource(index); })
		{ }

		GLResHolder(GLIndividualRes&& res);

		GLResHolder(const GLResHolder&) = delete;
		GLResHolder(GLResHolder&&) = default;

		operator GLuint();

	};

	
}

#endif // !OPENGL_HXX
