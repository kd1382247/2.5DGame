#include "Skeleton.h"

#include"../../Player/Player.h"
#include"../MoveArc/MoveArc.h"

void Skeleton::Init()
{
	BaseEnemy::Init();

	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Enemy/Skeleton/Skeleton.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon->SetSplit(8, 5);

	m_polygon->SetScale(6);

	m_pos = { 5,0,0 };


	// 移動方向の矢印
	m_spMoveArc = std::make_shared<MoveArc>();
	m_spMoveArc->SetPos({ 0,0.5,-0.2 });
}

void Skeleton::DrawUnLit()
{
	m_spMoveArc->DrawUnLit();
}

void Skeleton::Update()
{

	//Move();
	UpdateEnemyState();

	Math::Vector3 playerPos = {};
	if (m_wpPlayer.expired() == false)
	{
		std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
		playerPos = spPlayer->GetPos();
	}
	
	// 敵の向きを変える
	FlipEnemy(playerPos, m_pos, m_scale);
	
	m_spMoveArc->Update(playerPos,m_pos);
}

void Skeleton::PostUpdate()
{

	// レイ判定(地面)
	RayCollition(m_pos, m_gravity, 0, 0.2, KdCollider::TypeGround);


	m_spMoveArc->PostUpdate(m_pos);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale({ m_scale,1.0f,1.0f });

	m_mWorld = m_scaleMat * m_transMat;
}


void Skeleton::Move()
{
	Math::Vector3 playerPos = {};

	if (m_wpPlayer.expired() == false)
	{
		std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();

		playerPos = spPlayer->GetPos();
	}

	BaseEnemy::Move(playerPos, m_pos, m_speed);

}

void Skeleton::Attack()
{

}

void Skeleton::UpdateEnemyState()
{
	switch (m_eEnemyState)
	{
	case BaseEnemy::EnemyState::IDLE:
		m_polygon->SetUVRect(m_idle[(int)PlayAnim(0.1,3,m_animCnt,m_eEnemyState)]);
		break;
	case BaseEnemy::EnemyState::WALK:
		m_polygon->SetUVRect(m_walk[(int)PlayAnim(0.15, 3, m_animCnt, m_eEnemyState)]);
		break;
	case BaseEnemy::EnemyState::HIT:
		m_polygon->SetUVRect(m_hit[(int)PlayAnim(0.2, 3, m_animCnt, m_eEnemyState)]);
		break;
	case BaseEnemy::EnemyState::DEATH:
		m_polygon->SetUVRect(m_death[(int)PlayAnim(0.2, 3, m_animCnt, m_eEnemyState)]);
		break;
	case BaseEnemy::EnemyState::ATTACK:
		m_polygon->SetUVRect(m_attack[(int)PlayAnim(0.2, 4, m_animCnt, m_eEnemyState)]);
		break;
	}

}


void Skeleton::Release()
{

}

