#ifndef STD_3D_VERTICES_BASED_GRAPH_OBJ
#define STD_3D_VERTICES_BASED_GRAPH_OBJ

#include "igraph_obj.hxx"
#include "3rdparty_wrapper/opengl.hxx"

namespace Graph {
	/**
	 * 一个「标准」的图形对象：使用顶点、渲染程序、材质来渲染的图形对象。
	 *
	 */
	class Std3DVerticesBasedGraphObj SATISFIES(IGraphObj)
	{
	private:
		OpenGL::GLRes shadersProgram;
		OpenGL::GLRes vertexArr;
		OpenGL::GLRes texture;
		 targetFb;
		std::function<void()> render;
	public:

		void draw() override;
	};
}

#endif // !STD_3D_VERTICES_BASED_GRAPH_OBJ