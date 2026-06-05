#pragma once

class Player;
class BaseEnemy;

class MoveArc:public KdGameObject
{
public:

	MoveArc() { Init(); }
	~MoveArc(){}

	
	void Init()        override;
	void Update()      override;
	void PostUpdate()  override;

	void DrawUnLit()   override;

	void SetPos(Math::Vector3 pos) { m_pos = pos; }

	void SetEnemyInst(std::shared_ptr<BaseEnemy> enemy){m_wpEnemy = enemy;}
	void SetPlayerInst(std::shared_ptr<Player>player) { m_wpPlayer = player; }


private:

	std::shared_ptr<KdModelData>m_mode=nullptr;
	
	std::weak_ptr<BaseEnemy>m_wpEnemy;
	std::weak_ptr<Player>   m_wpPlayer;


	Math::Vector3 m_pos = {};
	float         m_angle = {};

	bool          m_attackFlg = {};


	Math::Matrix  m_transMat = Math::Matrix::Identity;
	Math::Matrix  m_rotationMat = Math::Matrix::Identity;

};