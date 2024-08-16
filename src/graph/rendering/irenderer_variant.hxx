#ifndef RENDERER_VARIANT_HXX
#define RENDERER_VARIANT_HXX
#include "simple_2d_geo_renderer.hxx"

namespace Graph::Rendering {
	DEF_TRAIT_VARIANT(IRenderer, Simple2DGeoRenderer);

	/**
	 * A RendererFacade OWNS a IRenderer.
	 */
	class RendererFacade
	{
	private:
		IRenderer renderer;
	public:
		RendererFacade(IRenderer&& renderer);
		IRenderer& operator ->();
	};
}

#endif // RENDERER_VARIANT_HXX