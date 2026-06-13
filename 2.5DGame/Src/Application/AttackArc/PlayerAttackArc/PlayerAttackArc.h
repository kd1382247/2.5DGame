#pragma once


class Player;

class PlayerAttackArc :public KdGameObject
{

public:

	PlayerAttackArc() { Init(); }
	~PlayerAttackArc(){}

	void Init()      override;

	void DrawUnLit() override;

	void Update()    override;
	void PostUpdate()override;

	void SetPlayerInst(std::shared_ptr<Player>player) { m_wpPlayer = player; }


private:

	
	std::shared_ptr<KdModelData>m_model;


	Math::Vector3 m_pos = {};

	float         m_angle = {};
	Math::Vector2 m_move = {};

	Math::Matrix  m_transMat = Math::Matrix::Identity;
	Math::Matrix  m_rotationMat=Math::Matrix::Identity;



	std::weak_ptr<Player>m_wpPlayer;



};