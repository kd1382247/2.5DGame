#include "Tree.h"

void Tree::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Tree/Tree.gltf");
}

void Tree::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);
}
