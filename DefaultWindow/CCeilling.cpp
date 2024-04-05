#include "stdafx.h"
#include "CCeilling.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
int     m_iRenderX;
CCeilling::CCeilling():m_eSceneId(SC_HOUSE), m_iNum(0), m_iRenderX(0), m_iRenderY(0)
{
}
CCeilling::~CCeilling()
{
}
void CCeilling::Initialize()
{

	m_eRender = RENDER_CEILLING;
	m_pFrameKey = L"SceneHouse_Ceilling";
}

int CCeilling::Update()
{
	switch (m_eSceneId)
	{
	case SC_HOUSE:
		m_pFrameKey = L"SceneHouse_Ceilling";
		m_iRenderX = 114;
		m_iRenderY = 293;
		break;
	case SC_VILLAGE:
		switch (m_iNum)
		{
		case 0:
			m_pFrameKey = L"Town_0";
			m_iRenderX = 432;
			m_iRenderY = 180;
			break;
		case 1:
			m_pFrameKey = L"Town_Wood";
			m_iRenderX = 390;
			m_iRenderY = 23;
			break;
		case 2:
			m_pFrameKey = L"TownMark";
			m_iRenderX = 312;
			m_iRenderY = 117;
			break;
		}
		break;
	case SC_DUNGEON:
		switch (m_iNum)
		{
		case 0:
			m_pFrameKey = L"Dungeon0";
			m_iRenderX = 144;
			m_iRenderY = 48;
			break;
		case 1:
			m_pFrameKey = L"Dungeon1";
			m_iRenderX = 144;
			m_iRenderY = 192;
			break;
		case 2:
			m_pFrameKey = L"Dungeon2";
			m_iRenderX = 144;
			m_iRenderY = 192;
			break;
		case 3:
			m_pFrameKey = L"Dungeon3";
			m_iRenderX = 132;
			m_iRenderY = 96;
			break;
		case 4:
			m_pFrameKey = L"Dungeon4";
			m_iRenderX = 240;
			m_iRenderY = 192;
			break;
		case 5:
			m_pFrameKey = L"Dungeon5";
			m_iRenderX = 200;
			m_iRenderY = 30;
			break;
		case 6:
			m_pFrameKey = L"Dungeon6";
			m_iRenderX = 242;
			m_iRenderY = 478;
			break;
		}
		break;
	case SC_BOSS1:
		break;
	case SC_ENDING:
		break;
	}
    return 0;
}

void CCeilling::Late_Update()
{
}

void CCeilling::Render(HDC hDC)
{
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vCameraPos.x), // 복사 받을 위치의 left
		(int)(m_vCameraPos.y ),			 // 복사 받을 위치의 top
		(int)m_iRenderX,			 // 복사 받을 가로 길이
		(int)m_iRenderY,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		0,						// 출력할 비트맵의 시작 x좌표
		0,						// 출력할 비트맵의 시작 y좌표
		(int)m_iRenderX,			// 출력할 비트맵의 가로 사이즈
		(int)m_iRenderY,			// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값
}

void CCeilling::Release()
{
}
