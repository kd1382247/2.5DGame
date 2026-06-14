#pragma once

class KeyGuide :public KdGameObject
{
public:

	KeyGuide() { Init(); }
	~KeyGuide()override{}

	void Init()override;
	void DrawSprite()override;

private:

	std::shared_ptr<KdTexture>m_keyTex=nullptr;
	std::shared_ptr<KdTexture>m_MouseTex=nullptr;

	Math::Vector3 m_pos = {};


};