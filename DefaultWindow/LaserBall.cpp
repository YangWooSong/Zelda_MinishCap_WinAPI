#include "stdafx.h"
#include "LaserBall.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Laser.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "EyeShield.h"
#include "SoundMgr.h"
#include "Boss1.h"
#include "Player.h"

CLaserBall::CLaserBall() : m_dwTime(GetTickCount()), m_pLaser (nullptr), m_pShield(nullptr), m_bShieldActive(true)
{
    Release();
}

CLaserBall::~CLaserBall()
{
}

void CLaserBall::Initialize()
{
    m_pFrameKey = L"Boss1_Eye";
    m_vSize = { 122.f, 73.f };
    m_fSpeed = 1.f;

    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };

    Set_Collider(0, 0, 0, 0);
    m_eRender = RENDER_GAMEOBJECT;

    m_iHp = 1;
    m_fDistance = 150.f;
    m_eId = OBJ_EYES;

    //레이저 생성
    m_pLaser = CAbstractFactory <CLaser>::Create();
    CObjMgr::Get_Instance()->Add_Object(OBJ_EYES, m_pLaser);
    //보호막 생성
    m_pShield = CAbstractFactory <CEyeShield>::Create();
   // CObjMgr::Get_Instance()->Add_Object(OBJ_EYES, m_pShield);
}

int CLaserBall::Update()
{
    if (dynamic_cast<CBoss1*>(m_pTarget)->Get_CurState() == DEAD )
        return OBJ_DEAD;

    if (!dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_InvenActive())
    {
        if (m_eCurState != ATTACK)
            m_fAngle += m_fSpeed;

        m_pShield->Update();
    }
    //m_dwTime = GetTickCount();

    if(m_tFrame.bIsPlayDone)
    {
        if (m_ePreState == IDLE)   //아이들 끝나면
        {
            m_eCurState = ATTACKREADY;
        }
        else if (m_ePreState == ATTACKREADY)   //준비 애니메이션 끝나면
        {
            Attack();
        }
        else if (m_ePreState == ATTACK)   //준비 애니메이션 끝나면
        {
            m_eCurState = IDLE;
            dynamic_cast<CLaser*>(m_pLaser)->Set_Active(false);
        }
    }

    if (!dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_InvenActive())
    {
        m_vPos.x = m_pTarget->Get_Pos().x + m_fDistance * cos(m_fAngle * (3.14 / 180.f));
        m_vPos.y = m_pTarget->Get_Pos().y - m_fDistance * sin(m_fAngle * (3.14 / 180.f));
    }

    if (m_iHp <= 0)
    {
        dynamic_cast<CBoss1*>(m_pTarget)->Minus_LaserEyeCount();
        CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
        CSoundMgr::Get_Instance()->PlaySound(L"MC_Enemy_Hit.wav", SOUND_MONSTER, 1.f);
        m_eCurState = DEAD;
        return OBJ_DEAD;
    }

    return OBJ_NOEVENT;
}

void CLaserBall::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, 30.f, 30.f);
    Motion_Change();
    m_pShield->Late_Update();
    __super::Move_Frame();
}

void CLaserBall::Render(HDC hDC)
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

    m_pShield->Render(hDC);
   // RenderCollision(hDC);
}

void CLaserBall::Release()
{
    Safe_Delete(m_pLaser);
    Safe_Delete(m_pShield);
}

void CLaserBall::Motion_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case IDLE:
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 0;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 500;
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
            m_tFrame.dwSpeed = 1500;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.bIsPlayDone = false;
            break;

        }

        m_ePreState = m_eCurState;
    }
}

void CLaserBall::Attack()
{
    m_eCurState = ATTACK;
    dynamic_cast<CLaser*>(m_pLaser) -> Set_Active(true);
    if (m_vPos.x > m_pTarget->Get_Pos().x - m_pTarget->Get_Collider_Scale().x * 0.5f
        && m_vPos.x < m_pTarget->Get_Pos().x + m_pTarget->Get_Collider_Scale().x * 0.5f
        && m_vPos.y < m_pTarget->Get_Pos().y
        )
    {
        //보스 위에 있을 때 
        dynamic_cast<CLaser*>(m_pLaser)->Set_Size(30.f, (m_pTarget->Get_Pos().y - m_pTarget->Get_Collider_Scale().y * 0.5f) - m_vPos.y);
        dynamic_cast<CLaser*>(m_pLaser)->Set_Pos(m_vPos.x, m_vPos.y + ((m_pTarget->Get_Pos().y - m_pTarget->Get_Collider_Scale().y * 0.5f) - m_vPos.y) * 0.5f + 15.f);
    }
    else
    {
        dynamic_cast<CLaser*>(m_pLaser)->Set_Size(30.f, 760.f - m_vPos.y);
        dynamic_cast<CLaser*>(m_pLaser)->Set_Pos(m_vPos.x, m_vPos.y + (760.f - m_vPos.y) * 0.5f + 15.f);
    }
    dynamic_cast<CLaser*>(m_pLaser)->Set_Target(this);
    dynamic_cast<CEyeShield*>(m_pShield)->Set_Target(this);
    CSoundMgr::Get_Instance()->StopSound(SOUND_BOSS);
    CSoundMgr::Get_Instance()->PlaySound(L"MC_Vaati_LightBlast_Hit.wav", SOUND_BOSS, 1.f);
}
