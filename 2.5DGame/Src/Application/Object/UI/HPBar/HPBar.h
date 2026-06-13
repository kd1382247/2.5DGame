#pragma once

class HPBar 
{

public:

	HPBar() { Init(); }
	~HPBar(){}

	void Init();
	void Update(int hp,int maxHp);
	void Draw(Math::Vector3 m_pos,bool flg);

private:


	std::shared_ptr<KdTexture>m_tex = {};

	// HPの割合
	float         m_rate = {};

	
};