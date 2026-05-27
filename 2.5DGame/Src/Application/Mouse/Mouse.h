#pragma once

class Mouse
{
public:


	POINT         Get2DMousePos()                      { return m_mouse2D; }
	void          Set2DMousePos(POINT a_mouse)         { m_mouse2D = a_mouse; }

	Math::Vector3 Get3DMousePos()                      { return m_mouse3D; }
	void          Set3DMousePos(Math::Vector3 a_mouse) { m_mouse3D = a_mouse; }

private:



	// 画面サイズ
	static const int ScrWidth = 1280;
	static const int ScrHeight = 720;


	POINT m_mouse2D = {};
	Math::Vector3 m_mouse3D{};

private:

	Mouse() {}
	~Mouse() {}

public:

	static Mouse& Instance()
	{
		static Mouse instance;
		return instance;
	}

};