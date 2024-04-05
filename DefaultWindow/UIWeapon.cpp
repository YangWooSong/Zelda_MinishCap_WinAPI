#include "stdafx.h"
#include "UIWeapon.h"
#include "BmpMgr.h"

CUIWeapon::CUIWeapon()
{
}

CUIWeapon::CUIWeapon(ITEM_ID _id, VEC2 _v)
{
    m_eItemId = _id;
    m_vPos = _v;
}

CUIWeapon::~CUIWeapon()
{
}

void CUIWeapon::Initialize()
{
    m_eRender = RENDER_UI;
}

int CUIWeapon::Update()
{
    return 0;
}

void CUIWeapon::Late_Update()
{
}

void CUIWeapon::Render(HDC hDC)
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
		Render_x = 300;
		break;
	}
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Item");

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		m_vPos.x - m_vSize.x * 0.5f, // ���� ���� ��ġ�� left
		m_vPos.y - m_vSize.y * 0.5f,			 // ���� ���� ��ġ�� top
		60,			 // ���� ���� ���� ����
		60,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		Render_x,						// ����� ��Ʈ���� ���� x��ǥ
		Render_y,						// ����� ��Ʈ���� ���� y��ǥ
		60,			// ����� ��Ʈ���� ���� ������
		60,			// ����� ��Ʈ���� ���� ������
		RGB(0, 0, 255));	// ������ �ȼ��� ���� ��
}

void CUIWeapon::Release()
{
}

void CUIWeapon::OnCollisionEnter(CObj* _pOther)
{
}
