#ifndef GRAPH_OBJ_HXX
#define GRAPH_OBJ_HXX

DEF_TRAIT_ITFC(IGraphObj) {
public:
	virtual void draw() = 0;
};

// Carefully: This may make a bunch of compiler errors. Make
// sure classes after the 1st argument implement IGraphObj correctly.
DEF_TRAIT_VARIANT(IGraphObj, class Std3DVerticesBasedGraphObj);



#endif // !GRAPH_OBJ_HXX


