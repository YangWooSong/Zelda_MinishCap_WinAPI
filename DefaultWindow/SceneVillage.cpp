#include "stdafx.h"
#include "SceneVillage.h"
#include "SoundMgr.h"
#include "Wall.h"
#include "Door.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CCeilling.h"
#include "SceneMgr.h"
#include "MiniGameNPC.h"
#include "OldManNPC.h"
#include "BallNPC.h"
CSceneVillage::CSceneVillage() : m_bSceneDungeon(false), m_bSceneStore(false)
{
}

CSceneVillage::~CSceneVillage()
{
    Release();
}

void CSceneVillage::Initialize()
{
    //플레이어 세팅
	if (CSceneMgr::Get_Instance()->Get_PreScene() == SC_STORE)
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1223.f, 2300.f);
	else
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1512.f, 2764.f);

    CObjMgr::Get_Instance()->Get_Player()->Set_Size(200.f, 200.f);

    //포탈
    CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDoor>::Create(1507.f, 48.f, 144.f, 94.f, ITEM_Door, &m_bSceneDungeon));
    CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDoor>::Create(1223.f, 2226.f, 80.f, 35.f, ITEM_Door, &m_bSceneStore));

    //천장 
    CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(1296.f, 2520.f, SC_VILLAGE,0));
    CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(1320.f, 2066.f, SC_VILLAGE,1));
    CObjMgr::Get_Instance()->Add_Object(OBJ_CEILLING, CAbstractFactory<CCeilling>::Create(1354.f, 765.f, SC_VILLAGE,2));


	//npc
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CMiniGameNPC>::Create(1632.f, 1500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<COldManNPC>::Create(1390.f, 1500.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CBallNPC>::Create(1390.f, 1730.f));

    //카메라
    CCamera::Get_Instance()->SetLookAtPos(1512.f, 2635.f);
    CCamera::Get_Instance()->SetMaxPos(VEC2(2659.f, 2639.f));
    CCamera::Get_Instance()->SetMinPos(VEC2(360.f, 241.f));
    CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());
}

int CSceneVillage::Update()
{
    CObjMgr::Get_Instance()->Update();
    CCamera::Get_Instance()->Update();

	//씬 전환
	if (m_bSceneDungeon )	    //씬 넘어가기
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

		CSceneMgr::Get_Instance()->Scene_Change(SC_DUNGEON);
		return 0;
	}
	if (m_bSceneStore)	    //씬 넘어가기
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

		CSceneMgr::Get_Instance()->Scene_Change(SC_STORE);

		return 0;
	}
    return 0;
}

void CSceneVillage::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();

}

void CSceneVillage::Render(HDC hDC)
{
    VEC2 vTemp = { 0,0 };
    m_vCameraRenderPos = CCamera::Get_Instance()->GetRenderPos(vTemp);
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Town");

    BitBlt(hDC, m_vCameraRenderPos.x, m_vCameraRenderPos.y, 3024, 2880, hMemDC, 0, 0, SRCCOPY);

    CObjMgr::Get_Instance()->Render(hDC);
    CCamera::Get_Instance()->Render(hDC);
}

void CSceneVillage::Release()
{
}
