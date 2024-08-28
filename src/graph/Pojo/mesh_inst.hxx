#ifndef MESH_INST_HXX
#define MESH_INST_HXX

namespace Graph
{
	struct MeshInst
	{
		StaticObjRef<Mesh> mesh;
		glm::mat4 transform;
	};
}

#endif // MESH_INST_HXX