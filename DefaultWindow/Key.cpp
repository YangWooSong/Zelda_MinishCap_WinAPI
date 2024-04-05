#include "stdafx.h"
#include "Key.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "SceneDungeon.h"
#include "SoundMgr.h"

CKey::CKey() : Render_y(0), Render_x(0), m_bActive(false), m_pScene(nullptr)
{
}

CKey::~CKey()
{
}

void CKey::Initialize()
{
    m_pFrameKey = L"Item";
    m_vSize = { 60, 60 };
    Render_x = 180;
    Render_y = 120;
    m_eRender = RENDER_BACKGROUND;
}

int CKey::Update()
{
    return 0;
}

void CKey::Late_Update()
{
    if(m_bActive)
         Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void CKey::Render(HDC hDC)
{
    if(m_bActive)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
        m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

        GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
            (int)(m_vCameraPos.x - (m_vSize.x*0.5)), // ���� ���� ��ġ�� left
            (int)(m_vCameraPos.y-(m_vSize.y * 0.5)),			 // ���� ���� ��ġ�� top
            (int)m_vSize.x,			 // ���� ���� ���� ����
            (int)m_vSize.y,			 // ���� ���� ���� ����
            hMemDC,					// ��Ʈ���� ������ �ִ� dc
            Render_x,						// ����� ��Ʈ���� ���� x��ǥ
            Render_y,						// ����� ��Ʈ���� ���� y��ǥ
            (int)m_vSize.x,			// ����� ��Ʈ���� ���� ������
            (int)m_vSize.y,			// ����� ��Ʈ���� ���� ������
            RGB(0, 0, 255));	// ������ �ȼ��� ���� ��
        //RenderCollision(hDC);
    }
}
void CKey::OnCollisionEnter(CObj* _pOther)
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
    CSoundMgr::Get_Instance()->PlaySound(L"MC_Emote_Exclaim.wav", SOUND_EFFECT2, 1.f);
    m_bActive = false;
    dynamic_cast<CSceneDungeon*>(m_pScene)->Set_KeyCount();
    Set_Collider(0, 0,0,0);
}
void CKey::Release()
{
}
