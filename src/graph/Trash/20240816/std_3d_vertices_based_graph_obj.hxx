#ifndef STD_3D_VERTICES_BASED_GRAPH_OBJ
#define STD_3D_VERTICES_BASED_GRAPH_OBJ

#include "igraph_obj_itfc.hxx"
//#include "graph_subsys.hxx"
#include "3rdparty_wrapper/opengl.hxx"

namespace Graph {
	/**
	 * 一个「标准」的图形对象：使用顶点、渲染程序、材质来渲染的图形对象。
	 *
	 */
	class Std3DVerticesBasedGraphObj SATISFIES(IGraphObj)
	{
	public:
		//Std3DVerticesBasedGraphObj()
		//Std3DVerticesBasedGraphObj(Std3DVerticesBasedGraphObj&&) = default;
		OpenGL::GLIndividualRes shadersProgram;
		//OpenGL::GLIndividualRes vertexArr;
		gsl::span<GLfloat> vertex;
		size_t offsetInGlobalVbo;
		bool shouldReinitGlobalVBO = false;

		OpenGL::GLIndividualRes texture;

		std::function<void(const Std3DVerticesBasedGraphObj&)> render;

	public:
		void onDraw() override;
		void onReinitGlobalVBO(std::function<size_t(const gsl::span<GLfloat> &vertex)> pushVertex) override;
	};
}

#endif // !STD_3D_VERTICES_BASED_GRAPH_OBJ