#include "simple_2d_geo_renderer.hxx"
#include "../Serv/graph_api_serv.hxx"
#include "../Pojo/vertex.hxx"

namespace Graph::Rendering {

	Simple2DGeoRenderer::Simple2DGeoRenderer()
		:
		//targetFb(targetFb),
		vb(GraphApiServ::createADynVbo(maxVert * sizeof(Vertex))),
		shaderProg(GraphApiServ::createGLShadersProgByFile(
			"res/simple_2d_geo_shader.vert",
			"res/simple_2d_geo_shader.frag"
		))
	{

	}

	void Simple2DGeoRenderer::regMesh(StaticObjHolder<Mesh>& mesh) {
		meshes.push_back(mesh);

		// 把 mesh 的顶点数据放到 vboContent
		GLuint curren
	}

	void Simple2DGeoRenderer::flush() {
		
	}
}