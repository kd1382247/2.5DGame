#include "FlyngEye.h"

#include"../../Player/Player.h"

void FlyingEye::Init()
{
	BaseEnemy::Init();

	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Enemy/FlyngEye/FlyngEye.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon->SetSplit(8, 4);

	m_polygon->SetScale(5);

	m_pos = { 5,0,5 };

	m_radius = 1;
}

void FlyingEye::Update()
{
	UpdateEnemyState();

	m_playerPos = {};
	if (m_wpPlayer.expired() == false)
	{
		std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
		m_playerPos = spPlayer->GetPos();
	}

	if(!m_attackFlg)
	{
		//Move(m_playerPos, m_pos, m_speed);

		FlipEnemy(m_playerPos, m_pos, m_scale);
	}

	Attack(m_pos, m_playerPos, m_radius, m_playerRadius, m_eEnemyState, m_attackFlg);

}

void FlyingEye::PostUpdate()
{

	RayCollition(m_pos, m_gravity, 0, 0.2, KdCollider::TypeGround);

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale({ m_scale,1.0f,1.0f });

	m_mWorld = m_scaleMat * m_transMat;
}

void FlyingEye::UpdateEnemyState()
{
	switch (m_eEnemyState)
	{
	case BaseEnemy::EnemyState::IDLE:
		m_polygon->SetUVRect(m_idle[(int)PlayAnim(0.2, 7, m_animCnt, m_eEnemyState, m_attackFlg)]);
		break;
	case BaseEnemy::EnemyState::HIT:
		m_polygon->SetUVRect(m_hit[(int)PlayAnim(0.2, 3, m_animCnt, m_eEnemyState, m_attackFlg)]);
		break;
	case BaseEnemy::EnemyState::DEATH:
		m_polygon->SetUVRect(m_death[(int)PlayAnim(0.2, 3, m_animCnt, m_eEnemyState, m_attackFlg)]);
		break;
	case BaseEnemy::EnemyState::ATTACK:
		m_polygon->SetUVRect(m_attack[(int)PlayAnim(0.1, 4, m_animCnt, m_eEnemyState, m_attackFlg)]);
		break;
	}

}

void FlyingEye::Release()
{

}
