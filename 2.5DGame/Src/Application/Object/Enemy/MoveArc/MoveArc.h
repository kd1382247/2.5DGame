#pragma once

class MoveArc
{
public:

	MoveArc() { Init(); }
	~MoveArc(){}

	
	void Init();
	void Update(Math::Vector3 playerPos, Math::Vector3 enemyPos);
	void PostUpdate(Math::Vector3 enemyPos);

	void DrawUnLit();

	void SetPos(Math::Vector3 pos) { m_pos = pos; }

private:

	std::shared_ptr<KdModelData>m_mode=nullptr;
	

	Math::Vector3 m_pos = {};
	float         m_angle = {};


	Math::Matrix  m_transMat = Math::Matrix::Identity;
	Math::Matrix  m_rotationMat = Math::Matrix::Identity;
	Math::Matrix  m_mWorld = Math::Matrix::Identity;

};