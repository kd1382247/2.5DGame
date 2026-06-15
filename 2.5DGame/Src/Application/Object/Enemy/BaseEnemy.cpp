#include "BaseEnemy.h"

#include"../../Scene/SceneManager.h"

#include"../Player/Player.h"

#include"../Effects/ChargeEffect/ChargeEffect.h"

void BaseEnemy::Init()
{
	// デバッグ用 : KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_polygon = nullptr;

	// 移動関連
	m_pos = m_mWorld.Translation();
	m_moveVec = {};
	m_speed = 0.05f;
	m_scale = 1;

	// 攻撃フラグ
	m_attackFlg = {};

	// 半径
	m_radius = {};
	// 重力
	m_gravity = {};

	// アニメーション関連
	// 現在の状態を待機状態で初期化
	m_eNowEnemyState = EnemyState::IDLE;
	m_eNextEnemyState = m_eNowEnemyState;

	m_animCnt = {};

	m_outroAnimCnt = {};

	// プレイヤー座標初期化
	m_playerPos = {};
	m_playerRadius = {};

	// 行列初期化(単位行列)
	m_scaleMat = Math::Matrix::Identity;
	m_transMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;

	m_pCamera = nullptr;
	
	m_spHPBar = nullptr;

	m_AtkCoolTimeCnt = 0;
	m_AtkCoolTimeFlg = false;


	m_hp = maxHP;

}

void BaseEnemy::DrawUnLit()
{
	if(m_polygon)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
	}
}

void BaseEnemy::GenerateDepthMapFromLight()
{
	if(m_polygon)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
	}
}

void BaseEnemy::Update()
{

}

void BaseEnemy::Release()
{
	m_polygon = nullptr;
}

float BaseEnemy::PlayAnim(float cntUp, int maxAnim)
{
	if (m_animCnt > maxAnim)
	{
		m_animCnt = 0;

		if (m_eNextEnemyState == EnemyState::HIT)
		{
			m_hitFlg = false;
		}

		if (m_eNextEnemyState != EnemyState::IDLE)
		{
			m_eNextEnemyState = EnemyState::IDLE;
		}
	}

	m_animCnt += cntUp;

	return m_animCnt;
}

float BaseEnemy::PlayAttackAnim(float cntUp, int maxAnim)
{
	if (m_animCnt > maxAnim)
	{
		m_animCnt = 0;

		m_AtkCoolTimeFlg = true;

		m_eNextEnemyState = EnemyState::IDLE;

		m_attackTime = 0;
		m_attackAnimFlg = false;

		m_attackFlg = false;

		m_shotFlg = true;
		m_collisionFlg = false;
	}

	if (!m_attackAnimFlg)
	{
		m_animCnt += cntUp;

		m_collisionFlg = false;
	}
	else
	{
		m_attackTime++;	
	}

	if (m_attackAnimFlg && m_attackTime > 2)
	{
		m_attackAnimFlg = false;
		m_collisionFlg = true;
		m_moveFlg = true;
	}


	if (m_attackTime == 0 && m_animCnt > 6)
	{
		m_attackAnimFlg = true;
	}


	return m_animCnt;
}

void BaseEnemy::Move(Math::Vector3 plPos, Math::Vector3& enemyPos, float speed)
{
	m_eNextEnemyState = EnemyState::WALK;

	Math::Vector3 move = plPos - enemyPos;
	move.Normalize();
	move.y = 0;
	enemyPos += move * speed;

}

void BaseEnemy::FlipEnemy(Math::Vector3 playerPos, Math::Vector3 enemyPos)
{
	if (enemyPos.x > playerPos.x)
	{
		m_scale = -1;
	}
	if (enemyPos.x < playerPos.x)
	{
		m_scale = 1;
	}
}

void BaseEnemy::Attack(Math::Vector3 enemyPos, Math::Vector3 playerPos, float enemyRadius, float playerRadius)
{
		Math::Vector3 pos = playerPos - enemyPos;

		if (pos.Length() < enemyRadius + playerRadius)
		{
			m_attackFlg = true;
			m_eNextEnemyState = EnemyState::ATTACK;
		}
}

void BaseEnemy::ChangeEnemyState()
{
	if (m_eNowEnemyState != m_eNextEnemyState)
	{
		m_animCnt = 0;
		m_eNowEnemyState = m_eNextEnemyState;
	}
}

void BaseEnemy::RayCollision(Math::Vector3& m_pos, float& gravity,float upPosY, float enableStepHigh, KdCollider::Type type)
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
	ray.m_range = gravity + enableStepHigh;
	// 当たり判定を行いたいタイプを設定
	ray.m_type = type;

	// デバッグ
	//m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

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

		gravity = 0;
	}
}

void BaseEnemy::SphereCollision(Math::Vector3& m_pos, float centerY, float radius, KdCollider::Type type,Math::Color color)
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
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius,color);

	// 球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult>retSphereList;
	// 全部ジェクトと当たり判定をする!
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		// 全オブジェクトに対してレイ判定する関数を呼び出す
		if(obj!=this->shared_from_this())
		{
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

void BaseEnemy::AttackArcCollision(Math::Vector3& m_pos, float centerY, float radius, KdCollider::Type type, Math::Color color)
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
	sphere.m_type = KdCollider::TypeDamage;

	// デバッグ
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius,color);

	// 全部ジェクトと当たり判定をする!


		// 全オブジェクトに対してレイ判定する関数を呼び出す

	std::shared_ptr<KdGameObject>obj = m_wpPlayer.lock();
	if(obj)
	{
		if (obj->Intersects(sphere, nullptr) == true)
		{

			bool damageFlg = false;

			if (m_wpPlayer.expired() == false)
			{
				damageFlg = m_wpPlayer.lock()->GetDamageFlg();
			}

			if (damageFlg)
			{
				m_hitFlg = true;
				m_attackFlg = false;
				m_eNextEnemyState = EnemyState::HIT;
				m_animCnt = 0;
				m_hp -= 10;
				if (m_hp <= 0)
				{
					m_hp = 0;
					m_outroFlg = true;
					m_eNextEnemyState = EnemyState::DEATH;
				}
			}
		}
	}

}

void BaseEnemy::AttackCoolTime()
{
	if (m_AtkCoolTimeFlg)
	{
		m_AtkCoolTimeCnt++;
		if (m_AtkCoolTimeCnt > 60 * 0.5)
		{
			m_AtkCoolTimeCnt = 0;
			m_AtkCoolTimeFlg = false;
		}
	}
}


