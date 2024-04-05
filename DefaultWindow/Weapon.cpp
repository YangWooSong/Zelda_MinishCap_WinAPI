#include "stdafx.h"
#include "Weapon.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Player.h"
#include "Inven.h"
#include "SoundMgr.h"
#include "ObjMgr.h"

CWeapon::CWeapon() : m_bRender(false)
{
}

CWeapon::CWeapon(ITEM_ID _id, VEC2 _v) : m_bRender(true)
{
	m_eItemId = _id;
	m_vPos = _v;
}

CWeapon::~CWeapon()
{
}

void CWeapon::Initialize()
{
    m_eRender = RENDER_EFFECT;
}

int CWeapon::Update()
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_CurState() == ITEM_GET)
	{
		m_vPos.x = CObjMgr::Get_Instance()->Get_Player()->Get_Pos().x;
		m_vPos.y = CObjMgr::Get_Instance()->Get_Player()->Get_Pos().y-40.f;
	}

	if (m_bDead)
		return OBJ_DEAD;
    return 0;
}

void CWeapon::Late_Update()
{
	if(m_bRender)
		Set_Collider(m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void CWeapon::Render(HDC hDC)
{
	int Render_x = 0;
	int Render_y = 0;

	switch (m_eItemId)
	{
	case ITEM_SWORD:
		Render_x = 180;
		break;
	case ITEM_BOW:
		Render_x = 120;
		break;
	case ITEM_SHIELD:
		Render_x = 240;
		break;
	case ITEM_WAND:
		Render_x = 0;
		break;
	case ITEM_POT:
		Render_x = 60;
		break;
	default:
		break;
	}

	if (m_bRender)
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
	}
	
	//RenderCollision(hDC);
}

void CWeapon:: OnCollisionEnter(CObj* _pOther)
{
	float   fX(0.f), fY(0.f);
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther);

	if (pPlayer == nullptr)
		return;
	RECT intersect = {};

	if (::IntersectRect(&intersect, &pPlayer->Get_Collider(), &m_tCollider))
	{
		CSoundMgr::Get_Instance()->PlaySoundW(L"58-Get-Item.wav", SOUND_GET_ITEM,1.0f);
		dynamic_cast<CInven*>(pPlayer->Get_Inven())->Set_SlotActive(m_eItemId);
	}
}

void CWeapon::Release()
{
}
