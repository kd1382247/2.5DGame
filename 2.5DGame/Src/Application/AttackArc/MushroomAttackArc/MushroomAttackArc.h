#pragma once

class Mushroom;

class MushroomAttackArc :public KdGameObject
{
public:

	MushroomAttackArc() { Init(); }
	~MushroomAttackArc()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void DrawUnLit()override;

	void SetMushroomInst(std::shared_ptr<Mushroom>mushroom) { m_wpMushroom = mushroom; }

	void SetPlayerPos(Math::Vector3 pos) { m_playerPos = pos; }

private:

	std::shared_ptr<KdModelData>m_model;

	Math::Vector3 m_pos = {};

	float         m_angle = {};
	Math::Vector2 m_move = {};

	Math::Matrix  m_transMat = Math::Matrix::Identity;
	Math::Matrix  m_rotationMat = Math::Matrix::Identity;

	Math::Vector3 m_playerPos = {};

	std::weak_ptr<Mushroom>m_wpMushroom;
	
};