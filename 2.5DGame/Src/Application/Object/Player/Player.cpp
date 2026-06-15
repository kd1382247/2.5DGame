#include "Player.h"

#include"../../Scene/SceneManager.h"
#include"../../Mouse/Mouse.h"
#include"../UI/HPBar/HPBar.h"

#include"../Effects/SlashEffect/SlashEffect.h"

void Player::Init()
{

	// デバッグ用 : KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Player/player.png");


	m_polygon->SetSplit(12, 8);

	m_polygon->SetScale(3.0f);

	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_tex.Load("Asset/Textures/HpBar/All.png");


	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"PlayerCollision",
		{0,0.5,0},
		0.3,
		KdCollider::Type::TypeBump);

	////=======================================

	m_pos = {-10,0,0,};
	m_scaleX = {};

	m_hp = maxHP;

	// 半径
	m_radius = 1.5;

	// 重力
	m_gravity = 0.0f;

	m_transMat = Math::Matrix::Identity;
	m_scaleMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;

	m_spHPBar = std::make_shared<HPBar>();

}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Player::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Player::DrawSprite()
{
	Math::Vector3 hpPos = m_mWorld.Translation();

	m_pCamera->ConvertWorldToScreenDetail(hpPos, hpPos);

	m_spHPBar->Draw(hpPos, true);
}

void Player::Update()
{
	Move();
	Attack();
	FlipCharacter();
}

void Player::PostUpdate()
{

	// 行列作成
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, 1.0f, 1.0f);
	m_mWorld =m_scaleMat * m_transMat;


	RayCollision(m_pos, 0, 0.2f,KdCollider::TypeGround);
	SphereCollision(m_pos, 1, 0.5, KdCollider::TypeGround);
	SphereCollision(m_pos, 1, 0.3, KdCollider::TypeBump);

	Damage();

	UpdatePlayerState();
	m_spHPBar->Update(m_hp, maxHP);
}

void Player::Release()
{

}

void Player::Move()
{	
	m_moveVec = Math::Vector3::Zero;

	// 攻撃していなかったら
	if(!m_attackFlg)
	{

		if (GetAsyncKeyState('W') & 0x8000)m_moveVec.z = 1.0f;
		if (GetAsyncKeyState('S') & 0x8000)m_moveVec.z = -1.0f;
		if (GetAsyncKeyState('A') & 0x8000)m_moveVec.x = -1.0f;
		if (GetAsyncKeyState('D') & 0x8000)m_moveVec.x = 1.0f;


		if(!m_hitFlg)
		{
			// 移動量が0だったら待機モーション
			if (m_moveVec == Math::Vector3::Zero)
			{
				m_eNextPlayerState = PlayerState::IDLE;
			}
			// 移動量が0以外だったら走るモーション
			else
			{
				m_eNextPlayerState = PlayerState::RUN;
			}
		}

	}

	// 正規化
	m_moveVec.Normalize();

	m_pos += m_moveVec * moveSpd;

	m_pos.y -= m_gravity;
	m_gravity += 0.01;

}

void Player::Attack()
{
	m_damageFlg = false;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_attackFlg)
		{
			m_attackFlg = true;
			m_hitFlg = false;
			m_damageFlg = true;

			m_inputWindowFrame = 0;
			m_inputWindowFlg = false;

			Math::Vector3 mousePos = Mouse::Instance().Get3DMousePos();

			if (m_attackPattern == (int)PlayerState::ATTACK1)
			{
				m_eNextPlayerState = PlayerState::ATTACK1;
			}
			if (m_attackPattern == (int)PlayerState::ATTACK2)
			{
				m_eNextPlayerState = PlayerState::ATTACK2;
			}
			if (m_attackPattern == (int)PlayerState::ATTACK3)
			{
				m_eNextPlayerState = PlayerState::ATTACK3;
			}
		}
	}

	// 3段攻撃モーションの受付フラグ
	if(m_inputWindowFlg)
	{
		// 受付時間カウントアップ
		m_inputWindowFrame++;

		// 一定の時間で受付終了
		if (m_inputWindowFrame > 60 * 0.2)
		{
			// 1段目の攻撃に戻る
			m_attackPattern = 0;
			m_attackFlg = false;
			m_inputWindowFlg = false;
		}
	}
}

void Player::UpdatePlayerState()
{
	ChangePlayerState();

	switch (m_eNextPlayerState)
	{
	case PlayerState::ATTACK1:
		
		m_polygon->SetUVRect(m_attack1[(int)PlayAnim(0.25, 4)]);

		break;
	case PlayerState::ATTACK2:

		m_polygon->SetUVRect(m_attack2[(int)PlayAnim(0.2, 3)]);

		break;
	case PlayerState::ATTACK3:

		m_polygon->SetUVRect(m_attack3[(int)PlayAnim(0.25, 5)]);

		break;
	case PlayerState::IDLE:

		m_polygon->SetUVRect(m_idle[(int)PlayAnim(0.15,6,m_animCnt)]);

		break;
	case PlayerState::RUN:

		m_polygon->SetUVRect(m_run[(int)PlayAnim(0.2, 6,m_animCnt)]);

		break;
	case PlayerState::GUARD:


		break;
	case PlayerState::HIT:

		m_polygon->SetUVRect(m_hit[(int)PlayAnim(0.1, 3, m_animCnt)]);
		break;
	case PlayerState::DEATH:


		break;
	}
}

