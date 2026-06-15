#include "Mushroom.h"

#include"../../../Scene/SceneManager.h"
#include"../../Player/Player.h"
#include"../../UI/HPBar/HPBar.h"
#include"../../Effects/SmokeEffect/SmokeEffect.h"
#include"../../../AttackArc/MushroomAttackArc/MushroomAttackArc.h"


void Mushroom::Init()
{
	BaseEnemy::Init();

	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Enemy/Mushroom/Mushroom.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(8, 5);

	m_polygon->SetScale(5);

	m_pos = { 0,0,5 };

	m_radius = 1.5;


	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"MushroomrCollision",
		{0,0.5,0},
		0.5,
		KdCollider::Type::TypeBump);

	//=======================================

	m_spHPBar = std::make_shared<HPBar>();

}


void Mushroom::Update()
{

	if (m_outroFlg)
	{
		OutroUpdate();
		m_spHPBar->Update(m_hp, maxHP);
		return;
	}

	m_playerPos = {};
	if (m_wpPlayer.expired() == false)
	{
		std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();
		m_playerPos = spPlayer->GetPos();
	}


	if (!m_hitFlg)
	{
		if (!m_attackFlg && !m_AtkCoolTimeFlg&&!m_moveFlg)
		{
			Move(m_playerPos, m_pos, m_speed);

			FlipEnemy(m_playerPos, m_pos);
			Attack(m_pos, m_playerPos, m_radius, m_playerRadius);

			m_mushroomAtkArc = nullptr;
		}
		else
		{

			if (m_mushroomAtkArc == nullptr)
			{
				m_mushroomAtkArc = std::make_shared<MushroomAttackArc>();
				m_mushroomAtkArc->SetMushroomInst(std::dynamic_pointer_cast<Mushroom>(shared_from_this()));
				m_mushroomAtkArc->SetPos(m_pos + Math::Vector3(0, 0.1, 0));
				m_mushroomAtkArc->SetPlayerPos(m_playerPos);
				m_attackArcAliveFlg = true;
				m_targetPos = m_playerPos;
				m_nowPos = m_pos;
				
				SceneManager::Instance().AddObject(m_mushroomAtkArc);
			}
			else
			{
				
				if(m_moveFlg)
				{
					Math::Vector3 dir = m_targetPos - m_nowPos;

					dir.Normalize();

					m_pos += dir * 0.1;

					m_moveCnt++;
					if (m_moveCnt > 60 * 0.25)
					{
						m_moveFlg = false;
						m_attackArcAliveFlg = false;
						m_moveCnt = 0;
					}
				}

				m_mushroomAtkArc->SetPos(m_pos + Math::Vector3(0, 0.1, 0));

			}
		}
	
	}

	AttackCoolTime();

	UpdateEnemyState();

	m_spHPBar->Update(m_hp, maxHP);
}

void Mushroom::PostUpdate()
{

	RayCollision(m_pos, m_gravity, 0, 0.2, KdCollider::TypeGround);

	SphereCollision(m_pos, 1, 0.5, KdCollider::TypeBump);
	SphereCollision(m_pos, 1, 0.5, KdCollider::TypeGround);

	AttackArcCollision(m_pos, 1, 0.5, KdCollider::TypeDamage);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale({ m_scale,1.0f,1.0f });

	m_mWorld = m_scaleMat * m_transMat;
}

void Mushroom::DrawSprite()
{
	Math::Vector3 hpPos = m_mWorld.Translation();
	m_pCamera->ConvertWorldToScreenDetail(GetPos(), hpPos);
	m_spHPBar->Draw(hpPos, false);
}

void Mushroom::UpdateEnemyState()
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
	case BaseEnemy::EnemyState::ATTACK:
		m_polygon->SetUVRect(m_attack[(int)PlayAttackAnim(0.1, 7)]);
		break;
	}

}

void Mushroom::OutroUpdate()
{
	ChangeEnemyState();
	m_polygon->SetUVRect(m_death[(int)m_outroAnimCnt]);

	if (m_outroAnimCnt > maxOutroAnim)
	{
		m_isExpired = true;

		std::shared_ptr<SmokeEffect>smoke = std::make_shared<SmokeEffect>();
		smoke->SetPos(m_pos);
		SceneManager::Instance().AddObject(smoke);
	}
	else
	{
		m_outroAnimCnt += 0.2;
	}
}

void Mushroom::Release()
{
	
}

