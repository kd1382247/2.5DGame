#pragma once

class HPBar;

class Player :public KdGameObject
{
public:

	Player() { Init(); }
	~Player()override { Release(); }


	void Init()                     override;

	void GenerateDepthMapFromLight()override;
	void DrawUnLit()                override;
	void DrawSprite()               override;


	void Update()                   override;
	void PostUpdate()               override;
	
	//=================================
	// クラス外使用の関数
	//=================================

	void SetCameraInst(KdCamera* camera) { m_pCamera = camera; }

	float GetRadius() { return m_radius; }

	bool  GetDamageFlg() { return m_damageFlg; }

	void SetPos(Math::Vector3 pos) { m_pos = pos; }
	Math::Vector3 GetPos() { return m_pos; }

private:

	enum class PlayerState
	{
		ATTACK1,
		ATTACK2,
		ATTACK3,
		IDLE,
		RUN,
		GUARD,
		HIT,
		DEATH
	};


	void Release();

	void Move();
	void Attack();
	void UpdatePlayerState();

	void RayCollision(Math::Vector3 &m_pos,float upPosY, float enableStepHigh,KdCollider::Type type);
	void SphereCollision(Math::Vector3 &m_pos,float centerY,float radius,KdCollider::Type type);

	void Damage();

	float PlayAnim(float cntUp,int maxAnim,float & animCnt);
	float PlayAnim(float cntUp,int maxAnim);

	void FlipCharacter();

	void ChangePlayerState();

	std::shared_ptr<KdSquarePolygon>m_polygon=nullptr;

	KdTexture m_tex;

	// 行列系
	Math::Matrix m_transMat=Math::Matrix::Identity;
	Math::Matrix m_scaleMat=Math::Matrix::Identity;

	// キャラの方向
	float m_scaleX = {};

	// 重力
	float m_gravity = {};

	// 移動系
	Math::Vector3 m_pos = Math::Vector3::Zero;
	Math::Vector3 m_moveVec = {};
	const float   moveSpd = 0.15f;

	// HP
	int           m_hp = {};
	const int     maxHP = 100;

	bool          m_damageFlg = {};

	bool          m_hitFlg = {};

	// 半径
	float         m_radius = {};

	// 攻撃系
	bool          m_attackFlg = {};
	int           m_attackPattern = {};
	float         m_inputWindowFrame = {};
	bool          m_inputWindowFlg = {};

	float         m_animCnt = {};

	// アニメーション系
	PlayerState   e_playerState = PlayerState::IDLE;

	PlayerState   m_eNowPlayerState = PlayerState::IDLE;
	PlayerState   m_eNextPlayerState = m_eNowPlayerState;

	float         m_runAnimCnt = {};
	float         m_idleAnimCnt = {};
	float         m_attackAnimCnt = {};

	// 各アニメーションの番号
	// 攻撃１
	int           m_attack1[5]= { 1,2,3,4,5 };
	// 攻撃2
	int           m_attack2[4] = { 12,13,14,15 };
	// 攻撃3
	int           m_attack3[6]= { 24,25,26,27,28,29 };

	int           m_hit[4] = {72,73,74,75};
	// 待機モーション
	int           m_idle[7] =   { 36,37,38,39,40,41,42 };

	// 移動
	int           m_run[7] = {49,50,51,52,53,54,55 };

	std::shared_ptr<HPBar>m_spHPBar=nullptr;

	
	KdCamera* m_pCamera = nullptr;
};