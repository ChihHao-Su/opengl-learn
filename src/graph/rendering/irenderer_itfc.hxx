#ifndef RENDERER_ITFC_HXX
#define RENDERER_ITFC_HXX
#include "../3rdparty_wrapper/opengl.hxx"

namespace Graph::Rendering {
	using namespace OpenGL;

	DEF_TRAIT_ITFC(IRenderer) {
<<<<<<< HEAD
		virtual void flush() = 0;
=======
		virtual void onFlush() = 0;
>>>>>>> master
	};
}

#endif // RENDERER_ITFC_HXX