#include "stdafx.h"
#include "MovingRock.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Player.h"
#include "SoundMgr.h"

CMovingRock::CMovingRock() 
{
}

CMovingRock::~CMovingRock()
{
}

void CMovingRock::Initialize()
{
	m_pFrameKey = L"Dungeon_MovingRock";
	m_vSize = { 50, 50 };

	m_eRender = RENDER_BACKGROUND;
}

int CMovingRock::Update()
{
	return 0;
}

void CMovingRock::Late_Update()
{
	Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void CMovingRock::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

	BitBlt(hDC, m_vCameraPos.x - (m_vSize.x * 0.5f), m_vCameraPos.y - (m_vSize.y * 0.5f), m_vSize.x, m_vSize.y, hMemDC, 0, 0, SRCCOPY);
}

void CMovingRock::Release()
{
}


void CMovingRock::OnCollisionStay(CObj* _pOther)
{
    float   fX(0.f), fY(0.f);
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

    if (pPlayer == nullptr)
        return;
    RECT intersect = {};

    if (::IntersectRect(&intersect, &pPlayer->Get_Collider(), &m_tCollider))
    {
        int w = intersect.right - intersect.left;
        int h = intersect.bottom - intersect.top;
        CSoundMgr::Get_Instance()->PlaySoundW(L"move object.wav", SOUND_EFFECT, 1.f);
        if (w > h)
        {
            if (intersect.top == m_tCollider.top)
            {
                m_vPos.y += h;
            }
            else
            {
                m_vPos.y -= h;
            }
        }
        else
        {
            if (intersect.left == m_tCollider.left)
            {

                m_vPos.x += w;

            }
            else
            {
                m_vPos.x -= w;
            }
        }

    }
}