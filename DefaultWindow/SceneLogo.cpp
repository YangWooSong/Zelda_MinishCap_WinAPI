#include "stdafx.h"
#include "SceneLogo.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
CSceneLogo::CSceneLogo()
{
}

CSceneLogo::~CSceneLogo()
{
	Release();
}

void CSceneLogo::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/LogoBack.bmp", L"Scene_Logo");
	CSoundMgr::Get_Instance()->PlaySoundW(L"01_Title_Screen.wav", SOUND_BGM,1.f);

	m_tFrame = { 0, 96, 0, 80, GetTickCount() };
	m_pFrameKey = L"Scene_Logo";
}

int CSceneLogo::Update()
{
	if (m_tFrame.iFrameStart >= 95)
		m_tFrame.iFrameStart = 90;

	return 0;
}

void CSceneLogo::Late_Update()
{
	if (CKeyMgr::Get_Instance()->GetKeySate(KEY::ENTER) == KEY_STATE::TAP)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_HOUSE);
		return;
	}

	__super::Move_Frame();
}

void CSceneLogo::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Scene_Logo");

	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	GdiTransparentBlt(hDC, // �������� �׸��� �׸� dc
		0, // ���� ���� ��ġ�� left
		0,			 // ���� ���� ��ġ�� top
		WINCX,			 // ���� ���� ���� ����
		WINCY,			 // ���� ���� ���� ����
		hMemDC,					// ��Ʈ���� ������ �ִ� dc
		m_tFrame.iFrameStart * WINCX,						// ����� ��Ʈ���� ���� x��ǥ
		m_tFrame.iMotion * WINCY,						// ����� ��Ʈ���� ���� y��ǥ
		WINCX,			// ����� ��Ʈ���� ���� ������
		WINCY,			// ����� ��Ʈ���� ���� ������
		NULL);	// ������ �ȼ��� ���� ��
}

void CSceneLogo::Release()
{
}
