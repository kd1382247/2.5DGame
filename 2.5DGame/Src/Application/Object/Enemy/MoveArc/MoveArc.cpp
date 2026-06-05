#include "MoveArc.h"

void MoveArc::Init()
{
	m_mode = std::make_shared<KdModelData>();
	m_mode->Load("Asset/Models/Cursor/Cursor.gltf");

	m_pos = {0,0,-0.2};
	m_angle={};

	m_transMat = Math::Matrix::Identity;
	m_rotationMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;
}

void MoveArc::Update(Math::Vector3 playerPos, Math::Vector3 enemyPos)
{
	m_angle = atan2(enemyPos.x - playerPos.x, enemyPos.z - playerPos.z);

	m_rotationMat = Math::Matrix::CreateRotationY(m_angle);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
}

void MoveArc::PostUpdate(Math::Vector3 enemyPos)
{
	Math::Matrix transMat = Math::Matrix::Identity;
	transMat = Math::Matrix::CreateTranslation(enemyPos);

	m_mWorld = (m_transMat * m_rotationMat) * transMat;
}

void MoveArc::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_mode, m_mWorld,kRedColor);
}
