#include "graph_subsys.hxx"
#include "Excp/shader_compile_failed_excp.hxx"
#include "Excp/vertex_format_error_excp.hxx"

using namespace std;
using namespace Essentials;

IMPL_SYBSYS(Graph)
{


	IMPL_SUBSYS_INTERNAL
	{
		OpenGL::GLIndividualRes screenPlaneVA;

		OpenGL::GLIndividualRes screenPlaneProgram;
		OpenGL::GLIndividualRes screenPlaneFb;
		OpenGL::GLIndividualRes screenPlaneTexture;
		OpenGL::GLIndividualRes masterSceneScreenFb;
		OpenGL::GLIndividualRes masterSceneScreenTexture;
		OpenGL::GLIndividualRes slaveSceneScreenFb;
		OpenGL::GLIndividualRes slaveSceneScreenTexture;
		float masterAndSlaveScnFbBlend = 0.0f;

		std::vector<Graph::IGraphObj> masterSceneGraphObjs;
		std::vector<Graph::IGraphObj> slaveSceneGraphObjs;

		OpenGL::GLIndividualRes createScreenPlaneGPUProgram() {
			return createGlShadersProgram(
				File::read("res/screen_shader.vert"),
				File::read("res/screen_shader.frag")
			);
		}

		void createScreenVertex() {
			static GLfloat vertexs[] = {
				// Coords     // texCoords
				1.0f, -1.0f,  1.0f, 0.0f,
			   -1.0f, -1.0f,  0.0f, 0.0f,
			   -1.0f,  1.0f,  0.0f, 1.0f,

				1.0f,  1.0f,  1.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
			   -1.0f,  1.0f,  0.0f, 1.0f
		   };

		   
		   auto screenVertexBuffer = OpenGL::makeBuffer();
		   glGenBuffers(1, &screenVertexBuffer);
		   auto screenVertexArray = OpenGL::makeVertexArray();
		   glGenVertexArrays(1, &screenVertexArray);
		   GL_BIND_VERT_ARR(screenVertexArray, BEGIN(
			   GL_BIND_ARR_BUFFER(screenVertexBuffer, BEGIN(
				   glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
				   glEnableVertexAttribArray(0);
				   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
				   glEnableVertexAttribArray(1);
				   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<void*>(2 * sizeof(GLfloat)));
			   ));
		   ));

		   SUBSYS_INTERNAL::screenPlaneVA = std::move(screenVertexArray);
		}


		void reinitGlobalVBOandVAO() {
			std::vector<GLfloat> globalVBOVertexs;

			auto pushVertex = [&](const gsl::span<GLfloat>& vertex) {
				if (vertex.size() % 4 != 0)
					throw VertexFormatErrorExcp{ 
						std::format("%s 没法被 4 整除！顶点矩阵必须是 4 列的！", vertex.size())
					};

				size_t vetMatRowCount = vertex.size() / 4;
				size_t globalVBOVertexSizeBeforeAddVertex = globalVBOVertexs.size();

				globalVBOVertexs.append_range(vertex);
				return globalVBOVertexSizeBeforeAddVertex;
			};

			for (auto& mgo : SUBSYS_INTERNAL::masterSceneGraphObjs) {
				std::visit([&](auto& laGraphObj) {
					laGraphObj.onReinitGlobalVBO(pushVertex);
				}, mgo);
			}
		}


	};

	IMPL_SYBSYS_INIT_FUNC() {
		reloadScreenGlProgram();
		SUBSYS_INTERNAL::createScreenVertex();

		// Init screen plane, master scene screen, slave scene frame buffers.


		//glGenFramebuffers(3, )

	}

	void onFrame() {
		GL_BIND_FRAME_BUFFER(SUBSYS_INTERNAL::masterSceneScreenFb, BEGIN(
			for (auto& graphObj : SUBSYS_INTERNAL::masterSceneGraphObjs) {
				std::visit([](auto& laGraphObj) {
					laGraphObj.onDraw();
				}, graphObj);
			}
		));

		GL_BIND_FRAME_BUFFER(SUBSYS_INTERNAL::slaveSceneScreenFb, BEGIN(
			for (auto& graphObj : SUBSYS_INTERNAL::slaveSceneGraphObjs) {
				std::visit([](auto& laGraphObj) {
					laGraphObj.onDraw();
				}, graphObj);
			}
		));

		GL_BIND_FRAME_BUFFER(SUBSYS_INTERNAL::screenPlaneProgram, BEGIN(
			GL_BIND_TEXTURE(GL_TEXTURE_2D, SUBSYS_INTERNAL::masterSceneScreenTexture, BEGIN(
				glDrawArrays(GL_TRIANGLES, 0, 6);
			));
		));


		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(SUBSYS_INTERNAL::screenPlaneProgram);
		GL_BIND_VERT_ARR(SUBSYS_INTERNAL::screenPlaneVA, BEGIN(
			GL_BIND_TEXTURE(GL_TEXTURE_2D, SUBSYS_INTERNAL::screenPlaneTexture, BEGIN(
				glDrawArrays(GL_TRIANGLES, 0, 6);
			));
		));
	}

	/*void addGraphObjToMasterScene(Graph::IGraphObj&& go) {
		SUBSYS_INTERNAL::masterSceneGraphObjs.push_back(std::move(go));
		SUBSYS_INTERNAL::reinitGlobalVBOandVAO();
	}
	void addGraphObjToSlaveScene(Graph::IGraphObj&& go) {
		SUBSYS_INTERNAL::slaveSceneGraphObjs.push_back(std::move(go));
		SUBSYS_INTERNAL::reinitGlobalVBOandVAO();
	}*/

	void masterizeSlave() {
		std::swap(SUBSYS_INTERNAL::masterSceneScreenFb, SUBSYS_INTERNAL::slaveSceneScreenFb);
		std::swap(SUBSYS_INTERNAL::masterSceneScreenTexture, SUBSYS_INTERNAL::slaveSceneScreenTexture);
		SUBSYS_INTERNAL::masterSceneGraphObjs.swap(SUBSYS_INTERNAL::slaveSceneGraphObjs);
	}

	void reloadScreenGlProgram() {
		SUBSYS_INTERNAL::screenPlaneProgram = SUBSYS_INTERNAL::createScreenPlaneGPUProgram();
	}

	OpenGL::GLIndividualRes createGlShadersProgram(
			const std::string &vertShaderSrc,
			const std::string &fragShaderSrc
	) {
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

	string getShaderInfoLog(OpenGL::GLIndividualRes &shader) {
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


	OpenGL::GLIndividualRes compileShader(const std::string &src, const GLenum shaderType) {
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