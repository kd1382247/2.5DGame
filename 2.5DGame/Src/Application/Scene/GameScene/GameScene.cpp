#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Mouse/Mouse.h"

#include"../../main.h"

#include"../../Object/Ground/Ground.h"
#include"../../Object/Player/Player.h"



void GameScene::Event()
{

	// タイトルに戻る
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	
	// カメラ更新
	Math::Vector3 camPos = { 0,5,-10 };

	Math::Matrix  rotationMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(20));

	Math::Matrix  transMat = Math::Matrix::CreateTranslation(camPos+m_player->GetPos());


	Math::Matrix  camWolrd = rotationMat * transMat;

	m_camera->SetCameraMatrix(camWolrd);



	// 画面上のマウス座標を取得
	Get2DMousePos();
	
	// マウス座標 2D～3D座標に変換
	GetMouseWorldPosition();

}

void GameScene::Init()
{
	// ●カメラ実体化
	
	//ユニークポインタは領域を指すことができるポインタを自分だけにする
	//                     ↓ユニークポインタで管理されている
	m_camera = std::make_unique <KdCamera>();


	// ●オブジェクト追加
	// ①ポインタを用意
	std::shared_ptr<Ground>ground;

	// ②実体化
	ground = std::make_shared<Ground>();
	// ③初期化
	// ※黒崎教はコンストラクタでInitを呼ぶので不要
	// ④オブジェクトリストに追加
	m_objList.push_back(ground);


	
	m_player = std::make_shared<Player>();
	m_objList.push_back(m_player);

}


void GameScene::Get2DMousePos()
{
	//ディスプレイ上のマウス座標を取得(PC画面左上(0,0))
	GetCursorPos(&m_mouse2D);

	//指定のウィンドウ基準のマウス座標に変換(実行画面の左上(0,0))
	ScreenToClient(Application::Instance().GetWindowHandle(), &m_mouse2D);

	Mouse::Instance().Set2DMousePos(m_mouse2D);

}

void GameScene::GetMouseWorldPosition()
{
	
	POINT mouse;

	//ディスプレイ上のマウス座標を取得(PC画面左上(0,0))
	GetCursorPos(&mouse);

	//指定のウィンドウ基準のマウス座標に変換(実行画面の左上(0,0))
	ScreenToClient(Application::Instance().GetWindowHandle(), &mouse);

	// 2Dから3D座標への変換
	Math::Vector3 rayPos;
	Math::Vector3 rayDir;
	float rayRange;

	m_camera->GenerateRayInfoFromClientPos(mouse, rayPos, rayDir, rayRange);

	float groundY = 1;

	float t = (groundY - rayPos.y) / rayDir.y;
	Math::Vector3 hit = rayPos + rayDir * t;

	hit;

	// マウスクラスに渡す
	Mouse::Instance().Set3DMousePos(hit);
}
