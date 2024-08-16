#ifndef RENDERER_ITFC_HXX
#define RENDERER_ITFC_HXX
#include "../3rdparty_wrapper/opengl.hxx"

namespace Graph::Rendering {
	using namespace OpenGL;

	DEF_TRAIT_ITFC(IRenderer) {
		virtual void onFlush() = 0;
	};
}

#endif // RENDERER_ITFC_HXX