#pragma once
#include"../../Enemy/BaseEnemy.h"

class Mushroom:public BaseEnemy
{
public:

	Mushroom() { Init(); }
	~Mushroom()override { Release(); }

	void Init()      override;

	void Update()    override;
	void PostUpdate()override;

	void DrawSprite()override;

private:

	void Release();
	void UpdateEnemyState();
	void OutroUpdate();


	float m_anim = {};

	// アニメーション変数
	int m_idle[4] = { 0,1,2,3 };
	int m_walk[8] = { 8,9,10,11,12,13,14,15 };
	int m_hit[4] = { 16,17,18,19 };
	int m_death[13] = { 16,17,18,19,24,24,25,25,26,26,27,27,27 };
	int m_attack[8] = { 32,33,34,35,36,37,38,39 };


};