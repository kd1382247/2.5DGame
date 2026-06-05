#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Mouse/Mouse.h"

#include"../../main.h"

#include"../../AttackArc/AttackArc.h"

#include"../../Object/Ground/Ground.h"
#include"../../Object/Wall/Wall.h"
#include"../../Object/Tree/Tree.h"

#include"../../Object/Player/Player.h"

#include"../../Object/Enemy/Mushroom/Mushroom.h"
#include"../../Object/Enemy/Goblin/Goblin.h"
#include"../../Object/Enemy/Skeleton/Skeleton.h"
#include"../../Object/Enemy/FlyngEye/FlyngEye.h"


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

	Math::Vector3 playerPos = {};
	if (m_wpPlayer.expired() == false)
	{
		std::shared_ptr<Player>spPlayer = m_wpPlayer.lock();

		playerPos = spPlayer->GetPos();
	}


	// カメラ更新
	Math::Vector3 camPos = { 0,8,-8 };
	//Math::Vector3 camPos = { 0,2,-6 };

	Math::Matrix  rotationMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));
	//Math::Matrix  rotationMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	Math::Matrix  transMat = Math::Matrix::CreateTranslation(camPos+playerPos);


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


	std::shared_ptr<Ground>ground;
	ground = std::make_shared<Ground>();
	m_objList.push_back(ground);

	std::shared_ptr<Wall>wall;
	wall = std::make_shared<Wall>();
	m_objList.push_back(wall);
	
	std::shared_ptr<Player>player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);

	std::shared_ptr<AttackArc>attackArc;
	attackArc = std::make_shared<AttackArc>();
	attackArc->SetPlayerInst(player);
	m_objList.push_back(attackArc);

	std::shared_ptr<Mushroom>mushroom;
	mushroom = std::make_shared<Mushroom>();
	mushroom->SetPlayerInst(player);
	m_objList.push_back(mushroom);

	std::shared_ptr<Goblin>goblin;
	goblin = std::make_shared<Goblin>();
	goblin->SetPlayerInst(player);
	m_objList.push_back(goblin);

	std::shared_ptr<FlyingEye>flyingEye;
	flyingEye = std::make_shared<FlyingEye>();
	flyingEye->SetPlayerInst(player);
	m_objList.push_back(flyingEye);

	std::shared_ptr<Skeleton>skeleton;
	skeleton = std::make_shared<Skeleton>();
	skeleton->SetPlayerInst(player);
	m_objList.push_back(skeleton);

	std::shared_ptr<Tree>tree;
	tree = std::make_shared<Tree>();
	m_objList.push_back(tree);

	m_wpPlayer = player;
	
}


void GameScene::Get2DMousePos()
{
	//ディスプレイ上のマウス座標を取得(PC画面左上(0,0))
	GetCursorPos(&m_mouse2D);

	//指定のウィンドウ基準のマウス座標に変換(実行画面の左上(0,0))
	ScreenToClient(Application::Instance().GetWindowHandle(), &m_mouse2D);

	m_mouse2D.x -= ScrWidth / 2;
	m_mouse2D.y -= ScrHeight / 2;
	m_mouse2D.y *= -1;

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
