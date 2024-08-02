#include "std_3d_vertices_based_graph_obj.hxx"


void Std3DVerticesBasedGraphObj::draw()
{
	glUseProgram(shadersProgram);
	GL_BIND_VERT_ARR(vertexArrProvider(), BEGIN(
		GL_BIND_TEXTURE(GL_TEXTURE_2D, textureProvider(), BEGIN(
			render();
		));
	));
}
