#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "igraph_obj_variant.hxx"
#include "3rdparty_wrapper/opengl.hxx"

DECL_SYBSYS(Graph)
{
	// extern OpenGL::GLIndividualRes mainScreenGlProgram;
	// extern OpenGL::GLIndividualRes mainScreenFb;
	// extern OpenGL::GLIndividualRes masterSceneScreenFb;
	// extern OpenGL::GLIndividualRes slaveSceneScreenFb;
	// extern float masterAndSlaveScnFbBlend;

	//extern std::vector<Graph::IGraphObj> masterSceneGraphObjs;
	//extern std::vector<Graph::IGraphObj> slaveSceneGraphObjs;

	DECL_SUBSYS_INTERNAL
	{
		extern std::vector<Graph::IGraphObj> masterSceneGraphObjs;
		extern std::vector<Graph::IGraphObj> slaveSceneGraphObjs;
		void reinitGlobalVBOandVAO();
	}

	extern OpenGL::GLIndividualRes globalVBO;
	
	enum class Scene {
		MASTER_SCN,
		SLAVE_SCN
	};


	DECL_SYBSYS_INIT_FUNC();

	void reloadScreenGlProgram();
	void masterizeSlave();
	void onFrame();
	//void addGraphObjToMasterScene(Graph::IGraphObj &go);
	//void addGraphObjToSlaveScene(Graph::IGraphObj &go);

	template <typename... Args>
	concept CanConstructIGraphObjWithArgs = std::constructible_from<Graph::IGraphObj, Args...>;

	template< class... Args >
	auto& emplaceGraphObjToMasterScene(Args&&... args)
			requires CanConstructIGraphObjWithArgs<Args...>
	{
		auto& vecEleRef = SUBSYS_INTERNAL::masterSceneGraphObjs.emplace_back(
			std::forward<Args>(args)...
		);
		SUBSYS_INTERNAL::reinitGlobalVBOandVAO();
		return vecEleRef;
	}

	template< class... Args >
	auto& emplaceGraphObjToSlaveScene(Args&&... args)
			requires CanConstructIGraphObjWithArgs<Args...> 
	{
		auto &vecEleRef = SUBSYS_INTERNAL::slaveSceneGraphObjs.emplace_back(
			std::forward<Args>(args)...
		);
		SUBSYS_INTERNAL::reinitGlobalVBOandVAO();
		return vecEleRef;
	}


	std::string getShaderInfoLog(OpenGL::GLIndividualRes &shader);
	OpenGL::GLIndividualRes compileShader(const std::string &src, const GLenum shaderType);
	OpenGL::GLIndividualRes createGlShadersProgram(
		const std::string & vertShaderSrc,
		const std::string & fragShaderSrc
	);
};

#endif

