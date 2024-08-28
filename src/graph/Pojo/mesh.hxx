#include "vertex.hxx"
#ifndef MESH_HXX
#define MESH_HXX

namespace Graph {
	struct Mesh
	{
		boost::container::static_vector<Vertex, 19200> vertices;
		boost::container::static_vector<GLuint, 19200> indices;

		struct GPURuntimeData
		{
			GLuint offsetInVBO;
			GLuint lengthInVBO;
		};
		std::optional<GPURuntimeData> gpuRuntimeData;
	};
}

#endif // MESH_HXX