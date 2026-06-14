#include "ChargeEffect.h"

#include"../../../Object/Enemy/BaseEnemy.h"
void ChargeEffect::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Effects/ChargeEffect/ChargeEffect.png");

	m_polygon->SetSplit(12, 1);

	m_polygon->SetScale(2);

	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_animCnt = 0;

}

void ChargeEffect::Update()
{

	if (m_wpEnemy.expired() == true||!m_wpEnemy.lock()->GetAttackFlg())
	{
		m_isExpired = true;
		return;
	}


	m_animCnt += 0.2;

	frame++;
	if (frame > 60*1)
	{
		m_isExpired = true;
	}

	m_polygon->SetUVRect((int)m_animCnt);
	

	m_mWorld = Math::Matrix::CreateTranslation(m_wpEnemy.lock()->GetPos()+Math::Vector3(0,0,-0.2));
	
}

void ChargeEffect::DrawUnLit()
{
	Math::Color color = { 1,1,1,0.7 };
	
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld,color);
}
