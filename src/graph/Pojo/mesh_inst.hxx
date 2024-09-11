#ifndef MESH_INST_HXX
#define MESH_INST_HXX

<<<<<<< HEAD


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
=======
namespace Graph
{
	struct MeshInst
	{
		StaticObjRef<Mesh> mesh;
		glm::mat4 transform;
>>>>>>> master
	};
}

#endif // MESH_INST_HXX