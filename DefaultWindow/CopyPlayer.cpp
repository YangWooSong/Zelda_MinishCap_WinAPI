#include "stdafx.h"
#include "CopyPlayer.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
CCopyPlayer::CCopyPlayer()
{
}

CCopyPlayer::~CCopyPlayer()
{
}

void CCopyPlayer::Initialize()
{
    m_fSpeed = 4.f;
    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
    m_pFrameKey = L"Player_Down";
	m_vSize = { 200.f, 200.f };
    Set_Collider(0, 0, 0, 0);
    m_eRender = RENDER_GAMEOBJECT;
    m_vLookDir = { 0.f, 1.f };

    m_eId = OBJ_PLAYER;
}

int CCopyPlayer::Update()
{
    Key_Input();

	m_vLookDir = m_pTarget->Get_Dir();

	if (m_bDead)
	{
		return OBJ_DEAD;
	}
    return OBJ_NOEVENT;
}

void CCopyPlayer::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, 50.f, 60.f);
    Motion_Change();

    __super::Move_Frame();
}

void CCopyPlayer::Render(HDC hDC)
{
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

    GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
        (int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
        (int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
        (int)m_vSize.x,			 // 복사 받을 가로 길이
        (int)m_vSize.y,			 // 복사 받을 세로 길이
        hMemDC,					// 비트맵을 가지고 있는 dc
        (int)(m_tFrame.iFrameStart * 200.f),						// 출력할 비트맵의 시작 x좌표
        (int)(m_tFrame.iMotion * 200.f),						// 출력할 비트맵의 시작 y좌표
        (int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
        (int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
        RGB(163, 13, 169));	// 제거할 픽셀의 색상 값

    //RenderCollision(hDC);
}

void CCopyPlayer::Release()
{
}

void CCopyPlayer::Key_Input()
{

		if (CKeyMgr::Get_Instance()->GetKeySate(KEY::RIGHT) == KEY_STATE::HOLD)
		{
			m_vLookDir = { 1,0 };
			m_vPos.x += m_fSpeed;
			m_pFrameKey = L"Player_Right";
			m_eCurState = WALK;
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::LEFT) == KEY_STATE::HOLD)
		{
			m_vLookDir = { -1,0 };
			m_vPos.x -= m_fSpeed;
			m_pFrameKey = L"Player_Left";
			m_eCurState = WALK;
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::UP) == KEY_STATE::HOLD)
		{
			m_vLookDir = { 0,-1 };
			m_vPos.y -= m_fSpeed;
			m_pFrameKey = L"Player_Up";
			m_eCurState = WALK;
		}

		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::DOWN) == KEY_STATE::HOLD)
		{
			m_vLookDir = { 0,1 };
			m_vPos.y += m_fSpeed;
			m_pFrameKey = L"Player_Down";
			m_eCurState = WALK;
		}
		else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::R) == KEY_STATE::TAP)
		{
			if (m_vLookDir.x == 1 && m_vLookDir.y == 0)
				m_vPos.x += m_fSpeed + 1.f;
			else if (m_vLookDir.x == -1)
				m_vPos.x -= m_fSpeed + 1.f;
			else if (m_vLookDir.y == -1)
				m_vPos.y -= m_fSpeed + 1.f;
			else if (m_vLookDir.y == 1)
				m_vPos.y += m_fSpeed + 1.f;
			m_eCurState = ROLL;
		}
	
		else
		{
			if (m_eCurState != DEAD && m_tFrame.bIsPlayDone == true)
			{
				m_eCurState = IDLE;
				m_tFrame.bIsPlayDone = false;
			}
		}

}

void CCopyPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = true;
			break;

		case ROLL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;

			break;

		case HIT:
			if (m_pFrameKey == L"Player_Down")
			{
				m_tFrame.iMotion = 13;
			}
			else
				m_tFrame.iMotion = 12;

			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwSpeed = 180;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case FALL:
			m_pFrameKey = L"Player_Down";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 12;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;


		}

		m_ePreState = m_eCurState;
	}
}

void CCopyPlayer::OnCollisionExit(CObj* _pOther)
{

}

void CCopyPlayer::OnCollisionStay(CObj* _pOther)
{

}

void CCopyPlayer::OnCollisionEnter(CObj* _pOther)
{

}