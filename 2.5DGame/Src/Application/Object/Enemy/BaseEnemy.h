#pragma once

class Player;

class HPBar;

class ChargeEffect;

class BaseEnemy :public KdGameObject
{
public:

	BaseEnemy() {}
	~BaseEnemy()                        override {}

	void Init()                         override;

	void DrawUnLit()                      override;
	void GenerateDepthMapFromLight()	override;

	void Update()                       override;

	// プレイヤーのインスタンスをウィークポインタで取得
	void const SetPlayerInst(const std::shared_ptr<Player>player)
	{
		m_wpPlayer = player;
	}

	void SetCameraInst(KdCamera* camera)
	{
		m_pCamera = camera;
	}

	bool GetAttackFlg() { return m_attackFlg; }

	bool GetOutroFlg() { return m_outroFlg; }

	Math::Vector3 GetPlayerPos() { return m_playerPos; }

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
	
	///////////////////////////////////////
	// ポインタ
	///////////////////////////////////////

	// 板ポリ
	std::shared_ptr<KdSquarePolygon>m_polygon = nullptr;

	// プレイヤーのウィークポインタ
	std::weak_ptr<Player>m_wpPlayer;

	// カメラポインタ
	KdCamera* m_pCamera = nullptr;
	
	// HPバーのポインタ
	std::shared_ptr<HPBar>m_spHPBar=nullptr;

	std::shared_ptr<ChargeEffect>m_spChargeEffect=nullptr;

	///////////////////////////////////////
	// 変数
	///////////////////////////////////////

	// プレイヤーの座標
	Math::Vector3 m_playerPos = {};
	float         m_playerRadius = {};

	// 座標と移動量
	Math::Vector3 m_pos = {};
	Math::Vector3 m_moveVec = {};
	float         m_speed = {};

	

	int           m_hp = {};
	const int     maxHP = 100;

	bool          m_hitFlg = {};

	// 半径
	float         m_radius = {};

	// 攻撃フラグ
	bool          m_attackFlg = {};

	bool          m_shotFlg = {};

	bool          m_AtkCoolTimeFlg = {};
	float         m_AtkCoolTimeCnt = {};


	// アウトロフラグ
	bool          m_outroFlg = {};
	const int     maxOutroAnim = 12;
	// 敵の状態
	EnemyState   m_eNowEnemyState = EnemyState::IDLE;
	EnemyState   m_eNextEnemyState=m_eNowEnemyState;
	

	// アニメカウント
	float m_animCnt = {};

	float m_outroAnimCnt = {};

	// スケール
	float m_scale = {};

	// 重力
	float m_gravity = {};

	// 行列
	Math::Matrix m_transMat=Math::Matrix::Identity;
	Math::Matrix m_scaleMat = Math::Matrix::Identity;

	///////////////////////////////////////////////
	//                 関数
	///////////////////////////////////////////////
	
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
	void RayCollision(Math::Vector3& m_pos, float& gravity, float upPosY, float enableStepHigh, KdCollider::Type type);

	// オブジェクトのスフィア判定
	void SphereCollision(Math::Vector3& m_pos, float centerY, float radius, KdCollider::Type type,Math::Color color= kWhiteColor);

	// プレイヤーの攻撃範囲入っているか
	void AttackArcCollision(Math::Vector3& m_pos, float centerY, float radius, KdCollider::Type type, Math::Color color = kWhiteColor);
	// 攻撃のクールタイム
	void AttackCoolTime();


};