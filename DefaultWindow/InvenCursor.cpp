#include "stdafx.h"
#include "InvenCursor.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CInvenCursor::CInvenCursor()
{
}

CInvenCursor::~CInvenCursor()
{
}

void CInvenCursor::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inven/LargeSelectButton_Inven.bmp", L"LargeSelectButton_Inven");
	m_eRender = RENDER_INVEN;

	m_vPos = {200.f, 125.f};
	m_vSize = { 115.f,95.f };
}

int CInvenCursor::Update()
{
	return 0;
}

void CInvenCursor::Late_Update()
{
}

void CInvenCursor::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LargeSelectButton_Inven");

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		m_vPos.x- m_vSize.x * 0.5f, // 복사 받을 위치의 left
		m_vPos.y - m_vSize.y * 0.5f,			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		0,						// 출력할 비트맵의 시작 x좌표
		0,						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,		// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,					// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값

	//BitBlt(hDC, 0.f, 0.f, 88.f, 75.f, hMemDC, 0, 0, SRCCOPY);
}

void CInvenCursor::Move_Right()
{
	if (m_vPos.x + 108.f < 560.f)
	{
		m_vPos.x += 108.f;
		CSoundMgr::Get_Instance()->StopSound(SOUND_INVEN);
		CSoundMgr::Get_Instance()->PlaySound(L"MC_Menu_Cursor.wav", SOUND_INVEN, 1.f);
	}
}

void CInvenCursor::Move_Left()
{
	if (m_vPos.x - 108.f > 195.f)
	{
		m_vPos.x -= 108.f;
		CSoundMgr::Get_Instance()->StopSound(SOUND_INVEN);
		CSoundMgr::Get_Instance()->PlaySound(L"MC_Menu_Cursor.wav", SOUND_INVEN, 1.f);
	}
}

void CInvenCursor::Move_Up()
{
	if (m_vPos.y - 72.f > 120.f)
	{
		m_vPos.y -= 72.f;
		CSoundMgr::Get_Instance()->StopSound(SOUND_INVEN);
		CSoundMgr::Get_Instance()->PlaySound(L"MC_Menu_Cursor.wav", SOUND_INVEN, 1.f);
	}

}

void CInvenCursor::Move_Down()
{
	if (m_vPos.y + 72.f < 275.f)
	{
		m_vPos.y += 72.f;
		CSoundMgr::Get_Instance()->StopSound(SOUND_INVEN);
		CSoundMgr::Get_Instance()->PlaySound(L"MC_Menu_Cursor.wav", SOUND_INVEN, 1.f);
	}
}


void CInvenCursor::Release()
{
}

