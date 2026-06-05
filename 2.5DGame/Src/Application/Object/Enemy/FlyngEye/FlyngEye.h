#pragma once
#include"../../Enemy/BaseEnemy.h"

class MoveArc;

class FlyingEye :public BaseEnemy
{
public:

	FlyingEye() { Init(); }
	~FlyingEye()override {}

	void Init()      override;
	void DrawUnLit() override;
	void Update()    override;
	void PostUpdate()override;


private:

	void Release();


	void Move();
	void Attack();
	void UpdateEnemyState();

	//std::weak_ptr<Player>m_wpPlayer;

	// アニメーション変数
	int m_idle[8] = { 0,1,2,3,4,5,6,7 };
	int m_hit[4] = { 16,17,18,19 };
	int m_death[4] = { 24,25,26,27 };
	int m_attack[5] = { 35,36,37,38,39 };

	std::shared_ptr<MoveArc>m_spMoveArc=nullptr;
};
