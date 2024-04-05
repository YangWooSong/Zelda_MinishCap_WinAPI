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

        GdiTransparentBlt(hDC, // 최종적인 그림을 그릴 dc
            (int)(m_vCameraPos.x - (m_vSize.x*0.5)), // 복사 받을 위치의 left
            (int)(m_vCameraPos.y-(m_vSize.y * 0.5)),			 // 복사 받을 위치의 top
            (int)m_vSize.x,			 // 복사 받을 가로 길이
            (int)m_vSize.y,			 // 복사 받을 세로 길이
            hMemDC,					// 비트맵을 가지고 있는 dc
            Render_x,						// 출력할 비트맵의 시작 x좌표
            Render_y,						// 출력할 비트맵의 시작 y좌표
            (int)m_vSize.x,			// 출력할 비트맵의 가로 사이즈
            (int)m_vSize.y,			// 출력할 비트맵의 세로 사이즈
            RGB(0, 0, 255));	// 제거할 픽셀의 색상 값
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
