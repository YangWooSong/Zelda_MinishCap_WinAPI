#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include<iostream>
#include "KeyMgr.h"
#include "Inven.h"
#include "Camera.h"
#include "PlayerUI.h"
#include "SoundMgr.h"
CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	Insert_Bmp();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_INVEN, CAbstractFactory<CInven>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerUI>::Create());

	CSoundMgr::Get_Instance()->Initialize();

	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Inven(CObjMgr::Get_Instance()->Get_Inven() );
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_UI(CObjMgr::Get_Instance()->Get_UI());

	CSceneMgr::Get_Instance()->Scene_Change(SC_LOAD);

//콘솔 창 띄우기
//#ifdef _DEBUG
//
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//
//#endif // _DEBUG
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}



void CMainGame::Render()
{
	// FPS 출력

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Insert_Bmp()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Boss1_Map.bmp", L"SceneBoss1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Boss2_Map.bmp", L"SceneBoss2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon.bmp", L"SceneDungeon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/LinkHouse_Ceilling.bmp", L"SceneHouse_Ceilling");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon0.bmp", L"Dungeon0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon1.bmp", L"Dungeon1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon2.bmp", L"Dungeon2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon_Ver2.bmp", L"Dungeon_Ver2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon3.bmp", L"Dungeon3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon4.bmp", L"Dungeon4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon5.bmp", L"Dungeon5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon6.bmp", L"Dungeon6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon6.bmp", L"Dungeon6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/brazierOn.bmp", L"brazierOn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon_Obj_Water.bmp", L"Dungeon_Obj_Water");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon_MovingFloor.bmp", L"Dungeon_MovingFloor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Dungeon_Road.bmp", L"Dungeon_Road");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Town_0.bmp", L"Town_0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Town.bmp", L"Town");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Town_Wood.bmp", L"Town_Wood");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/TownMark.bmp", L"TownMark");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Shop_ver2.bmp", L"Shop_ver2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Boss1_Map2.bmp", L"Boss1_Map2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Ending_Credit.bmp", L"Ending_Credit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/Boss1.bmp", L"Boss1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/Boss1_Eye.bmp", L"Boss1_Eye");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/Boss1_Laser.bmp", L"Boss1_Laser");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/Boss1_Laser2.bmp", L"Boss1_Laser2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/BossExplosion.bmp", L"BossExplosion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss/Boss1_Bullet.bmp", L"Boss1_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dungeon_Monster.bmp", L"Dungeon_Monster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Shield.bmp", L"Monster_Shield");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Snake.bmp", L"Snake");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item.bmp", L"Item");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Button.bmp", L"Button");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Pot_Effect.bmp", L"Pot_Effect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/KeyRock.bmp", L"KeyRock");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Floor_Tile.bmp", L"Floor_Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Dungeon_MovingRock.bmp", L"Dungeon_MovingRock");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/FireBall.bmp", L"FireBall");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/brazier.bmp", L"brazier");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Dungeon_Door.bmp", L"Dungeon_Door");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Rupe.bmp", L"Rupe");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Down.bmp", L"Player_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Left.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Right.bmp", L"Player_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Up.bmp", L"Player_Up");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/Npc_Grandfather.bmp", L"Npc_Grandfather");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NPC_Store2.bmp", L"NPC_Store2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NPC_MiniGame2.bmp", L"NPC_MiniGame2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NPC_Quest.bmp", L"NPC_Quest");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NPC_OldMan.bmp", L"NPC_OldMan");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NPC_Ball.bmp", L"NPC_Ball");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/House_Text_01.bmp", L"House_Text_01");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/House_Text_02.bmp", L"House_Text_02");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Store_Text_01.bmp", L"Store_Text_01");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Number.bmp", L"Number");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/LinkHp.bmp", L"LinkHp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Key_UI.bmp", L"Key_UI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/GageBar_BackGround.bmp", L"GageBar_BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/GageBar_Bar.bmp", L"GageBar_Bar");
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CBmpMgr::Destroy();
	CSceneMgr::Destroy();
	CObjMgr::Destroy();
	CKeyMgr::Destroy();
	CCamera::Destroy();
	CSoundMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}

