#pragma once

class Mouse
{
public:

	POINT         Get2DMousePos()                      { return m_mouse2D; }
	void          Set2DMousePos(POINT mouse)         { m_mouse2D = mouse; }

	Math::Vector3 Get3DMousePos()                      { return m_mouse3D; }
	void          Set3DMousePos(Math::Vector3 mouse) { m_mouse3D = mouse; }

private:

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