#pragma once

class SmokeEffect :public KdGameObject
{
public:

	SmokeEffect() { Init(); }
	~SmokeEffect()override{}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;

private:


	std::shared_ptr<KdSquarePolygon>m_polygon=nullptr;

	const int maxAnimCnt = 20;
	float m_animCnt = {};


};