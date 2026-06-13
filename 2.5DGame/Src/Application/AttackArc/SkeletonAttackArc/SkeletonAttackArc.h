#pragma once


class Skeleton;

class SkeletonAttackArc :public KdGameObject
{

public:

	SkeletonAttackArc() { Init(); }
	~SkeletonAttackArc() {}

	void Init()      override;

	void DrawUnLit() override;

	void Update()    override;
	void PostUpdate()override;

	void SetSkeletonInst(std::shared_ptr<Skeleton>skeleton) { m_wpSkeleton = skeleton; }

	void SetPos(Math::Vector3 pos) { m_pos = pos; }


private:


	std::shared_ptr<KdModelData>m_model;


	Math::Vector3 m_pos = {};

	float         m_angle = {};
	Math::Vector2 m_move = {};

	std::weak_ptr<Skeleton>m_wpSkeleton;
};