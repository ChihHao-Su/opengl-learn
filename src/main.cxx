using namespace std;
using namespace Essentials;

#include "graph/std_3d_vertices_based_graph_obj.hxx"
#include "graph/graph_subsys.hxx"

int main() {
	INIT_SUBSYS(Graph);


	SUBSYS(Graph)::emplaceGraphObjToMasterScene(
		std::in_place_type<Graph::Std3DVerticesBasedGraphObj>
	);
}