#pragma once

class BaseEnemy;

class ChargeEffect :public KdGameObject
{
public:

	ChargeEffect() { Init(); }
	~ChargeEffect()override {}

	void Init()override;
	void Update()override;
	void DrawUnLit()override;


	void SetEnemyInst(std::shared_ptr<BaseEnemy> enemy) { m_wpEnemy = enemy; }

private:


	std::shared_ptr<KdSquarePolygon>m_polygon = nullptr;
	
	std::weak_ptr<BaseEnemy>m_wpEnemy;


	const int maxAnimCnt = 20;
	float m_animCnt = {};

	float frame = {};
};
