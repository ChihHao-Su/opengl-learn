#include "irenderer_variant.hxx"

namespace Graph::Rendering {
	RendererFacade::RendererFacade(IRenderer&& renderer)
		: renderer(std::move(renderer)) { }

	IRenderer& RendererFacade::operator->()
	{
		return renderer;
	}
}