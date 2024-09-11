#ifndef MESH_INST_HXX
#define MESH_INST_HXX



namespace Graph
{
	using namespace Essentials::Memory;

	class MeshInst
	{
	public:
		StaticObjRef<struct Mesh> mesh;
		glm::mat3 transform;

		static StaticObjHolder<MeshInst> create(StaticObjRef<Mesh> &mesh, glm::mat3 transform);
		~MeshInst();
	};
}

#endif // MESH_INST_HXX