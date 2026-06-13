#pragma once

class SlashEffect :public KdGameObject
{
public:

	SlashEffect() { Init(); }
	~SlashEffect() {};

	void Init()override;
	void Update()override;

	void DrawUnLit()override;

	void SetAngle(Math::Vector3 alngle) { m_angle = alngle; }
	void SetAnimCnt(int cnt) { m_animCnt = cnt,m_maxAnimCnt=cnt+=3; }

	void SetPlayerPos(Math::Vector3 pos) { m_playerPos = pos; }
	void SetMousePos(Math::Vector3 pos) { m_mousePos = pos; }

private:

	std::shared_ptr<KdSquarePolygon>m_polygon=nullptr;

	float m_animCnt = {};

	float m_scale = 1;

	Math::Vector3 m_angle = {};

	float m_maxAnimCnt = {};
	Math::Vector3 m_pos={};

	Math::Vector3 m_playerPos = {};
	Math::Vector3 m_mousePos = {};

};