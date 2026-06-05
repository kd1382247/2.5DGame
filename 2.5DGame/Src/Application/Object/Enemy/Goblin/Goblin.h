#pragma once
#include"../../Enemy/BaseEnemy.h"

class MoveArc;

class Goblin :public BaseEnemy
{
public:

	Goblin() { Init(); }
	~Goblin()override {}

	void Init()      override;
	void DrawUnLit() override;

	void Update()    override;
	void PostUpdate()override;


private:

	void Release();
	void Move();
	void Attack();

	void UpdateEnemyState();


	// アニメーション変数
	int m_idle[4] = { 0,1,2,3 };
	int m_walk[8] = { 8,9,10,11,12,13,14,15 };
	int m_hit[4] = { 16,17,18,19 };
	int m_death[4] = { 24,25,26,27 };
	int m_attack[5] = { 35,36,37,38,39 };

	std::shared_ptr<MoveArc>m_spMoveArc=nullptr;

};