#pragma once

class FlyngEye;

class EnergyBullet :public KdGameObject
{
public:

	EnergyBullet() { Init(); }
	~EnergyBullet()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void DrawUnLit()override;

	void OnHit()override;

	void SetPlayerPos(Math::Vector3 pos) { m_playerPos = pos; }
	void SetEnemyPos(Math::Vector3 pos) { m_enemyPos = pos; }
	
	void SetPos(Math::Vector3 pos) { m_pos = pos; }

	void SetEnemyInst(std::shared_ptr<FlyngEye>flyngEye) { m_wpEnemy = flyngEye; }

private:

	std::shared_ptr<KdSquarePolygon>m_polygon = nullptr;

	std::weak_ptr<FlyngEye>m_wpEnemy;


	Math::Vector3 m_pos = {};
	float m_animCnt = {};



	Math::Vector3 m_playerPos = {};

	Math::Vector3 m_enemyPos = {};

	const float   m_speed = 0.05;

};