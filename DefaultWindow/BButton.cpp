#include "stdafx.h"
#include "BButton.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Inven.h"
#include "UIWeapon.h"
#include "Inven.h"

CBButton::CBButton() : m_eObjId(ITEM_END), m_pWeapon(nullptr), m_pPlayer(nullptr)
{
}

CBButton::CBButton(float _x, float _y) : m_eObjId(ITEM_END), m_pWeapon(nullptr), m_pPlayer(nullptr)
{
	m_vPos = { _x,_y };
	m_vSize = {36.f,42.f};
}

CBButton::~CBButton()
{
	Release();
}

void CBButton::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Use1.bmp", L"Use1");
	m_eRender = RENDER_UI;
	m_pFrameKey = L"Use1";

	//Inven�� B ������ �ҷ�����
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_pWeapon = new CUIWeapon(m_eObjId, VEC2(m_vPos.x - 50.f, m_vPos.y - 40.f));
}

int CBButton::Update()
{
	m_eObjId = dynamic_cast<CInven*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inven())->Get_BItem();

	dynamic_cast<CUIWeapon*>(m_pWeapon)->Set_ItemId(m_eObjId);
	return 0;
}

void CBButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		(int)(m_vPos.x - m_vSize.x * 0.5f), // ���� ���� ��ġ�� left
		(int)(m_vPos.y - m_vSize.y * 0.5f),			 // ���� ���� ��ġ�� top
		(int)m_vSize.x,			 // ���� ���� ���� ����
		(int)m_vSize.y,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		0,						// ����� ��Ʈ���� ���� x��ǥ
		0,						// ����� ��Ʈ���� ���� y��ǥ
		(int)m_vSize.x,		// ����� ��Ʈ���� ���� ������
		(int)m_vSize.y,					// ����� ��Ʈ���� ���� ������
		RGB(255, 0, 255));	// ������ �ȼ��� ���� ��


	m_pWeapon->Render(hDC);
}

void CBButton::Release()
{
	Safe_Delete(m_pWeapon);
}
