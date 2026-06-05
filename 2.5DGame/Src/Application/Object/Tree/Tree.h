#pragma once

class Tree :public KdGameObject
{
public:

	Tree() { Init(); }
	~Tree()override{}

	void Init()override;
	void DrawLit()override;


private:

	std::shared_ptr<KdModelData>m_model=nullptr;

};