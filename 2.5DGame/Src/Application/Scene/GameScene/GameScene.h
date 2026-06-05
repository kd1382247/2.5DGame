#pragma once

#include"../BaseScene/BaseScene.h"


class Player;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	void Get2DMousePos();

	void GetMouseWorldPosition();

	POINT m_mouse2D = {};
	Math::Vector3 m_mouse3D{};

	

	std::weak_ptr<Player>m_wpPlayer;
};
