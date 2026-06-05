#include "BaseEnemy.h"

#include"../../Scene/SceneManager.h"

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
	m_eEnemyState = EnemyState::IDLE;

	// 各アニメカウント
	m_idleAnimCnt = {};
	m_walkAnimCnt = {};
	m_attackAnimCnt = {};
	m_hitAnimCnt = {};
	m_deathAnimCnt = {};

	// プレイヤー座標初期化
	m_playerPos = {};
	m_playerRadius = {};

	// 行列初期化(単位行列)
	m_scaleMat = Math::Matrix::Identity;
	m_transMat = Math::Matrix::Identity;
	m_mWorld = Math::Matrix::Identity;

}

void BaseEnemy::DrawLit()
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

float BaseEnemy::PlayAnim(float cntUp, int maxAnim, float& animCnt,EnemyState &enemyState,bool&attackFlg)
{
	if (animCnt > maxAnim)
	{
		animCnt = 0;

		if (enemyState == EnemyState::ATTACK)
		{
			attackFlg = false;
		}

		if (enemyState != EnemyState::IDLE)
		{
			enemyState = EnemyState::IDLE;
		}
	}

	animCnt += cntUp;

	return animCnt;
}

void BaseEnemy::Move(Math::Vector3 plPos, Math::Vector3& enemyPos, float speed)
{
	Math::Vector3 move = plPos - enemyPos;
	move.Normalize();
	move.y = 0;
	enemyPos += move * speed;
}

void BaseEnemy::FlipEnemy(Math::Vector3 playerPos, Math::Vector3 enemyPos, float& scale)
{
	if (enemyPos.x > playerPos.x)
	{
		scale = -1;
	}
	if (enemyPos.x < playerPos.x)
	{
		scale = 1;
	}
}

void BaseEnemy::Attack(Math::Vector3 enemyPos, Math::Vector3 playerPos, float enemyRadius, float playerRadius, EnemyState& enemyState, bool& m_attackFlg)
{
	Math::Vector3 pos = playerPos - enemyPos;

	if (pos.Length() < enemyRadius + playerRadius)
	{
		m_attackFlg = true;
		enemyState = EnemyState::ATTACK;
	}
}

void BaseEnemy::RayCollition(Math::Vector3& m_pos, float& gravity,float upPosY, float enableStepHigh, KdCollider::Type type)
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

		gravity = 0;
	}
}

