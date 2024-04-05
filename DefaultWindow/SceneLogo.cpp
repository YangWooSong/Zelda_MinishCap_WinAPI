#include "stdafx.h"
#include "SceneLogo.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
CSceneLogo::CSceneLogo()
{
}

CSceneLogo::~CSceneLogo()
{
	Release();
}

void CSceneLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/LogoBack.bmp", L"Scene_Logo");
	CSoundMgr::Get_Instance()->PlaySoundW(L"01_Title_Screen.wav", SOUND_BGM,1.f);

	m_tFrame = { 0, 96, 0, 80, GetTickCount() };
	m_pFrameKey = L"Scene_Logo";
}

int CSceneLogo::Update()
{
	if (m_tFrame.iFrameStart >= 95)
		m_tFrame.iFrameStart = 90;

	return 0;
}

void CSceneLogo::Late_Update()
{
	if (CKeyMgr::Get_Instance()->GetKeySate(KEY::ENTER) == KEY_STATE::TAP)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_HOUSE);
		return;
	}

	__super::Move_Frame();
}

void CSceneLogo::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Scene_Logo");

	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		0, // 복사 받을 위치의 left
		0,			 // 복사 받을 위치의 top
		WINCX,			 // 복사 받을 가로 길이
		WINCY,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		m_tFrame.iFrameStart * WINCX,						// 출력할 비트맵의 시작 x좌표
		m_tFrame.iMotion * WINCY,						// 출력할 비트맵의 시작 y좌표
		WINCX,			// 출력할 비트맵의 가로 사이즈
		WINCY,			// 출력할 비트맵의 세로 사이즈
		NULL);	// 제거할 픽셀의 색상 값
}

void CSceneLogo::Release()
{
}
