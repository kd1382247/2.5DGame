#pragma once

class Wall :public KdGameObject
{

public:

	Wall() { Init(); }
	~Wall()override{}

	void Init()override;
	void DrawLit()override;


private:

	void Release();

	Math::Vector3 m_pos;
	
	std::shared_ptr<KdModelData>m_model=nullptr;

};