#include "HPBar.h"

void HPBar::Init()
{

	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/UI/HPBar/HP.png");

	m_rate = {};
}

void HPBar::Update(int hp, int maxHp)
{
	m_rate = (float)hp / (float)maxHp;
}

void HPBar::Draw(Math::Vector3 m_pos, bool flg)
{

	Math::Rectangle rc = {};
	Math::Vector2 pivot = {};


	rc = { 0,20,58,10 };

	// HPバー(赤)
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, m_pos.x, m_pos.y - 10, 58, 10, &rc);

	if (flg)
	{
		// プレイヤーだったら青
		rc = { 0,0,60,9 };
	}
	else
	{
		// 敵だったら緑
		rc = { 0,10,60,9 };
	}

	pivot = { 0,0.5 };

	// HPバー(緑or青)
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, m_pos.x - 30, m_pos.y - 10, m_rate * 60, 9, &rc, nullptr, pivot);

	// HPフレーム
	rc = { 0,30,62,9 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, m_pos.x, m_pos.y - 10, 62, 9, &rc);


}
