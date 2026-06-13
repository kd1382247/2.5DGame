#pragma once
#include"../../Enemy/BaseEnemy.h"

class SkeletonAttackArc;

class Skeleton :public BaseEnemy
{
public:

	Skeleton() { Init(); }
	~Skeleton()override { Release(); }

	void Init()      override;
	void Update()    override;
	void PostUpdate()override;
	void DrawSprite()override;

private:

	void Release();
	void UpdateEnemyState();
	void OutroUpdate();

	// アニメーション変数

	int m_idle[4] = {0,1,2,3};
	int m_walk[4] = {8,9,10,11};
	int m_hit[4] = { 16,17,18,19 };
	int m_death[13] = { 16,17,18,19,24,24,25,25,26,26,27,27,27 };
	int m_attack[8] = {32,33,34,35,36,37,38,39};

	std::shared_ptr<SkeletonAttackArc>m_skeletonAtkArc = nullptr;


};