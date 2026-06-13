#include "FlyngEye.h"

#include"../../../Scene/SceneManager.h"

#include"../../Player/Player.h"
#include"../../UI/HPBar/HPBar.h"
#include"../../Effects/SmokeEffect/SmokeEffect.h"

void FlyingEye::Init()
{
	BaseEnemy::Init();

	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Enemy/FlyngEye/FlyngEye.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon->SetSplit(8, 4);

	m_polygon->SetScale(5);

	m_pos = { 5,0,5 };

	m_radius = 1.5;

	m_eNowEnemyState = EnemyState::WALK;
	m_eNextEnemyState = m_eNowEnemyState;

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	"FlyngEyeCollition",
	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"Collision",
		{0,0.5,0},
		0.5,
		KdCollider::Type::TypeBump);

	//=======================================


	m_spHPBar = std::make_shared<HPBar>();



}

void FlyingEye::Update()
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


	if(!m_hitFlg)
	{
		if (!m_attackFlg)
		{
			Move(m_playerPos, m_pos, m_speed);

			FlipEnemy(m_playerPos, m_pos);
			Attack(m_pos, m_playerPos, m_radius, m_playerRadius);
		}

		
	}

	UpdateEnemyState();

	/*if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_hp++;
		if (m_hp >= maxHP)
		{
			m_hp = maxHP;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_hp--;
		if (m_hp <= 0)
		{
			m_hp =0;
		}
	}*/
}

void FlyingEye::PostUpdate()
{
	
	RayCollision(m_pos, m_gravity, 0, 0.2, KdCollider::TypeGround);

	SphereCollision(m_pos, 1, 0.5, KdCollider::TypeBump,kRedColor);
	SphereCollision(m_pos, 1, 0.5, KdCollider::TypeGround);

	AttackArcCollision(m_pos, 1, 0.5, KdCollider::TypeDamage);

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale({ m_scale,1.0f,1.0f });

	m_mWorld = m_scaleMat * m_transMat;

	m_spHPBar->Update(m_hp, maxHP);
}

void FlyingEye::DrawSprite()
{
	Math::Vector3 hpPos = m_mWorld.Translation();
	m_pCamera->ConvertWorldToScreenDetail(GetPos(), hpPos);
	m_spHPBar->Draw(hpPos, false);
}

void FlyingEye::OutroUpdate()
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

void FlyingEye::OnHit()
{

}

void FlyingEye::UpdateEnemyState()
{

	ChangeEnemyState();

	switch (m_eNextEnemyState)
	{
	case BaseEnemy::EnemyState::IDLE:
	case BaseEnemy::EnemyState::WALK:
		m_polygon->SetUVRect(m_walk[(int)PlayAnim(0.2, 7)]);
		break;
	case BaseEnemy::EnemyState::HIT:
		m_polygon->SetUVRect(m_hit[(int)PlayAnim(0.2, 3)]);
		break;
	case BaseEnemy::EnemyState::ATTACK:
		m_polygon->SetUVRect(m_attack[(int)PlayAttackAnim(0.1, 7)]);
		break;
	}

}

void FlyingEye::Release()
{
	
}
