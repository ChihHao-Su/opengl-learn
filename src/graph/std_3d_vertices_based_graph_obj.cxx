#include "std_3d_vertices_based_graph_obj.hxx"

namespace Graph {
	void Std3DVerticesBasedGraphObj::onDraw()
	{
		/*glUseProgram(shadersProgram);
		GL_BIND_VERT_ARR(vertexArr, BEGIN(
			render();
		));*/
	}

	void Std3DVerticesBasedGraphObj::onReinitGlobalVBO(
			std::function<size_t(const gsl::span<GLfloat> &vertex)> pushVertex
	) {
		this->offsetInGlobalVbo = pushVertex(this->vertex);
	}
};