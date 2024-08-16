#include "simple_2d_geo_renderer.hxx"
namespace Graph::Rendering {
	Simple2DGeoRenderer::Simple2DGeoRenderer(Ref<GLResHolder> targetFb)
		:
		targetFb(targetFb),
		vb([] {
			GLIndividualRes res = makeVertexArray();
			glGenBuffers(1, &res);
			return res;
		}()),
		vShader(makeShader(glCreateShader(GL_VERTEX_SHADER))),
	
	{

	}

	void Simple2DGeoRenderer::onFlush() {

	}

}