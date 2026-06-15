#include "MushroomAttackArc.h"

#include"../../Object/Enemy/Mushroom/Mushroom.h"

void MushroomAttackArc::Init()
{

	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/AttackArc/MushroomAttackArc/MushroomAttackArc.gltf");

	m_pos = { 0,0.2,0 };
	m_angle = {};

	m_transMat = Math::Matrix::Identity;
	m_rotationMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"MushroomAttackArcCollision",
		m_model,
		KdCollider::Type::TypeDamage);

	//=======================================
}

void MushroomAttackArc::Update()
{
	if (m_wpMushroom.expired() == true||!m_wpMushroom.lock()->GetAttackAliveFlg()||!m_wpMushroom.lock()->GetAttackFlg())
	{
		m_isExpired = true;
		return;
	}

	if (m_wpMushroom.lock()->GetCollisionFlg())
	{
		m_collisionFlg = true;
	}

	Math::Vector3 mushroomPos = {};

	if (m_wpMushroom.expired() == false)
	{
		mushroomPos = m_wpMushroom.lock()->GetPos();
	}

	m_angle = atan2(mushroomPos.x - m_playerPos.x, mushroomPos.z - m_playerPos.z);

	m_rotationMat = Math::Matrix::CreateRotationY(m_angle);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);

}

void MushroomAttackArc::PostUpdate()
{
	Math::Matrix transMat = Math::Matrix::Identity;
	if (m_wpMushroom.expired() == false)
	{
		transMat = Math::Matrix::CreateTranslation(m_wpMushroom.lock()->GetPos());
	}

	m_mWorld = (m_transMat * m_rotationMat) * transMat;
}

void MushroomAttackArc::DrawUnLit()
{
	if (m_wpMushroom.expired() == false)
	{
		if(!m_wpMushroom.lock()->GetMoveFlg()&&m_wpMushroom.lock()->GetAttackAliveFlg())
		{
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
		}
	}
}
