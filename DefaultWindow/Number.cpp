#include "stdafx.h"
#include "Number.h"
#include "BmpMgr.h"

CNumber::CNumber() : m_iNum(0)
{
}

CNumber::~CNumber()
{
    Release();
}

void CNumber::Initialize()
{
    m_eRender = RENDER_UI;
    m_pFrameKey = L"Number";
	m_vSize = { 24.f,24.f };
}

int CNumber::Update()
{
    return 0;
}

void CNumber::Late_Update()
{
}

void CNumber::Render(HDC hDC)
{
	int iRender_x = 24.f;
	int iRender_y = 0;
	if (m_iNum == 10)
	{
		m_pFrameKey = L"Rupe";
		iRender_x =0;
		m_vSize = { 14.f,28.f };
	}
	else if (m_iNum == 11)
	{
		m_pFrameKey = L"Key_UI";
		iRender_x = 0;
		m_vSize = { 33.f,33.f };
	}
	else
		iRender_x *= m_iNum;

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		iRender_x,						// 출력할 비트맵의 시작 x좌표
		iRender_y,						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,		// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,					// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값

		

}

void CNumber::Release()
{
}
