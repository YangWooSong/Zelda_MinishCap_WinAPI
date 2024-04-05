#include "stdafx.h"
#include "Effect.h"
#include "BmpMgr.h"
#include "Camera.h"

CEffect::CEffect() : m_bActive(false)
{
}

CEffect::~CEffect()
{
    Release();
}

void CEffect::Initialize()
{
    m_vSize = { 100.f, 100.f };
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
	m_eRender = RENDER_EFFECT;
    m_eCurState = IDLE;
}

int CEffect::Update()
{
    if (m_pTarget)
    {
        m_vOwnerDir = m_pTarget->Get_Dir();

        m_vPos = m_pTarget->Get_Pos();
        if (m_vOwnerDir.x == 1)
        {
            m_vPos.x = m_pTarget->Get_Pos().x +  90.f;
            m_vPos.y = m_pTarget->Get_Pos().y;
        }
        else if (m_vOwnerDir.x == -1)
        {
            m_vPos.x = m_pTarget->Get_Pos().x - 90.f;
            m_vPos.y = m_pTarget->Get_Pos().y;
        }
        else if (m_vOwnerDir.y == 1)
        {
            m_vPos.y = m_pTarget->Get_Pos().y + 90.f;
            m_vPos.x = m_pTarget->Get_Pos().x;
        }
        else if (m_vOwnerDir.y == -1)
        {
            m_vPos.y = m_pTarget->Get_Pos().y - 90.f;
            m_vPos.x = m_pTarget->Get_Pos().x;
        }
      
    }
    if (m_bActive)
        m_eCurState = ATTACK;
    else
        m_eCurState = IDLE;

	return 0;
}

void CEffect::Late_Update()
{
    Motion_Change();

    Set_Collider(m_vPos.x, m_vPos.y, 100.f, 100.f);
    __super::Move_Frame();
}

void CEffect::Render(HDC hDC)
{
    if (m_bActive)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Pot_Effect");
        m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

        GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
            (int)(m_vCameraPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
            (int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
            (int)m_vSize.x,			 // ���� ���� ���� ����
            (int)m_vSize.y,			 // ���� ���� ���� ����
            hMemDC,					// ��Ʈ���� ������ �ִ� dc
            (int)(m_tFrame.iFrameStart * m_vSize.x),						// ����� ��Ʈ���� ���� x��ǥ
            (int)(m_tFrame.iMotion * m_vSize.y),						// ����� ��Ʈ���� ���� y��ǥ
            (int)m_vSize.x,			// ����� ��Ʈ���� ���� ������
            (int)m_vSize.y,			// ����� ��Ʈ���� ���� ������
            RGB(0, 0, 255));	// ������ �ȼ��� ���� ��

      //  RenderCollision(hDC);
    }
}

void CEffect::Release()
{
}

void CEffect::Motion_Change()
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

        case ATTACK:
           if (m_vOwnerDir.x == 1)
            {
                m_vPos.x = m_pTarget->Get_Pos().x + m_vSize.x * 0.5f + 40.f;
                m_tFrame.iMotion = 0;
            }
            else if (m_vOwnerDir.x == -1)
            {
                m_vPos.x = m_pTarget->Get_Pos().x - m_vSize.x * 0.5f - 40.f;
                m_tFrame.iMotion = 1;
            }
            else if (m_vOwnerDir.y == 1)
            {
                m_vPos.y = m_pTarget->Get_Pos().y + m_vSize.y * 0.5f + 40.f;
                m_tFrame.iMotion = 3;
            }
            else if (m_vOwnerDir.y == -1)
            {
                m_vPos.y = m_pTarget->Get_Pos().y -m_vSize.y * 0.5f - 40.f;
                m_tFrame.iMotion = 2;
            }

            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 3;
     
            m_tFrame.dwSpeed = 120;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.bIsPlayDone = true;
            break;

        }

        m_ePreState = m_eCurState;
    }
}
