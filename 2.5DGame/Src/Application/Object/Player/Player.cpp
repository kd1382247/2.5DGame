#include "Player.h"

#include"../../Mouse/Mouse.h"

void Player::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Player/player.png");

	m_polygon->SetSplit(12, 9);
	m_polygon->SetScale(3.0f);

	m_pos = { 0,1,0 };
}

void Player::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Player::Update()
{
	Move();
	Animation();
	Attack();
	FlipCharacter();

}



void Player::Move()
{	
	m_moveVec.x = 0;
	m_moveVec.z = 0;
	m_moveVec.y = 0;

	if(!m_attackFlg)
	{
		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_moveVec.x = -1.0f;

			e_playerState = PlayerState::RUN;

		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_moveVec.x = 1.0f;

			e_playerState = PlayerState::RUN;

		}
	

		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_moveVec.z = 1.0f;

			e_playerState = PlayerState::RUN;

		}
		

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_moveVec.z = -1.0f;

			e_playerState = PlayerState::RUN;

		}
		
	}

	if(!m_attackFlg)
	{
		// もしどの移動キーも押されていなければ
		if(m_moveVec==Math::Vector3::Zero)
		{
			e_playerState = PlayerState::IDLE;
		}
	}


	// 正規化
	m_moveVec.Normalize();


	m_pos += m_moveVec * moveSpd;


	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);

	m_mWorld = scaleMat * transMat;
}

void Player::Attack()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_attackFlg)
		{
			m_attackFlg = true;

			m_InputWindowFrame = 0;
			m_inputWindowFlg = false;

			if(m_attackPattern==(int)PlayerState::ATTACK1)
			{
				e_playerState = PlayerState::ATTACK1;

			}
			if (m_attackPattern == (int)PlayerState::ATTACK2)
			{
				e_playerState = PlayerState::ATTACK2;
			}
			if (m_attackPattern == (int)PlayerState::ATTACK3)
			{
				e_playerState = PlayerState::ATTACK3;
			}

			m_moveAnimCnt = 0;
		}
	}

	if(m_inputWindowFlg)
	{
		m_InputWindowFrame++;
		if (m_InputWindowFrame > 60 * 0.2)
		{
			m_attackPattern = 0;
			m_inputWindowFlg = false;
		}
	}
}

void Player::Animation()
{

	switch (e_playerState)
	{


	case PlayerState::ATTACK1:
		
		m_polygon->SetUVRect(m_attack1[(int)AttackAnim(0.25, 4)]);

		break;
	case PlayerState::ATTACK2:

		m_polygon->SetUVRect(m_attack2[(int)AttackAnim(0.2, 3)]);

		break;
	case PlayerState::ATTACK3:

		m_polygon->SetUVRect(m_attack3[(int)AttackAnim(0.25, 5)]);

		break;
	case PlayerState::IDLE:

		m_polygon->SetUVRect(m_idle[(int)PlayAnim(0.15,6)]);

		break;
	case PlayerState::RUN:

		m_polygon->SetUVRect(m_run[(int)PlayAnim(0.2, 6)]);


		break;
	case PlayerState::GUARD:


		break;
	case PlayerState::HIT:


		break;
	case PlayerState::DEATH:


		break;
	}
}

float Player::PlayAnim(float cntUp,int maxAnim)
{
	
	if (m_moveAnimCnt >maxAnim)
	{
		m_moveAnimCnt = 0;
		if(e_playerState!=PlayerState::IDLE)
		{
			e_playerState = PlayerState::IDLE;
		}
	}

	m_moveAnimCnt += cntUp;

	return m_moveAnimCnt;
	
}

float Player::AttackAnim(float cntUp, int maxAnim)
{
	if (m_attackAnimCnt > maxAnim)
	{
		m_attackAnimCnt = 0;

		m_attackPattern++;
		if (m_attackPattern >= 3)
		{
			m_attackPattern = 0;
		}

		m_inputWindowFlg = true;

		m_attackFlg = false;

		e_playerState = PlayerState::IDLE;
	}

	m_attackAnimCnt += cntUp;

	return m_attackAnimCnt;
}

void Player::FlipCharacter()
{

	if(!m_attackFlg)
	{
		if (Mouse::Instance().Get3DMousePos().x > m_pos.x)
		{
			m_scaleX = 1;
		}
		if (Mouse::Instance().Get3DMousePos().x < m_pos.x)
		{
			m_scaleX = -1;
		}
	}

}