void Player::RayCollision(Math::Vector3& m_pos, float upPosY, float enableStepHigh,KdCollider::Type type)
{
	// 当てる側
		// ==================
		// レイ(光線)判定
		//===================
	KdCollider::RayInfo ray;
	// レイの発射位置を設定
	ray.m_pos = m_pos;
	// ちょっと上からの位置にする
	ray.m_pos.y += upPosY;
	// 段差の許容用範囲
	ray.m_pos.y += enableStepHigh;
	// レイの発射方向を設定
	ray.m_dir = { 0,-1,0 };
	// レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;
	// 当たり判定を行いたいタイプを設定
	ray.m_type =type;

	// デバッグ
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	// レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult>retRayList;
	// 当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		// 全オブジェクトに対してレイ判定する関数を呼び出す
		obj->Intersects(ray, &retRayList);
	}

	// レイリストから一番近いオブジェクトを探す
	float         maxOverlap = 0;
	Math::Vector3 hitPos;
	bool          hit = false;

	for (auto& ret : retRayList)
	{
		// レイを遮断しオーバー下長さが一番長いものを探す
		if (maxOverlap < ret.m_overlapDistance)
		{
			// 更新
			maxOverlap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}
	if (hit == true)
	{
		// 当たっていたらその座標をプレイヤー座標にセット
		m_pos = hitPos + Math::Vector3(0, 0, 0);

		m_gravity = 0;
	}
}

void Player::SphereCollision(Math::Vector3& m_pos, float centerY, float radius, KdCollider::Type type)
{
	// ==================
	// 球(スフィア)判定
	//===================
	// 球判定用の変数を用意
	KdCollider::SphereInfo sphere;
	// 球の中心座標を設定
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += centerY;
	// 球の半径を設定
	sphere.m_sphere.Radius = radius;
	// 当たり判定をしたいタイプを設定
	sphere.m_type = type;

	// デバッグ
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	// 球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult>retSphereList;


	// 全部ジェクトと当たり判定をする!
	for (auto& obj : SceneManager::Instance().GetObjList())
	{

		if(obj!=this->shared_from_this() )
		{
			// 全オブジェクトに対してレイ判定する関数を呼び出す
			obj->Intersects(sphere, &retSphereList);

		}
	}

	// 球に当たったリストから一番近いオブジェクトを探す
	float maxOverlap = 0;
	bool hit = false;
	Math::Vector3 hitDir;  // 当たった方向

	for (auto& ret : retSphereList)
	{
		// 球にめり込んだ長さが一番長いものを探す
		if (maxOverlap < ret.m_overlapDistance)
		{
			// 更新
			maxOverlap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true)
	{
		hitDir.y = 0;

		// ※方向ベクトルは絶対長さ１
		// 正規化 (長さが1)
		hitDir.Normalize();

		// 押し戻し処理
		m_pos += hitDir * maxOverlap;
	}
}

void Player::Damage()
{
	//==============
	// 球判定
	//==============
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos();
	sphere.m_sphere.Radius = 0.3;
	sphere.m_type = KdCollider::TypeDamage;

	// デバッグ
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	// 当たったオブジェクト情報を格納するリストは不要！！

	// 全てのオブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//                           ↓リストをセットしていた
		if (obj->Intersects(sphere, nullptr) == true)
		{
			if(obj->GetCollisionFlg())
			{
				// 当たった！！
				// 敵オブジェクト確定！！
				obj->OnHit();

				obj->SetCollisionFlg(false);
				m_hp-=10;
				m_hitFlg = true;
				m_eNextPlayerState = PlayerState::HIT;

				if (m_hp < 0)
				{
					m_hp = 0;
				}
			}
		}
	}
}

float Player::PlayAnim(float cntUp,int maxAnim,float& animCnt)
{

	if (animCnt >maxAnim)
	{
		animCnt = 0;
		
		if (m_eNextPlayerState == PlayerState::HIT)
		{
			m_hitFlg = false;
			m_attackFlg = false;
		}


		if(m_eNextPlayerState !=PlayerState::IDLE)
		{
			m_eNextPlayerState = PlayerState::IDLE;
		}

	
	}

	animCnt += cntUp;

	return animCnt;
	
}

float Player::PlayAnim(float cntUp, int maxAnim)
{
	if (m_animCnt > maxAnim)
	{
		m_animCnt = 0;
		m_attackFlg = false;

		// 攻撃パターンのカウントアップ
		m_attackPattern++;

		// ３段攻撃までしたら、リセット
		if (m_attackPattern >= 3)
		{
			m_attackPattern = 0;
		}

		// 入力受付フラグをture
		m_inputWindowFlg = true;

		// 攻撃が終われば待機モーション
		m_eNextPlayerState = PlayerState::IDLE;
	}

	m_animCnt += cntUp;

	return m_animCnt;
}

void Player::FlipCharacter()
{
	// マウスのX座標にキャラの向きを合わせる

		if (Mouse::Instance().Get3DMousePos().x > m_pos.x)
		{
			m_scaleX = 1;
		}
		if (Mouse::Instance().Get3DMousePos().x < m_pos.x)
		{
			m_scaleX = -1;
		}
	

}

void Player::ChangePlayerState()
{
	if (m_eNowPlayerState != m_eNextPlayerState)
	{

		m_animCnt = 0;
		m_eNowPlayerState = m_eNextPlayerState;
	}
}

