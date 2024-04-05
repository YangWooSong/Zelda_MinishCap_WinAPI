#include "stdafx.h"
#include "Laser.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "SoundMgr.h"

CLaser::CLaser()
    : m_bActive(false)
{
}

CLaser::~CLaser()
{
    Release();
}

void CLaser::Initialize()
{
    m_pFrameKey = L"Boss1_Laser";
    m_vSize = { 15.f, 800.f };

    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

    Set_Collider(0, 0, 0, 0);
    m_eRender = RENDER_GAMEOBJECT;
}

int CLaser::Update()
{
    if(m_pTarget)
        m_vPos.x = m_pTarget->Get_Pos().x - 1.f;
    return 0;
}

void CLaser::Late_Update()
{
    //눈동자 위치 받아와서 설정
    if (m_bActive)
    {

        m_eCurState = ATTACK;
        Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
    }

        
    else 
        Set_Collider(0, 0, 0, 0);
   
    if (m_ePreState != m_eCurState)
    {
        if (m_eCurState == ATTACK)
        {
           
            //기본 공격 애니메이션만 존재
            m_tFrame.iFrameStart = 1;
            m_tFrame.iFrameEnd = 1;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 150;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.bIsPlayDone = true;

        }

        m_ePreState = m_eCurState;

    }
    __super::Move_Frame();
}

void CLaser::Render(HDC hDC)
{
    if (m_bActive)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Boss1_Laser2");
        m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

        GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
            (int)(m_vCameraPos.x - m_vSize.x * 0.5f), // 복사 받을 위치의 left
            (int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // 복사 받을 위치의 top
            (int)m_vSize.x,			 // 복사 받을 가로 길이
            (int)m_vSize.y,			 // 복사 받을 세로 길이
            hMemDC,					// 비트맵을 가지고 있는 dc
            (int)(m_tFrame.iFrameStart * m_vSize.x),						// 출력할 비트맵의 시작 x좌표
            (int)(800- m_vSize.y),						// 출력할 비트맵의 시작 y좌표
            (int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
            (int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
            RGB(255, 0, 255));	// 제거할 픽셀의 색상 값

        //RenderCollision(hDC);
    }
  
}

void CLaser::Release()
{
}

