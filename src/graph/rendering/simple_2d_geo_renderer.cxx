#include "simple_2d_geo_renderer.hxx"
#include "../Serv/graph_api_serv.hxx"
namespace Graph::Rendering {

	Simple2DGeoRenderer::Simple2DGeoRenderer(Ref<GLResHolder> targetFb)
		:
		targetFb(targetFb),
		vb([] {
			GLIndividualRes res = makeVertexArray();
			glGenBuffers(1, &res);
			return res;
		}()),
		shaderProg(GraphApiServ::createGLShadersProgByFile(
			"",
			""
		))
	{

	}

	void Simple2DGeoRenderer::onFlush() {

	}

}