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


	bool GetAttackFlg() { return m_attackFlg; }

	
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

	// プレイヤーのウィークポインタ
	std::weak_ptr<Player>m_wpPlayer;

	// プレイヤーの座標
	Math::Vector3 m_playerPos = {};
	float         m_playerRadius = {};

	// 座標と移動量
	Math::Vector3 m_pos = {};
	Math::Vector3 m_moveVec = {};
	float         m_speed = {};

	// 半径
	float         m_radius = {};

	bool          m_attackFlg = {};

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
	float PlayAnim(float cntUp, int maxAnim, float& animCnt, EnemyState& enemyState, bool& attackFlg);

	// 攻撃アニメーション関数
	float PlayAttackAnim(float cntUp,int maxAnim,float&animCnt,EnemyState&enemyState,bool&attackFlg);

	// 移動関数
	void  Move(Math::Vector3 playerPos, Math::Vector3& enemyPos, float speed);
	// プレイヤーの方向に向く関数
	void  FlipEnemy(Math::Vector3 playerPos,Math::Vector3 enemyPos,float &scale);
	// 攻撃関数
	void  Attack(Math::Vector3 enemyPos, Math::Vector3 playerPos, float enemyRadius, float playerRadius, EnemyState& enemyState, bool& m_attackFlg);

	// レイ判定
	void RayCollition(Math::Vector3& m_pos, float& gravity, float upPosY, float enableStepHigh, KdCollider::Type type);


};