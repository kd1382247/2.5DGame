#include "AttackArc.h"

#include"../Object/Player/Player.h"
#include"../Mouse/Mouse.h"

void AttackArc::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Cursor/Cursor.gltf");


	m_pos = {0,0.8,0};
	m_angle = {};

	m_transMat = Math::Matrix::Identity;
	m_rotationMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;
}

void AttackArc::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, kBlueColor);
}

void AttackArc::Update()
{
	m_angle = atan2(m_player->GetPos().x - Mouse::Instance().Get3DMousePos().x, m_player->GetPos().z - Mouse::Instance().Get3DMousePos().z);

	m_rotationMat = Math::Matrix::CreateRotationY(m_angle);

	m_transMat = Math::Matrix::CreateTranslation(m_pos);

}

void AttackArc::PostUpdate()
{


	Math::Matrix transMat = Math::Matrix::Identity;
	if (m_player)
	{
		transMat = Math::Matrix::CreateTranslation(m_player->GetPos());
	}

	m_mWorld = (m_transMat*m_rotationMat)*transMat;
}
