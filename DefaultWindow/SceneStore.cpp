#include "stdafx.h"
#include "SceneStore.h"
#include "Camera.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Wall.h"
#include "AbstractFactory.h"
#include "Door.h"
#include "SceneMgr.h"
#include "StoreBox.h"
#include "StoreNPC.h"

CSceneStore::CSceneStore()
{
}

CSceneStore::~CSceneStore()
{
    Release();
}

void CSceneStore::Initialize()
{
    //플레이어
    CObjMgr::Get_Instance()->Get_Player()->Set_Pos(370.f, 427.f);
    CObjMgr::Get_Instance()->Get_Player()->Set_Size(200.f, 200.f);

    //벽
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(50.f, 287, 95.f, 570.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(705.f, 287, 95.f, 570.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(250.f, 287, 246.f, 72.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(353.f, 200, 47.f, 104.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(372.f, 58, 553.f, 120.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(615.f, 149, 71.f, 48.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(615.f, 149, 71.f, 48.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(212.f, 416, 175.f, 92.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(530.f, 535, 229.f, 103.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(215.f, 523, 248.f, 103.f));

    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(493.f, 254, 50.f, 60.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(595.f, 254, 50.f, 60.f));

    //포탈
    CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDoor>::Create(371.f, 512.f, 60.f, 52.f, ITEM_Door, &m_bSceneChange));

    //상자
    CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStoreBox>::Create(495.f, 254.f, ITEM_WAND));
    CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStoreBox>::Create(596.f, 254.f, ITEM_POT));
   
    //NPC
    CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CStoreNPC>::Create(240.f, 241.f));

    //카메라
    CCamera::Get_Instance()->SetLookAtPos(392.f, 324.f);
    CCamera::Get_Instance()->SetMaxPos(VEC2(392.f, 324.f));
    CCamera::Get_Instance()->SetMinPos(VEC2(360.f, 240.f));
    CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());
}

int CSceneStore::Update()
{
    CObjMgr::Get_Instance()->Update();
    CCamera::Get_Instance()->Update();

    //씬 넘어가기
    if (m_bSceneChange)
    {
        list<CObj*>* list = CObjMgr::Get_Instance()->Get_ObjList();

        for (size_t i = OBJ_WALL; i < OBJ_ITEM; ++i)
        {
            for (auto iter = list[i].begin();
                iter != list[i].end(); )
            {
                int		iResult = (*iter)->Update();

                Safe_Delete<CObj*>(*iter);
                iter = list[i].erase(iter);

            }
        }

        CSceneMgr::Get_Instance()->Scene_Change(SC_VILLAGE);
    }

    return 0;
}

void CSceneStore::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
}

void CSceneStore::Render(HDC hDC)
{
    VEC2 vTemp = { 0,0 };
    m_vCameraRenderPos = CCamera::Get_Instance()->GetRenderPos(vTemp);
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shop_ver2");

    BitBlt(hDC, m_vCameraRenderPos.x, m_vCameraRenderPos.y,750, 575, hMemDC, 0, 0, SRCCOPY);


    CObjMgr::Get_Instance()->Render(hDC);
    CCamera::Get_Instance()->Render(hDC);
}

void CSceneStore::Release()
{
}
