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
	//void PreUpdate()                    override;
	void Update()                       override;

	// プレイヤーのインスタンスをウィークポインタで取得
	void const SetPlayerInst(const std::shared_ptr<Player>player)
	{
		m_wpPlayer = player;
	}


	bool GetAttackFlg() { return m_attackFlg; }

private:

	void Release();

	bool m_attackAnimFlg = {};
	float m_attackTime = {};
	float m_frame = {};

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
	

	// 板ポリ
	std::shared_ptr<KdSquarePolygon>m_polygon = nullptr;

	// モデル
	std::shared_ptr<KdModelData>m_model = nullptr;

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
	EnemyState   m_eNowEnemyState = EnemyState::IDLE;
	EnemyState   m_eNextEnemyState=m_eNowEnemyState;
	

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
	float PlayAnim(float cntUp, int maxAnim);

	// 攻撃アニメーション関数
	float PlayAttackAnim(float cntUp,int maxAnim);

	// 移動関数
	void  Move(Math::Vector3 playerPos, Math::Vector3& enemyPos, float speed);
	// プレイヤーの方向に向く関数
	void  FlipEnemy(Math::Vector3 playerPos,Math::Vector3 enemyPos);
	// 攻撃関数
	void  Attack(Math::Vector3 enemyPos, Math::Vector3 playerPos, float enemyRadius, float playerRadius);
	// 敵の状態を管理する関数
	void ChangeEnemyState();

	// レイ判定
	void RayCollition(Math::Vector3& m_pos, float& gravity, float upPosY, float enableStepHigh, KdCollider::Type type);

	// プレイヤーの衝突判定
	void SphereCollition(Math::Vector3& m_pos, float centerY, float radius, KdCollider::Type type);

};