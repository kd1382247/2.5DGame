#pragma once

class Player;

class BaseEnemy :public KdGameObject
{
public:

	BaseEnemy() {}
	~BaseEnemy()                        override {}

	void Init()                         override;

	void DrawLit()                      override;
	void GenerateDepthMapFromLight()	override;

	void Update()                       override;

	// プレイヤーのインスタンスをウィークポインタで取得
	void const SetPlayerInst(const std::shared_ptr<Player>player)
	{
		m_wpPlayer = player;
	}

	
private:

	void Release();

protected:
	
	// 敵の状態
	enum class EnemyState
	{
		IDLE,
		WALK,
		HIT,
		DEATH,
		ATTACK
	};
	

	std::shared_ptr<KdSquarePolygon>m_polygon = nullptr;

	std::weak_ptr<Player>m_wpPlayer;

	// 座標と移動量
	Math::Vector3 m_pos = {};
	Math::Vector3 m_moveVec = {};
	float         m_speed = {};

	// 敵の状態
	EnemyState   m_eEnemyState=EnemyState::IDLE;

	// アニメカウント
	float m_idleAnimCnt = {};
	float m_walkAnimCnt = {};
	float m_attackAnimCnt = {};
	float m_hitAnimCnt = {};
	float m_deathAnimCnt = {};

	// アニメカウント
	float m_animCnt = {};

	// スケール
	float m_scale = {};

	// 重力
	float m_gravity = {};

	// 行列
	Math::Matrix m_transMat=Math::Matrix::Identity;
	Math::Matrix m_scaleMat = Math::Matrix::Identity;

	// アニメーション関数
	float PlayAnim(float cntUp, int maxAnim, float& animCnt, EnemyState& enemyState);
	// 移動関数
	void  Move(Math::Vector3 playerPos,Math::Vector3 &enemyPos,float speed);
	// プレイヤーの方向に向く関数
	void  FlipEnemy(Math::Vector3 playerPos,Math::Vector3 enemyPos,float &scale);
	// レイ判定
	void RayCollition(Math::Vector3& m_pos, float& gravity, float upPosY, float enableStepHigh, KdCollider::Type type);
};