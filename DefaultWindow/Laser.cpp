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
    //������ ��ġ �޾ƿͼ� ����
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
           
            //�⺻ ���� �ִϸ��̼Ǹ� ����
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

        GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
            (int)(m_vCameraPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
            (int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
            (int)m_vSize.x,			 // ���� ���� ���� ����
            (int)m_vSize.y,			 // ���� ���� ���� ����
            hMemDC,					// ��Ʈ���� ������ �ִ� dc
            (int)(m_tFrame.iFrameStart * m_vSize.x),						// ����� ��Ʈ���� ���� x��ǥ
            (int)(800- m_vSize.y),						// ����� ��Ʈ���� ���� y��ǥ
            (int)m_vSize.x,			// ����� ��Ʈ���� ���� ������
            (int)m_vSize.y,			// ����� ��Ʈ���� ���� ������
            RGB(255, 0, 255));	// ������ �ȼ��� ���� ��

        //RenderCollision(hDC);
    }
  
}

void CLaser::Release()
{
}

