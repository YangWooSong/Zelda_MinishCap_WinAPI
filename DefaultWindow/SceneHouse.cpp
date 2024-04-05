#include "stdafx.h"
#include "BmpMgr.h"
#include "SceneHouse.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Wall.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "Door.h"
#include "CCeilling.h"
#include "Weapon.h"
#include "SoundMgr.h"
#include "NpcGrandfather.h"
#include "PlayerUI.h"

CSceneHouse::CSceneHouse() : m_pSword(nullptr), m_iSowrdActiveCount(0)
{
}
CSceneHouse::~CSceneHouse()
{
	Release();
}
void CSceneHouse::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/LinkHouse2.bmp", L"SceneHouse");
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(360.f, 245.f);
	CObjMgr::Get_Instance()->Get_Player()->Set_Size(200.f, 200.f);

	//벽
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(60.f,200.f,90.f,500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(800.f, 130.f,  200.f, 240.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(800.f, 440.f, 200.f, 240.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1540.f, 200.f, 90.f, 500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(800.f, 48.f, 1500.f, 100.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(205.f, 467.f, 310.f, 80.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(980.f, 467.f, 1100.f, 80.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(445.f, 200.f, 120.f, 80.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(360.f, 195.f, 45.f, 45.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(555.f, 122.f, 240, 70.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1315.f, 125.f, 400.f, 70.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1387.f, 347.f, 150.f, 50.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1365.f, 282.f, 50.f, 50.f));

	//포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDoor>::Create(400.f, 430.f, 50.f, 50.f , ITEM_Door, &m_bSceneChange));

	//테스트용 아이템 드랍
	/*
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CWeapon>::Create(1075.f, 280.f, 60.f, 60.f, ITEM_BOW));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CWeapon>::Create(1175.f, 380.f, 60.f, 60.f, ITEM_WAND));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CWeapon>::Create(1075.f, 380.f, 60.f, 60.f, ITEM_SHIELD));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CWeapon>::Create(1075.f, 180.f, 60.f, 60.f, ITEM_POT));*/
	m_pSword = CAbstractFactory<CWeapon>::Create(1345.f, 280.f, 60.f, 60.f, ITEM_SWORD);
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, m_pSword);
	dynamic_cast<CWeapon*>(m_pSword)->Set_Render(false);

	CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(745.f, 240.f, SC_HOUSE,0));

	CCamera::Get_Instance()->SetLookAtPos(360.f,240.f  );
	CCamera::Get_Instance()->SetMaxPos(VEC2(1252.f, 292.5));
	CCamera::Get_Instance()->SetMinPos(VEC2(360.f, 230.f));
	CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());

	//NPC
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNpcGrandfather>::Create(1420.f, 318.f));

	//소리
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"04-Princess-Zelda.wav", 1.f);

	m_eRender = RENDER_BACKGROUND;
}

int CSceneHouse::Update()
{
	CObjMgr::Get_Instance()->Update();
	CCamera::Get_Instance()->Update();

	if (m_bSceneChange)	    //씬 넘어가기
	{
		list<CObj*>* list = CObjMgr::Get_Instance()->Get_ObjList();

		for (size_t i = OBJ_WALL; i <= OBJ_ITEM; ++i)
		{
			for (auto iter = list[i].begin();
				iter != list[i].end(); )
			{
				Safe_Delete<CObj*>(*iter);
				iter = list[i].erase(iter);
			}
		}

		CSceneMgr::Get_Instance()->Scene_Change(SC_FOREST);
	}

	if(m_iSowrdActiveCount == 0)
		Set_SwordActive();

	return 0;
}

void CSceneHouse::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CSceneHouse::Render(HDC hDC)
{
	VEC2 vTemp = { 0,0 };
	m_vCameraRenderPos = CCamera::Get_Instance()->GetRenderPos(vTemp);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SceneHouse");

	BitBlt(hDC, m_vCameraRenderPos.x, m_vCameraRenderPos.y, 1600, 533, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	CCamera::Get_Instance()->Render(hDC);
}

void CSceneHouse::Release()
{
}

void CSceneHouse::Set_SwordActive()
{
	if(dynamic_cast<CPlayerUI*>(CObjMgr::Get_Instance()->Get_UI())->Get_TextNum() == 1)
	{
		dynamic_cast<CWeapon*>(m_pSword)->Set_Render(true);
		m_iSowrdActiveCount++;
	}
}
