#pragma once

class Player :public KdGameObject
{
public:

	Player() { Init(); }
	~Player(){}


	void Init()   override;
	void DrawUnLit()override;
	void Update() override;
	

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


	void Move();
	void Attack();
	void Animation();
	float PlayAnim(float cntUp,int maxAnim);
	float AttackAnim(float cntUp,int maxAnim);

	void FlipCharacter();


	std::shared_ptr<KdSquarePolygon>m_polygon;

	// キャラの方向
	float m_scaleX=1;

	// 移動系
	Math::Vector3 m_pos = Math::Vector3::Zero;
	Math::Vector3 m_moveVec = {};
	const float   moveSpd = 0.1f;
	bool          m_moveFlg[4] = {};

	// 攻撃系
	bool          m_attackFlg = {};
	int           m_attackPattern = {};
	float         m_InputWindowFrame = {};
	bool          m_inputWindowFlg = {};


	// アニメーション系
	PlayerState   e_playerState = PlayerState::IDLE;
	float         m_moveAnimCnt = {};
	float         m_attackAnimCnt = {};

	// 各アニメーションの番号
	// 攻撃１
	int           m_attack1[5]= { 2,3,4,5,6 };
	// 攻撃2
	int           m_attack2[4] = { 12,13,14,15 };
	// 攻撃3
	int           m_attack3[6]= { 24,25,26,27,28,29 };

	// 待機モーション
	int           m_idle[7] =   { 36,37,38,39,40,41,42 };

	// 移動
	int           m_run[7] = {49,50,51,52,53,54,55 };


};