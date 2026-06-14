#include "EnergyBullet.h"

#include"../../../../Scene/SceneManager.h"

#include"../FlyngEye.h"

void EnergyBullet::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Enemy/FlyngEye/EnergyBullet/1.png");

	m_polygon->SetSplit(10, 1);

	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_pos = {};

	// デバッグ用 : KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"AttackArcCollision",
		{0,0.3,0},
		0.2,
		KdCollider::Type::TypeDamage);

	//=======================================
	
}

void EnergyBullet::Update()
{

	if (m_wpEnemy.expired() == true)
	{
		m_isExpired = true;
		return;
	}

	m_animCnt+=0.2;
	if(m_animCnt>10)
	{
		m_animCnt = 0;
	}


	if (m_wpEnemy.lock()->GetCollisionFlg())
	{
		m_collisionFlg = true;
	}


	m_polygon->SetUVRect((int)m_animCnt);


	Math::Vector3 dir = m_playerPos - m_enemyPos;

	dir.Normalize();

	m_pos += dir * m_speed;

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

}

void EnergyBullet::PostUpdate()
{
	
}

void EnergyBullet::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void EnergyBullet::OnHit()
{
	m_isExpired = true;
}
