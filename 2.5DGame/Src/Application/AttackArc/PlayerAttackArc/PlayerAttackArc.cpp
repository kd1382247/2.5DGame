#include "PlayerAttackArc.h"

#include"../../Object/Player/Player.h"
#include"../../Mouse/Mouse.h"

void PlayerAttackArc::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/AttackArc/PlayerAttackArc/PlayerAttackArc.gltf");

	m_pos = {0,0.8,0};
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

void PlayerAttackArc::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, kBlueColor);
}

void PlayerAttackArc::Update()
{
	if (m_wpPlayer.expired() == true)
	{
		m_isExpired = true;
		return;
	}


	Math::Vector3 playerPos = {};

	if (m_wpPlayer.expired() == false)
	{
		playerPos = m_wpPlayer.lock()->GetPos();
	}

	m_angle = atan2(playerPos.x - Mouse::Instance().Get3DMousePos().x, playerPos.z - Mouse::Instance().Get3DMousePos().z);

	m_rotationMat = Math::Matrix::CreateRotationY(m_angle);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);

}

void PlayerAttackArc::PostUpdate()
{

	Math::Matrix transMat = Math::Matrix::Identity;
	if (m_wpPlayer.expired()==false)
	{
		transMat = Math::Matrix::CreateTranslation(m_wpPlayer.lock()->GetPos());
	}

	m_mWorld = (m_transMat*m_rotationMat)*transMat;
}
