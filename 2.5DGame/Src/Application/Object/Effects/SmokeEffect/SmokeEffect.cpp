#include "SmokeEffect.h"

void SmokeEffect::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Effects/SmokeEffect/Smoke.png");

	m_polygon->SetSplit(20, 1);

	m_polygon->SetScale(2);

	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_animCnt = 0;

}

void SmokeEffect::Update()
{
	m_animCnt += 0.4;
	if (m_animCnt > maxAnimCnt)
	{
		m_isExpired = true;
	}


	m_polygon->SetUVRect((int)m_animCnt);
}

void SmokeEffect::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
