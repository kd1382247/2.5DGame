#pragma once
#include"../../Enemy/BaseEnemy.h"

class MushroomAttackArc;

class Mushroom:public BaseEnemy
{
public:

	Mushroom() { Init(); }
	~Mushroom()override { Release(); }

	void Init()      override;

	void Update()    override;
	void PostUpdate()override;

	void DrawSprite()override;

	bool GetMoveFlg() { return m_moveFlg; }

	bool GetAttackAliveFlg() { return m_attackArcAliveFlg; }

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

	std::shared_ptr<MushroomAttackArc>m_mushroomAtkArc=nullptr;

	Math::Vector3 m_targetPos = {};
	Math::Vector3 m_nowPos = {};

	float m_moveCnt = {};

	bool  m_attackArcAliveFlg = {};

};