#include "stdafx.h"
#include "GageBar.h"
#include "BmpMgr.h"

CGageBar::CGageBar() : m_iStart(0), m_time(GetTickCount()), m_iRenderLength(230), m_bChangeLength(true), m_time2(GetTickCount())
{
}

CGageBar::~CGageBar()
{
    Release();
}

void CGageBar::Initialize()
{
    m_eRender = RENDER_UI;
    m_pFrameKey = L"GageBar_Bar";
}

int CGageBar::Update()
{
	if (m_bIsActive == true)
	{
		//bool 줄어드는 변수
		if (m_bChangeLength)
		{
			if(m_time2 + 108 < GetTickCount())
			{
				if (m_iRenderLength > 0)
					m_iRenderLength -= 2;
				m_time2 = GetTickCount();
			}
		}
		else 
			m_iRenderLength = 230;
	}

    return 0;
}

void CGageBar::Late_Update()
{
	
}

void CGageBar::Render(HDC hDC)
{
	if(m_bIsActive)
	{
		if (m_time + 300 < GetTickCount())
		{
			if (m_iStart == 0)
				m_iStart = 1;
			else
				m_iStart = 0;

			m_time = GetTickCount();
		}

		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
			m_vPos.x, // 복사 받을 위치의 left
			m_vPos.y,			 // 복사 받을 위치의 top
			m_iRenderLength,			 // 복사 받을 가로 길이
			7,			 // 복사 받을 세로 길이
			hMemDC,					// 비트맵을 가지고 있는 dc
			230 * m_iStart,						// 출력할 비트맵의 시작 x좌표
			0,						// 출력할 비트맵의 시작 y좌표
			m_iRenderLength,			// 출력할 비트맵의 가로 사이즈
			7,			// 출력할 비트맵의 세로 사이즈
			NULL);	// 제거할 픽셀의 색상 값
	}
}

void CGageBar::Release()
{
}
