#pragma once


class Player;

class AttackArc :public KdGameObject
{

public:

	AttackArc() { Init(); }
	~AttackArc(){}

	void Init()      override;

	void DrawUnLit() override;

	void Update()    override;
	void PostUpdate()override;

	void SetPlayerInst(std::shared_ptr<Player>player) { m_player = player; }


private:

	
	std::shared_ptr<KdModelData>m_model;

	Math::Vector3 m_pos = {};

	float         m_angle = {};
	Math::Vector2 m_move = {};

	Math::Matrix  m_transMat = Math::Matrix::Identity;
	Math::Matrix  m_rotationMat=Math::Matrix::Identity;



	std::shared_ptr<Player>m_player;



};