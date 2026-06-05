#include "Ground.h"

void Ground::Init()
{
	// ●モデル読込
	// ポインタのままでは使えないので、実体化
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Ground.gltf");

	//========== 当てられる側の処理==========

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"GroundCollision",
		m_model,
		KdCollider::TypeGround);

	//=======================================

	m_mWorld = Math::Matrix::CreateTranslation(0, 0, -5);

}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
