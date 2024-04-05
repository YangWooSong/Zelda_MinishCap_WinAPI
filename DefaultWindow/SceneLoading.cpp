#include "stdafx.h"
#include "SceneLoading.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CSceneLoading::CSceneLoading()
{
}

CSceneLoading::~CSceneLoading()
{
    Release();
}

void CSceneLoading::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/LoadScene.bmp", L"LoadScene");
	m_pFrameKey = L"LoadScene";
}

int CSceneLoading::Update()
{
    return 0;
}

void CSceneLoading::Late_Update()
{
	if (CKeyMgr::Get_Instance()->GetKeySate(KEY::ENTER) == KEY_STATE::TAP)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
		return;
	}
}

void CSceneLoading::Render(HDC hDC)
{

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CSceneLoading::Release()
{
}
