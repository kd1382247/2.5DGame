#include "Goblin.h"

#include"../../Player/Player.h"

void Goblin::Init()
{
	BaseEnemy::Init();

	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Enemy/Goblin/Goblin.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(8, 5);

	m_polygon->SetScale(5);

	m_pos = { -5,0,0 };

	m_radius = 1.5;


	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Enemy/Enemy.gltf");

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"PlayerCollision",
		m_model,
		KdCollider::Type::TypeBump);

	//=======================================



}


void Goblin::Update()
{

	m_playerPos = {};
	if (m_wpPlayer.expired() == false)
	{
		std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
		m_playerPos = spPlayer->GetPos();
	}

	if(!m_attackFlg)
	{
		Move(m_playerPos, m_pos, m_speed);

		FlipEnemy(m_playerPos, m_pos);
	}

	Attack(m_pos, m_playerPos, m_radius, m_playerRadius);
	UpdateEnemyState();
}

void Goblin::PostUpdate()
{

	RayCollition(m_pos, m_gravity, 0, 0.2, KdCollider::TypeGround);

	SphereCollition(m_pos, 1, 0.8, KdCollider::TypeBump);
	SphereCollition(m_pos, 1, 0.8, KdCollider::TypeGround);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale({ m_scale,1.0f,1.0f });

	m_mWorld = m_scaleMat * m_transMat;
}

void Goblin::UpdateEnemyState()
{

	ChangeEnemyState();

	switch (m_eNextEnemyState)
	{
	case BaseEnemy::EnemyState::IDLE:
		m_polygon->SetUVRect(m_idle[(int)PlayAnim(0.1, 3)]);
		break;
	case BaseEnemy::EnemyState::WALK:
		m_polygon->SetUVRect(m_walk[(int)PlayAnim(0.15, 7)]);
		break;
	case BaseEnemy::EnemyState::HIT:
		m_polygon->SetUVRect(m_hit[(int)PlayAnim(0.2, 3)]);
		break;
	case BaseEnemy::EnemyState::DEATH:
		m_polygon->SetUVRect(m_death[(int)PlayAnim(0.2, 3)]);
		break;
	case BaseEnemy::EnemyState::ATTACK:
		m_polygon->SetUVRect(m_attack[(int)PlayAttackAnim(0.1, 7)]);
		break;
	}

}

void Goblin::Release()
{

}

