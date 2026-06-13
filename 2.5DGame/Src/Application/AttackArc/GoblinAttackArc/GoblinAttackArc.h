#pragma once


class Goblin;

class GoblinAttackArc :public KdGameObject
{

public:

	GoblinAttackArc() { Init(); }
	~GoblinAttackArc() {}

	void Init()      override;

	void DrawUnLit() override;

	void Update()    override;
	void PostUpdate()override;

	void SetGoblinInst(std::shared_ptr<Goblin>Goblin) { m_wpGoblin = Goblin; }

	void SetPlayerPos(Math::Vector3 pos) { m_playerPos = pos; }

private:


	std::shared_ptr<KdModelData>m_model;


	Math::Vector3 m_pos = {};

	float         m_angle = {};
	Math::Vector2 m_move = {};

	Math::Matrix  m_transMat = Math::Matrix::Identity;
	Math::Matrix  m_rotationMat = Math::Matrix::Identity;

	Math::Vector3 m_playerPos = {};

	std::weak_ptr<Goblin>m_wpGoblin;



};