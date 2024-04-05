#include "stdafx.h"
#include "EyeShield.h"
#include "LaserBall.h"
#include "BmpMgr.h"
#include "Camera.h"

CEyeShield::CEyeShield()
{
}

CEyeShield::~CEyeShield()
{
	Release();
}

void CEyeShield::Initialize()
{
    m_pFrameKey = L"Boss1_Laser";
    m_vSize = { 122.f, 73.f };

    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

    Set_Collider(0, 0, 0, 0);
    m_eRender = RENDER_CEILLING;

    m_eId = OBJ_EYES;
}

int CEyeShield::Update()
{
    if(m_pTarget)
    {
        if (m_bActive)
        {
            m_vPos = m_pTarget->Get_Pos();
            m_bActive = dynamic_cast<CLaserBall*>(m_pTarget)->Get_ShieldActive();
        }
    }
	
    
    return 0;
}

void CEyeShield::Late_Update()
{
    if (m_bActive)
    {
        m_eCurState = ATTACK;
        Set_Collider(m_vPos.x, m_vPos.y, 45.f, 45.f);
    }
    else
        Set_Collider(0, 0, 0, 0);

    if (m_ePreState != m_eCurState)
    {
        if(m_eCurState == ATTACK)
        {
            //기본 애니메이션만 존재
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 4;
            m_tFrame.iMotion = 1;
            m_tFrame.dwSpeed = 100;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.bIsPlayDone = false;
        }

        m_ePreState = m_eCurState;

    }
    __super::Move_Frame();
}

void CEyeShield::Render(HDC hDC)
{
    if (m_bActive)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss1_Eye");
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
            RGB(255, 0, 255));	// 제거할 픽셀의 색상 값

        //RenderCollision(hDC);
    }

}

void CEyeShield::Release()
{
}
