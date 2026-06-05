#include "Wall.h"

void Wall::Init()
{

	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Wall/Wall.gltf");

	//========== 当てられる側の処理==========

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"WallCollision",  // 当たり判定の識別名
		m_model,
		KdCollider::TypeGround);

	//=======================================
}

void Wall::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);
}

void Wall::Release()
{}
