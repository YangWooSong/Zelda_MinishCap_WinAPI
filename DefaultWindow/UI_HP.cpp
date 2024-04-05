#include "stdafx.h"
#include "UI_HP.h"
#include "BmpMgr.h"

CUI_HP::CUI_HP() : m_iFullCount(0), m_bFull(false)
{
	m_vSize = {30.f, 30.f};
}

CUI_HP::~CUI_HP()
{
	Release();
}

void CUI_HP::Initialize()
{
    m_eRender = RENDER_UI;
    m_pFrameKey = L"LinkHp";
}

int CUI_HP::Update()
{
    return 0;
}

void CUI_HP::Late_Update()
{
}

void CUI_HP::Render(HDC hDC)
{
	int iRender_x = 0;

	if (m_bFull)
	{
		iRender_x = 0;
	}
	else
	{
		switch (m_iFullCount)
		{
		case 0:
			iRender_x = 120;
			break;
		case 1:
			iRender_x = 90;
			break;
		case 2:
			iRender_x = 60;
			break;
		case 3:
			iRender_x = 30;
			break;

		default:
			break;
		}
		
	}


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		iRender_x,						// 출력할 비트맵의 시작 x좌표
		0,						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,		// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,					// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값

}

void CUI_HP::Release()
{
}
