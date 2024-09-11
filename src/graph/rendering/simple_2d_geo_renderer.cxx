#include "simple_2d_geo_renderer.hxx"
#include "../Serv/graph_api_serv.hxx"
#include "../Pojo/vertex.hxx"

namespace Graph::Rendering
{

	Simple2DGeoRenderer::Simple2DGeoRenderer()
		:
		//targetFb(targetFb),
		vb(GraphApiServ::createADynVbo(maxVert * sizeof(Vertex))),
		shaderProg(GraphApiServ::createGLShadersProgByFile(
			"res/simple_2d_geo_shader.vert",
			"res/simple_2d_geo_shader.frag"
		))
	{

	}

	void Simple2DGeoRenderer::regMesh(StaticObjHolder<Mesh>& mesh) {
		meshes.push_back(mesh);

		// 记录 mesh 的顶点数据的起始位置
		GLfloat *meshBeginOffset = dataToUploadToGPU.vboContent.end().get_ptr();

		// 把 mesh 的顶点数据放到 vboContent
		for (auto& v : mesh->vertices) {
			dataToUploadToGPU.vboContent.push_back(v.pos.x);
			dataToUploadToGPU.vboContent.push_back(v.pos.y);
			dataToUploadToGPU.vboContent.push_back(v.pos.z);
			dataToUploadToGPU.vboContent.push_back(v.colour.r);
			dataToUploadToGPU.vboContent.push_back(v.colour.g);
			dataToUploadToGPU.vboContent.push_back(v.colour.b);
			dataToUploadToGPU.vboContent.push_back(v.uv.x);
			dataToUploadToGPU.vboContent.push_back(v.uv.y);
		}

		

		// 记录 mesh 的顶点数据结束位置
		GLfloat *meshEndOffset = dataToUploadToGPU.vboContent.end().get_ptr();
		
		size_t meshDataSize = meshEndOffset - meshBeginOffset;

		mesh->gpuRuntimeData = { meshBeginOffset, meshDataSize };

	}

	void Simple2DGeoRenderer::flush() {
		
	}

	
}