#include "stdafx.h"
#include "NpcGrandfather.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "PlayerUI.h"
#include "SoundMgr.h"
CNpcGrandfather::CNpcGrandfather() : m_time(GetTickCount()), m_pPlayerUi(nullptr)
{
}

CNpcGrandfather::~CNpcGrandfather()
{
    Release();
}

void CNpcGrandfather::Initialize()
{
    m_eCurState = IDLE;
    m_tFrame = { 0, 0, 0, 0, GetTickCount(),false };
    m_pFrameKey = L"Npc_Grandfather";
    m_vSize = { 200.f,200.f };

	m_pPlayerUi = dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI());
    m_eRender = RENDER_GAMEOBJECT;
}

int CNpcGrandfather::Update()
{
	if (m_vPos.x - CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x < 195.f && m_pPlayerUi->Get_TextNum() <1)
	{
		if (m_ePreState == IDLE)
		{
			CSoundMgr::Get_Instance()->PlaySoundW(L"MC_Emote_Question.wav", SOUND_EFFECT, 1.f);
			m_eCurState = ATTACK;
			m_time = GetTickCount();
		}
		m_pPlayerUi->Set_TextActive(true);
	}

	if (m_pPlayerUi->Get_TextActive())
	{
		if (m_time + 3000 < GetTickCount())
		{
			if (m_pPlayerUi->Get_TextNum() < 1)
			{
				m_pPlayerUi->Plus_TextNum();
				m_time = GetTickCount();
			}
			else
			{
				m_pPlayerUi->Set_TextActive(false);
				m_eCurState = IDLE;
			}
		}
	}
    return OBJ_NOEVENT;
}

void CNpcGrandfather::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, 160.f, 160.f);
    Motion_Change();
    __super::Move_Frame();
}

void CNpcGrandfather::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
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
		RGB(128, 128, 128));	// ������ �ȼ��� ���� ��

	//RenderCollision(hDC);
}

void CNpcGrandfather::Release()
{
}

void CNpcGrandfather::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;

		case ATTACK:
			m_tFrame.iFrameStart =0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200.f;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.bIsPlayDone = false;
			break;
		}
		m_ePreState = m_eCurState;
	}
}
