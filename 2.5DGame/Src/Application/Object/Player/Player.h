#pragma once

class Player :public KdGameObject
{
public:

	Player() { Init(); }
	~Player()override{}


	void Init()                     override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()                  override;
	void DrawUnLit()                override;

	void Update()                   override;
	void PostUpdate()               override;
	
	//=================================
	// クラス外使用の関数
	//=================================

	float GetRadius() { return m_radius; }

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

	void RayCollition(Math::Vector3 &m_pos,float upPosY, float enableStepHigh,KdCollider::Type type);
	void SphereCollition(Math::Vector3 &m_pos,float centerY,float radius,KdCollider::Type type);


	float PlayAnim(float cntUp,int maxAnim,float & animCnt);
	float PlayAnim(float cntUp,int maxAnim);

	void FlipCharacter();


	std::shared_ptr<KdSquarePolygon>m_polygon=nullptr;
	std::shared_ptr<KdModelData>    m_model = nullptr;

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

	// 半径
	float         m_radius = {};

	// 攻撃系
	bool          m_attackFlg = {};
	int           m_attackPattern = {};
	float         m_inputWindowFrame = {};
	bool          m_inputWindowFlg = {};


	// アニメーション系
	PlayerState   e_playerState = PlayerState::IDLE;

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

	// 待機モーション
	int           m_idle[7] =   { 36,37,38,39,40,41,42 };

	// 移動
	int           m_run[7] = {49,50,51,52,53,54,55 };


	//std::enable_shared_from_this<Player>m_player;

};