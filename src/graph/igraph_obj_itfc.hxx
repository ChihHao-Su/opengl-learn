#ifndef GRAPH_OBJ_ITFC_HXX
#define GRAPH_OBJ_ITFC_HXX

DEF_TRAIT_ITFC(IGraphObj) {
public:
	virtual void onDraw() = 0;
	virtual void onReinitGlobalVBO(std::function<size_t(const gsl::span<GLfloat> &vertex)> pushVertex) = 0;
};

#endif // !GRAPH_OBJ_HXX


