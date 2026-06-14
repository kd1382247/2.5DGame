#include "SkeletonAttackArc.h"

#include"../../Object/Enemy/Skeleton/Skeleton.h"
#include"../../Mouse/Mouse.h"

void SkeletonAttackArc::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/AttackArc/SkeletonAttackArc/SkeletonAttackArc.gltf");

	m_pos = { 0,0,0 };
	m_angle = {};

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

void SkeletonAttackArc::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void SkeletonAttackArc::Update()
{
	if (m_wpSkeleton.expired() == true||!m_wpSkeleton.lock()->GetAttackFlg())
	{
		m_isExpired = true;
		return;
	}


	if (m_wpSkeleton.lock()->GetCollisionFlg())
	{
		m_collisionFlg = true;
	}
	else
	{
		m_collisionFlg = false;
	}
}

void SkeletonAttackArc::PostUpdate()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}
