#ifndef SIMPLE_2D_GEO_RENDERER_HXX
#define SIMPLE_2D_GEO_RENDERER_HXX
#include "irenderer_itfc.hxx"

namespace Graph::Rendering {
	using namespace OpenGL;
	class Simple2DGeoRenderer SATISFIES(IRenderer) {
	public:
		Simple2DGeoRenderer();

		void onFlush() override;

	private:
		//Ref<GLResHolder> targetFb;
	
		
		const GLuint maxQuads = 100;
		const GLuint maxVert = maxQuads * 4;
		const GLuint maxIndices = maxVert * 6;

		GLResHolder vb;

		GLResHolder shaderProg;
	};
};

#endif // SIMPLE_2D_GEO_RENDERER_HXX