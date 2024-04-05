#include "stdafx.h"
#include "StoreBox.h"
#include "Player.h"
#include "PlayerUI.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Inven.h"
#include "Slot.h"
#include "Weapon.h"
CStoreBox::CStoreBox() : m_bButItem(true), m_pItem(nullptr), m_eITemId(ITEM_END)
{
}

CStoreBox::~CStoreBox()
{
    Release();
}

void CStoreBox::Initialize()
{
    m_vSize = { 50.f,70.f };
	dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Set_TextNum(2);
}

int CStoreBox::Update()
{
	if (!m_bButItem)
	{
		return OBJ_DEAD;
	}
		
    return 0;
}

void CStoreBox::Late_Update()
{
    Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
    m_eRender = RENDER_GAMEOBJECT;
}

void CStoreBox::Render(HDC hDC)
{
	int Render_x = 0;
	int Render_y = 0;

	switch (m_eITemId)
	{
	case ITEM_WAND:
		Render_x = 0;
		break;
	case ITEM_POT:
		Render_x = 60;
		break;
	default:
		break;
	}

	if (m_bButItem)
	{
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Item");
		m_vCameraPos = CCamera::Get_Instance()->GetRenderPos(m_vPos);

		GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
			(int)(m_vCameraPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
			(int)(m_vCameraPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
			60,			 // ���� ���� ���� ����
			60,			 // ���� ���� ���� ����
			hMemDC,					// ��Ʈ���� ������ �ִ� dc
			Render_x,						// ����� ��Ʈ���� ���� x��ǥ
			Render_y,						// ����� ��Ʈ���� ���� y��ǥ
			60,			// ����� ��Ʈ���� ���� ������
			60,			// ����� ��Ʈ���� ���� ������
			RGB(0, 0, 255));	// ������ �ȼ��� ���� ��

	//	RenderCollision(hDC);
	}

}

void CStoreBox::Release()
{
}


void CStoreBox::OnCollisionEnter(CObj* _pOther)
{
    if (dynamic_cast<CPlayer*>(_pOther) && m_bButItem)
    {
        dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Set_TextActive(true);
		KeyInput();
    }
       
}

void CStoreBox::OnCollisionStay(CObj* _pOther)
{
	if (dynamic_cast<CPlayer*>(_pOther) && m_bButItem)
	{
		KeyInput();
	}

}
void CStoreBox::OnCollisionExit(CObj* _pOther)
{
    dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Set_TextActive(false);
}

void CStoreBox::KeyInput()
{
    if (CKeyMgr::Get_Instance()->GetKeySate(KEY::Y) == KEY_STATE::TAP)
    {
        m_bButItem = false;
        dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Set_TextActive(false);
        dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Rupe(-100);
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
        CSoundMgr::Get_Instance()->PlaySoundW(L"MC_Rupee.wav",SOUND_EFFECT,1.0f);
		
		dynamic_cast<CInven*>(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Inven())->Set_SlotActive(m_eITemId);
			
    }
    else if (CKeyMgr::Get_Instance()->GetKeySate(KEY::N) == KEY_STATE::TAP)
    {
        dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Set_TextActive(false);
      
    }

}
