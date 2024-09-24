#ifndef MESH_HXX
#define MESH_HXX

#include "vertex.hxx"
#include "mesh_inst.hxx"

namespace Graph
{
	using namespace Essentials::Memory;

	struct Mesh
	{
		boost::container::static_vector<Vertex, 19200> vertices;
		boost::container::static_vector<GLuint, 19200> indices;
		std::vector<StaticObjRef<MeshInst>> instances;

		struct GPURuntimeData
		{
            GLfloat *vertDataOffsetInVBO;
            size_t vertDataLen;
            GLuint *indDataOffsetInEBO;
            size_t indDataLen;
		};
		std::optional<GPURuntimeData> gpuRuntimeData;
	};
}

#endif // MESH_HXX
