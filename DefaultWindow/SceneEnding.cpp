#include "stdafx.h"
#include "SceneEnding.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CSceneEnding::CSceneEnding()
{
}

CSceneEnding::~CSceneEnding()
{
    Release();
}

void CSceneEnding::Initialize()
{
    m_pFrameKey = L"Ending_Credit";

    m_eRender = RENDER_BACKGROUND;

    CSoundMgr::Get_Instance()->StopAll();
    CSoundMgr::Get_Instance()->PlayBGM(L"11_Hyrule_Field.wav", 1.f);

}

int CSceneEnding::Update()
{
    return 0;
}

void CSceneEnding::Late_Update()
{
}

void CSceneEnding::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

}

void CSceneEnding::Release()
{
}
