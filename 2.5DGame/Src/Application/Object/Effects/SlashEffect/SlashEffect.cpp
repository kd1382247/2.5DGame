#include "SlashEffect.h"

void SlashEffect::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Effects/SlashEffect/Slash.png");

	m_polygon->SetSplit(8, 1);

	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_polygon->SetScale(3);

	m_mWorld = Math::Matrix::CreateTranslation(Math::Vector3(3, 2, 0));
}

void SlashEffect::Update()
{

	// ２段目
	// 三段目x=0,z=40

	// 現在のオブジェクト数をデバッグ
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("x%f",m_angle.x );
	KdDebugGUI::Instance().AddLog("z%f",m_angle.z );

	if (m_animCnt > m_maxAnimCnt)
	{
		m_animCnt = 0;
		m_isExpired = true;
		return;
	}

	m_animCnt += 0.1;
	m_polygon->SetUVRect(m_animCnt);


	Math::Matrix playerMat = Math::Matrix::CreateTranslation(m_playerPos);

	//Math::Matrix transMat = Math::Matrix::CreateRotationY(angle);
	Math::Matrix transMat2 = Math::Matrix::CreateTranslation(m_mousePos);

	Math::Matrix rotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
	Math::Matrix rotationZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(0));

	m_mWorld = (transMat2*rotationX*rotationZ);

}

void SlashEffect::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon,m_mWorld);
}
