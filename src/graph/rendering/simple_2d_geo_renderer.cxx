#include "simple_2d_geo_renderer.hxx"
#include "../Serv/graph_api_serv.hxx"
#include "../Pojo/vertex.hxx"

namespace Graph::Rendering
{
    namespace EssMath = Essentials::Math;
	Simple2DGeoRenderer::Simple2DGeoRenderer()
		:
		//targetFb(targetFb),
		vb(GraphApiServ::createADynVbo(maxVert * sizeof(Vertex))),
        vaIndex(EssMath::randNum(0, 5)),
        va(GraphApiServ::createAVao(vaIndex, 8, GL_FLOAT, false, sizeof(float) * 8, nullptr)),
		shaderProg(GraphApiServ::createGLShadersProgByFile(
			"res/simple_2d_geo_shader.vert",
			"res/simple_2d_geo_shader.frag"
		))
	{

	}

	void Simple2DGeoRenderer::regMesh(StaticObjHolder<Mesh>& mesh) {
		meshes.push_back(mesh);
        // TODO: 寫一箇代表 mesh 的頂點數據 / 頂點索引數據的結構體，直接把每箇
        // mesh 的頂點數據 / 頂點索引數據的結構體放入 Content；而不要獲得 mesh
        // 的頂點數據 / 頂點索引數據中每一箇字段，將其一一放入 Content。

		// 记录 mesh 的顶点数据的起始位置
        GLfloat *meshVertDataBeginOffset = dataToUploadToGPU.vboContent.end().get_ptr();

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
        GLfloat *meshVertDataEndOffset = dataToUploadToGPU.vboContent.end().get_ptr();

        size_t meshVertDataSize = meshVertDataEndOffset - meshVertDataBeginOffset;

        // 記錄 mesh 的頂點索引數據的起始位置
        GLuint *meshIndDataBeginOffset = dataToUploadToGPU.eboContent.end().get_ptr();

        // 把 mesh 頂點索引數據放到 eboContent
        for (auto& i : mesh->indices) {
            dataToUploadToGPU.eboContent.push_back(i);
        }

        // 記錄 mesh 的頂點索引數據結束位置
        GLuint *meshIndDataEndOffset = dataToUploadToGPU.eboContent.end().get_ptr();
        size_t meshIndDataSize = meshIndDataEndOffset - meshIndDataBeginOffset;

        mesh->gpuRuntimeData = {
            .vertDataOffsetInVBO = meshVertDataBeginOffset,
            .vertDataLen = meshVertDataSize,
            .indDataOffsetInEBO = meshIndDataBeginOffset,
            .indDataLen = meshIndDataSize
        };

	}

    void Simple2DGeoRenderer::flushAllMeshesToGPU() {
        // 將所有 Mesh 的頂點數據送入 GPU
        size_t vertDataSize = dataToUploadToGPU.vboContent.size();
        auto vertDataPtr = dataToUploadToGPU.vboContent.begin().get_ptr();
        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertDataSize, vertDataPtr);
    }

    void Simple2DGeoRenderer::render() {
        // 遍歷每箇 Mesh，繪製出其所有的 MeshInstance

	}

}
