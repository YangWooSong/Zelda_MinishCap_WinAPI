#include "stdafx.h"
#include "MovingFloor.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Player.h"

CMovingFloor::CMovingFloor() : m_iDir(-1), m_time(GetTickCount()), m_bMove(true)
{
}

CMovingFloor::~CMovingFloor()
{
    Release();
}

void CMovingFloor::Initialize()
{
    m_pFrameKey = L"Dungeon_MovingFloor";
    m_vSize = { 336, 144 };
    m_fSpeed = 1.f;

    m_eRender = RENDER_BACKGROUND;
}

int CMovingFloor::Update()
{
    if (m_bMove)
    {
        //위아래 방향 전환
        if (m_vPos.y > 3430.f || m_vPos.y < 3100)
        {
            m_bMove = false;
            m_iDir *= -1;
        }
        else
            m_vPos.y += m_iDir * m_fSpeed;
    }  
    else
    {
        //도착하면 잠시 대기
        if (m_time + 10000 < GetTickCount())
        {
            m_bMove = true;
            m_vPos.y += m_iDir * m_fSpeed;
            m_time = GetTickCount();
        }
           
    }

  
  

   
    return 0;
}

void CMovingFloor::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void CMovingFloor::Render(HDC hDC)
{
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

    BitBlt(hDC, m_vCameraPos.x - (m_vSize.x * 0.5f), m_vCameraPos.y - (m_vSize.y * 0.5f), m_vSize.x, m_vSize.y, hMemDC, 0, 0, SRCCOPY);
}

void CMovingFloor::Release()
{
}


void CMovingFloor::OnCollisionStay(CObj* _pOther)
{
    if (dynamic_cast<CPlayer*>(_pOther) != nullptr)
    {
        if (m_bMove)
            _pOther->Set_PosY(_pOther->Get_Pos().y + (m_iDir * m_fSpeed));
    }
}