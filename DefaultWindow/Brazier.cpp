#include "stdafx.h"
#include "Brazier.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Player.h"
#include "SoundMgr.h"

CBrazier::CBrazier() : m_bActive(false)
{
}

CBrazier::~CBrazier()
{
    Release();
}

void CBrazier::Initialize()
{
    m_pFrameKey = L"brazier";
    m_vSize = { 48, 48 };
    m_eCurState = IDLE;

    m_eRender = RENDER_BACKGROUND;
}

int CBrazier::Update()
{
    return 0;
}

void CBrazier::Late_Update()
{
    if (m_bActive)
    {
        if (m_ePreState != m_eCurState)
        {
            m_pFrameKey = L"brazierOn";
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwSpeed = 100;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.bIsPlayDone = false;
        }
        m_ePreState = m_eCurState;
    }
    Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);

    __super::Move_Frame();
}

void CBrazier::Render(HDC hDC)
{

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
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
        RGB(185, 185, 185));	// 제거할 픽셀의 색상 값

	//RenderCollision(hDC);
}

void CBrazier::Release()
{
}

void CBrazier::OnCollisionEnter(CObj* _pOther)
{
    float   fX(0.f), fY(0.f);
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

    if (pPlayer == nullptr)
    {
        CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
        CSoundMgr::Get_Instance()->PlaySound(L"MC_FlameLantern_On.wav", SOUND_EFFECT, 1.f);
        m_bActive = true;

    }
    else
    {
        RECT intersect = {};

        if (::IntersectRect(&intersect, &pPlayer->Get_Collider(), &m_tCollider))
        {
            int w = intersect.right - intersect.left;
            int h = intersect.bottom - intersect.top;

            if (w > h)
            {
                if (intersect.top == m_tCollider.top)
                {
                    pPlayer->Set_PosY(pPlayer->Get_Pos().y - h - 4);
                }
                else
                {
                    pPlayer->Set_PosY(pPlayer->Get_Pos().y + h + 4);
                }
            }
            else
            {
                if (intersect.left == m_tCollider.left)
                {

                    pPlayer->Set_PosX(pPlayer->Get_Pos().x - w - 4);

                }
                else
                {
                    pPlayer->Set_PosX(w + pPlayer->Get_Pos().x + 4);
                }
            }

        }
    }
}
