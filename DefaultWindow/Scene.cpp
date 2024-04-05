#include "stdafx.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "Wall.h"
CScene::CScene():m_bSceneChange(false)
{
	ZeroMemory(&m_vCameraRenderPos, sizeof(VEC2));
}


CScene::~CScene()
{
}

void CScene::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}

}
