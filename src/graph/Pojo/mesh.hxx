#include "vertex.hxx"
#ifndef MESH_HXX
#define MESH_HXX

namespace Graph {
	struct Mesh
	{
		boost::container::static_vector<Vertex, 1920000> vert;
		boost::container::static_vector<GLuint, 1920000> indices;
	};
}

#endif // MESH_HXX