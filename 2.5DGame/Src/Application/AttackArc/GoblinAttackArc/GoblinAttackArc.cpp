#include "GoblinAttackArc.h"

#include"../../Object/Enemy/Goblin/Goblin.h"
#include"../../Mouse/Mouse.h"

void GoblinAttackArc::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/AttackArc/GoblinAttackArc/GoblinAttackArc.gltf");

	m_pos = { 0,0.2,0 };
	m_angle = {};

	m_transMat = Math::Matrix::Identity;
	m_rotationMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;


	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"AttackArcCollision",
		m_model,
		KdCollider::Type::TypeDamage);

	//=======================================

}

void GoblinAttackArc::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, kRedColor);
}

void GoblinAttackArc::Update()
{
	if (m_wpGoblin.expired() == true||!m_wpGoblin.lock()->GetAttackFlg())
	{
		m_isExpired = true;
		return;
	}

	Math::Vector3 goblinPos = {};

	if (m_wpGoblin.expired() == false)
	{
		goblinPos = m_wpGoblin.lock()->GetPos();
	}

	m_angle = atan2(goblinPos.x - m_playerPos.x, goblinPos.z - m_playerPos.z);

	m_rotationMat = Math::Matrix::CreateRotationY(m_angle);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);

}

void GoblinAttackArc::PostUpdate()
{

	Math::Matrix transMat = Math::Matrix::Identity;
	if (m_wpGoblin.expired() == false)
	{
		transMat = Math::Matrix::CreateTranslation(m_wpGoblin.lock()->GetPos());
	}

	m_mWorld = (m_transMat * m_rotationMat) * transMat;
}
