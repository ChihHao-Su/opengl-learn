#include "mesh_inst.hxx"
#include "mesh.hxx"


namespace Graph
{
	StaticObjHolder<MeshInst> MeshInst::create(StaticObjRef<Mesh>& mesh, glm::mat3 transform)
	{
		StaticObjHolder meshInst{MeshInst{mesh, transform} };
		mesh->instances.push_back(meshInst);
		meshInst->mesh = mesh;
		return meshInst;
	}

	MeshInst::~MeshInst() {
		std::remove(mesh->instances.begin(), mesh->instances.end(), *this);
	}

}
