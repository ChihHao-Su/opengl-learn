#ifndef SIMPLE_2D_GEO_RENDERER_HXX
#define SIMPLE_2D_GEO_RENDERER_HXX
#include "irenderer_itfc.hxx"

namespace Graph::Rendering {
	using namespace OpenGL;
	class Simple2DGeoRenderer SATISFIES(IRenderer) {
	public:
		Simple2DGeoRenderer(Ref<∃GLResHolder> targetFb);

		void onFlush() override;

	private:
		Ref<∃GLResHolder> targetFb;
		∃GLResHolder vb;
		∃GLResHolder vShader;
		∃GLResHolder fShader;
	};
};

#endif // SIMPLE_2D_GEO_RENDERER_HXX