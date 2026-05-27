#pragma once


//                       ↓全てのオブジェクトに継承
class Ground :public KdGameObject
{
public:

	Ground() { Init(); }
	~Ground(){}

	void Init()      override;
	void DrawLit()   override;


private:

	// モデルやテクスチャはポインタで管理
	std::shared_ptr < KdModelData > m_model;

};