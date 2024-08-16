#ifndef IGRAPH_OBJ_VARIANT_HPP
#define IGRAPH_OBJ_VARIANT_HPP

#include "std_3d_vertices_based_graph_obj.hxx"

// Carefully: This may make a bunch of compiler errors. Make
// sure classes after the 1st argument implement IGraphObj correctly.
namespace Graph {
	DEF_TRAIT_VARIANT(IGraphObj,
		Std3DVerticesBasedGraphObj
	);
}

#endif