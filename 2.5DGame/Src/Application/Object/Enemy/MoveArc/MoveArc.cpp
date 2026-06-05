#include "MoveArc.h"

#include"../BaseEnemy.h"
#include"../../Player/Player.h"

void MoveArc::Init()
{
	m_mode = std::make_shared<KdModelData>();
	m_mode->Load("Asset/Models/Cursor/Cursor.gltf");

	m_pos = {0,0,-0.2};
	m_angle={};

	m_attackFlg = {};

	m_transMat = Math::Matrix::Identity;
	m_rotationMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;
}

void MoveArc::Update()
{

	// 敵の生存期限が切れたら
	if (m_wpEnemy.expired() == true)
	{
		m_isExpired = true;
	}

	// 敵座標を取得
	Math::Vector3 enemyPos = {};
	if (m_wpEnemy.expired() == false)
	{
		std::shared_ptr<BaseEnemy>enemy = m_wpEnemy.lock();

		enemyPos = enemy->GetPos();
		m_attackFlg = enemy->GetAttackFlg();
	}

	// プレイヤー座標を取得
	Math::Vector3 playerPos = {};
	if (m_wpPlayer.expired() == false)
	{
		std::shared_ptr<Player>player = m_wpPlayer.lock();

		playerPos = player->GetPos();
	}

	if(!m_attackFlg)
	{
		m_angle = atan2(enemyPos.x - playerPos.x, enemyPos.z - playerPos.z);

		m_rotationMat = Math::Matrix::CreateRotationY(m_angle);

		m_transMat = Math::Matrix::CreateTranslation(m_pos);
	}

}

void MoveArc::PostUpdate()
{
	// 敵座標を取得
	Math::Matrix transMat = Math::Matrix::Identity;

	Math::Vector3 enemyPos = {};
	if (m_wpEnemy.expired() == false)
	{
		std::shared_ptr<BaseEnemy>enemy = m_wpEnemy.lock();

		enemyPos=enemy->GetPos();
	}

	
	transMat = Math::Matrix::CreateTranslation(enemyPos);

	m_mWorld = (m_transMat * m_rotationMat) * transMat;
}

void MoveArc::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_mode, m_mWorld,kRedColor);
}
