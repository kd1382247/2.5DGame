#pragma once
#include"../../Enemy/BaseEnemy.h"

class FlyingEye :public BaseEnemy
{
public:

	FlyingEye() { Init(); }
	~FlyingEye()override {}

	void Init()      override;
	void Update()    override;
	void PostUpdate()override;


private:

	void Release();
	void UpdateEnemyState();


	// アニメーション変数
	int m_idle[8] = { 0,1,2,3,4,5,6,7 };
	int m_hit[4] = { 8,19,10,11 };
	int m_death[4] = { 15,16,17,18 };
	int m_attack[5] = { 27,28,29,30,31 };

};
