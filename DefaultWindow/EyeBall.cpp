#include "stdafx.h"
#include "EyeBall.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "SoundMgr.h"
#include "Boss1.h"
#include "ObjMgr.h"
#include "Player.h"


CEyeBall::CEyeBall()
	: m_fDistance (130.f)
{

}

CEyeBall::~CEyeBall()
{
    Release();
}

void CEyeBall::Initialize()
{
    m_pFrameKey = L"Boss1_Eye";
    m_vSize = { 122.f, 73.f };
    m_fSpeed = 1.f;

    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

    Set_Collider(0, 0, 0, 0);
    m_eRender = RENDER_CEILLING;

	m_iHp = 1;
}

int CEyeBall::Update()
{
	if (dynamic_cast<CBoss1*>(m_pTarget)->Get_CurState() == DEAD)
		return OBJ_DEAD;

	if (!dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_InvenActive())
	{
		m_fAngle += m_fSpeed;

		m_vPos.x = m_pTarget->Get_Pos().x + m_fDistance * cos(m_fAngle * (3.14 / 180.f));
		m_vPos.y = m_pTarget->Get_Pos().y - m_fDistance * sin(m_fAngle * (3.14 / 180.f));
	}

 	if (m_iHp <= 0)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
		CSoundMgr::Get_Instance()->PlaySound(L"MC_Enemy_Hit.wav", SOUND_MONSTER, 1.f);
		dynamic_cast<CBoss1*>(m_pTarget)->Minus_EyeCount();
		m_eCurState = DEAD;
		return OBJ_DEAD;
	}

    return OBJ_NOEVENT;
}

void CEyeBall::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, 30.f, 30.f);
	Motion_Change();
	__super::Move_Frame();
}

void CEyeBall::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss1_Eye");
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
		(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
		(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
		(int)m_vSize.x,			 // 복사 받을 가로 길이
		(int)m_vSize.y,			 // 복사 받을 세로 길이
		hMemDC,					// 비트맵을 가지고 있는 dc
		(int)(m_tFrame.iFrameStart * 300.f),						// 출력할 비트맵의 시작 x좌표
		(int)(m_tFrame.iMotion * 300.f),						// 출력할 비트맵의 시작 y좌표
		(int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
		(int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
		RGB(255, 0, 255));	// 제거할 픽셀의 색상 값

	//RenderCollision(hDC);
}


void CEyeBall::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = true;
			break;

		case ATTACKREADY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		}

		m_ePreState = m_eCurState;
	}
}
void CEyeBall::Release()
{
}
