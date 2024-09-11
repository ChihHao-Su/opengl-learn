<<<<<<< HEAD
#ifndef MESH_HXX
#define MESH_HXX

#include "vertex.hxx"
#include "mesh_inst.hxx"

namespace Graph
{
	using namespace Essentials::Memory;

=======
#include "vertex.hxx"
#ifndef MESH_HXX
#define MESH_HXX

namespace Graph {
>>>>>>> master
	struct Mesh
	{
		boost::container::static_vector<Vertex, 19200> vertices;
		boost::container::static_vector<GLuint, 19200> indices;
<<<<<<< HEAD
		std::vector<StaticObjRef<MeshInst>> instances;

		struct GPURuntimeData
		{
			GLfloat *offsetInVBO;
			size_t lengthInVBO;
=======

		struct GPURuntimeData
		{
			GLuint offsetInVBO;
			GLuint lengthInVBO;
>>>>>>> master
		};
		std::optional<GPURuntimeData> gpuRuntimeData;
	};
}

#endif // MESH_HXX