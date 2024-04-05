#include "stdafx.h"
#include "GageBarBack.h"
#include "AbstractFactory.h"
#include "GageBar.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
CGageBarBack::CGageBarBack() : m_pGageBar(nullptr)
{
}

CGageBarBack::~CGageBarBack()
{
}

void CGageBarBack::Initialize()
{
	m_pGageBar = new CGageBar();
	m_pGageBar->Initialize();

	m_vSize = { 242.f, 19.f };

    m_eRender = RENDER_UI;

}

int CGageBarBack::Update()
{
	if (m_pGageBar)
	{
		m_pGageBar->Set_Pos(m_vPos.x+6, m_vPos.y+6);
		m_pGageBar->Set_IsActive(m_bIsActive);
	}

 	if (dynamic_cast<CGageBar*>(m_pGageBar)->Get_RenderLength() <= 0)
	{
		m_bIsActive = false;
	}

	m_pGageBar->Update();

    return 0;
}

void CGageBarBack::Late_Update()
{
	
	m_pGageBar->Late_Update();
}

void CGageBarBack::Render(HDC hDC)
{
	if(m_bIsActive)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GageBar_BackGround");

		GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
			m_vPos.x, // 복사 받을 위치의 left
			m_vPos.y,			 // 복사 받을 위치의 top
			m_vSize.x,			 // 복사 받을 가로 길이
			m_vSize.y,			 // 복사 받을 세로 길이
			hMemDC,					// 비트맵을 가지고 있는 dc
			0,						// 출력할 비트맵의 시작 x좌표
			0,						// 출력할 비트맵의 시작 y좌표
			m_vSize.x,			// 출력할 비트맵의 가로 사이즈
			m_vSize.y,			// 출력할 비트맵의 세로 사이즈
			RGB(255, 0, 255));	// 제거할 픽셀의 색상 값
	}
	
	if (m_pGageBar)
	{
		m_pGageBar->Render(hDC);
	}
}

void CGageBarBack::Release()
{
}
