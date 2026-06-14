#include "KeyGuide.h"

void KeyGuide::Init()
{
	m_keyTex = std::make_shared<KdTexture>();

	m_keyTex->Load("Asset/Textures/UI/KeyGuide/key.png");

	m_MouseTex = std::make_shared<KdTexture>();

	m_MouseTex->Load("Asset/Textures/UI/KeyGuide/mouse.png");
}

void KeyGuide::DrawSprite()
{


	KdShaderManager::Instance().m_spriteShader.DrawTex(m_keyTex,000,-300,247,61);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_MouseTex,300,-300,253,62);


}
