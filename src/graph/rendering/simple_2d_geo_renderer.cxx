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

	void Simple2DGeoRenderer::onFlush() {

	}

}