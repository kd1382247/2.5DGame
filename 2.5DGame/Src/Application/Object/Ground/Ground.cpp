#include "Ground.h"

void Ground::Init()
{
	// ●モデル読込
	// ポインタのままでは使えないので、実体化
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Terrain/Terrain.gltf");

}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);
}
