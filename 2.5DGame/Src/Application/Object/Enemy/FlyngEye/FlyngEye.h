#pragma once
#include"../../Enemy/BaseEnemy.h"


class FlyngEye :public BaseEnemy
{
public:

	FlyngEye() { Init(); }
	~FlyngEye()override { Release(); }

	void Init()      override;
	void Update()    override;
	void PostUpdate()override;

	void DrawSprite()override;

	void OutroUpdate();

	void OnHit()override;


private:

	void Release();
	void UpdateEnemyState();

	// アニメーション変数
	int m_walk[8] = { 0,1,2,3,4,5,6,7 };
	int m_hit[4] = { 8,9,10,11 };
	int m_death[13] = { 8,9,10,11,16,16,17,17,18,18,19,19,19 };
	int m_attack[8] = { 24,25,26,27,28,29,30,31 };
	
};
