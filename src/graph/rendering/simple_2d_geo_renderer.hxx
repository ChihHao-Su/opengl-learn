#ifndef SIMPLE_2D_GEO_RENDERER_HXX
#define SIMPLE_2D_GEO_RENDERER_HXX
#include "irenderer_itfc.hxx"
#include "../Pojo/mesh.hxx"
#include "../Pojo/mesh_inst.hxx"


namespace Graph::Rendering {
	using namespace OpenGL;
	using namespace Essentials::Memory;

	class Simple2DGeoRenderer SATISFIES(IRenderer) {
	public:
		Simple2DGeoRenderer();

		void regMesh(StaticObjHolder<Mesh> &mesh);

		void flush() override;

	private:
		//Ref<GLResHolder> targetFb;

		//boost::container::static_vector<StaticObjHolder<Mesh>, 1000> meshese;
		boost::container::static_vector<StaticObjRef<Mesh>, 165000> meshes;
		boost::container::static_vector<StaticObjRef<MeshInst>, 165000> meshInsts;

		struct DataToUploadToGPU
		{
			boost::container::static_vector<GLfloat, 165000> vboContent;
		} dataToUploadToGPU;
		
		const GLuint maxQuads = 100;
		const GLuint maxVert = maxQuads * 4;
		const GLuint maxIndices = maxVert * 6;

		GLResHolder vb;

		GLResHolder shaderProg;
	};
};

#endif // SIMPLE_2D_GEO_RENDERER_HXX