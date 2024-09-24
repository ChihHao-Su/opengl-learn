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

        void flushAllMeshesToGPU();

        void render() override;

	private:
        static const GLuint maxVert = 165000;
        static const GLuint maxIndices = 100000;

		//Ref<GLResHolder> targetFb;
		//boost::container::static_vector<StaticObjHolder<Mesh>, 1000> meshese;
		boost::container::static_vector<StaticObjRef<Mesh>, 165000> meshes;
		boost::container::static_vector<StaticObjRef<MeshInst>, 165000> meshInsts;

		struct DataToUploadToGPU
		{
            boost::container::static_vector<GLfloat, maxVert> vboContent;
            boost::container::static_vector<GLuint, maxIndices> eboContent;
		} dataToUploadToGPU;
		


		GLResHolder vb;
        int vaIndex;
        GLResHolder va;

		GLResHolder shaderProg;
	};
};

#endif // SIMPLE_2D_GEO_RENDERER_HXX
