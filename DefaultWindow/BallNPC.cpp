#include "stdafx.h"
#include "BallNPC.h"
#include "BmpMgr.h"
#include "Camera.h"
CBallNPC::CBallNPC()
{
}

CBallNPC::~CBallNPC()
{
    Release();
}

void CBallNPC::Initialize()
{
    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
    m_pFrameKey = L"NPC_Ball";
    m_vSize = { 120.f,120.f };

    m_eRender = RENDER_GAMEOBJECT;
}

int CBallNPC::Update()
{
    Motion_Change();
    __super::Move_Frame();
    return 0;
}

void CBallNPC::Late_Update()
{
}

void CBallNPC::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)(m_tFrame.iFrameStart * m_vSize.x),						// 출력할 비트맵의 시작 x좌표
		(int)(m_tFrame.iMotion * m_vSize.y),						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
		RGB(255, 255, 255));	// 제거할 픽셀의 색상 값
}

void CBallNPC::Release()
{
}

void CBallNPC::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;
		}
		m_ePreState = m_eCurState;
	}
}
