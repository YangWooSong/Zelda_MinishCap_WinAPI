#include "stdafx.h"
#include "KeyRock.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "SceneDungeon.h"
#include "Player.h"
#include "SoundMgr.h"
CKeyRock::CKeyRock() : m_bActive(true), m_pScene(nullptr)
{
}

CKeyRock::~CKeyRock()
{
    Release();
}

void CKeyRock::Initialize()
{
    m_pFrameKey = L"KeyRock";
    m_vSize = { 50, 50 };

    m_eRender = RENDER_BACKGROUND;
}

int CKeyRock::Update()
{
    if (m_bActive)
        Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
    else
        Set_Collider(0, 0, 0, 0);
    return 0;
}

void CKeyRock::Late_Update()
{
}

void CKeyRock::Render(HDC hDC)
{
    if (m_bActive)
    {
        HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
        m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

        BitBlt(hDC, m_vCameraPos.x - (m_vSize.x * 0.5f), m_vCameraPos.y - (m_vSize.y * 0.5f), m_vSize.x, m_vSize.y, hMemDC, 0, 0, SRCCOPY);

      //  RenderCollision(hDC);
    }
}

void CKeyRock::Release()
{
}

void CKeyRock::OnCollisionEnter(CObj* _pOther)
{
    if (dynamic_cast<CSceneDungeon*>(m_pScene)->Get_KeyCount() > 0)
    {
        dynamic_cast<CSceneDungeon*>(m_pScene)->Set_MinusKeyCount();
        CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
        CSoundMgr::Get_Instance()->PlaySoundW(L"MC_Link_Shield.wav", SOUND_EFFECT, 1.f);
        m_bActive = false;
    }

    float   fX(0.f), fY(0.f);
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

    if (pPlayer == nullptr)
        return;
    RECT intersect = {};

    if (::IntersectRect(&intersect, &pPlayer->Get_Collider(), &m_tCollider))
    {
        int w = intersect.right - intersect.left;
        int h = intersect.bottom - intersect.top;

        if (w > h)
        {
            if (intersect.top == m_tCollider.top)
            {
                // pPlayer->Set_PosY(-h + 1);
                pPlayer->Set_PosY(pPlayer->Get_Pos().y - h - 4);
            }
            else
            {
                // pPlayer->Set_PosY(h + 1);
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