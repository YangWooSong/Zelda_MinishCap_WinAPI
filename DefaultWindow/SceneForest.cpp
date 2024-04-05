#include "stdafx.h"
#include "SceneForest.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Weapon.h"
#include "Snake.h"
#include "SoundMgr.h"
#include "Wall.h"
#include "Door.h"
CSceneForest::CSceneForest() : m_pSnake(nullptr)
{
}

CSceneForest::~CSceneForest()
{
    Release();
}

void CSceneForest::Initialize()
{
    //플레이어 세팅
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene/Forest.bmp", L"SceneForest");
    CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1990.f, 1263.f);
    CObjMgr::Get_Instance()->Get_Player()->Set_Size(200.f, 200.f);

    //몬스터
    m_pSnake = CAbstractFactory<CSnake>::Create(1400.f, 1200.f);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pSnake);
    dynamic_cast<CSnake*>( m_pSnake)->Set_Dirint(1);

    //벽
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1672.f, 1256.f, 50.f, 578.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1754.f, 1212.f, 107.f, 95.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1857.f, 1175.f, 71.f, 62.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(2069.f, 1106.f, 328.f, 210.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(2069.f, 1106.f, 328.f, 210.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1986.f, 1221.f, 93.f, 18.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(2292.f, 1250.f, 71.f, 576.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1817.f, 1508.f, 238.f, 83.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(2150.f, 1483.f, 210.f, 141.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1930.f, 1412.f, 12.f, 104.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(2047.f, 1382.f, 16.f, 45.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1304.f, 1746.f, 194.f, 189.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(2309.f, 1622.f, 340.f, 145.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1107.f, 1582.f, 480.f, 145.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(964.f, 1428.f, 201.f, 160.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1972.f, 987.f, 558.f, 44.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(964.f, 999.f, 484.f, 170.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(820.f, 1216.f, 196.f, 260.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1151.f, 849.f, 196.f, 166.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1306.f, 646.f, 185.f, 343.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1756.f, 576.f, 227.f, 182.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1308.f, 108.f, 227.f, 182.f));
    CObjMgr::Get_Instance()->Add_Object(OBJ_WALL, CAbstractFactory<CWall>::Create(1744.f, 115.f, 194.f, 232.f));

    //포탈
    CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDoor>::Create(1530.f, 55.f, 235.f, 111.f, ITEM_Door, &m_bSceneChange));

    //카메라
    CCamera::Get_Instance()->SetLookAtPos(1990.f, 1263.f);
    CCamera::Get_Instance()->SetMaxPos(VEC2(2700.f, 1875.f));
    CCamera::Get_Instance()->SetMinPos(VEC2(360.f, 240.f));
    CCamera::Get_Instance()->SetTarget(CObjMgr::Get_Instance()->Get_Player());

    CSoundMgr::Get_Instance()->StopAll();
    CSoundMgr::Get_Instance()->PlayBGM(L"05-Festival-Outskirts.wav", 1.0f);
}

int CSceneForest::Update()
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

void CSceneForest::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
}

void CSceneForest::Render(HDC hDC)
{
    VEC2 vTemp = { 0,0 };
    m_vCameraRenderPos = CCamera::Get_Instance()->GetRenderPos(vTemp);
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SceneForest");

    BitBlt(hDC,(int) m_vCameraRenderPos.x, (int)m_vCameraRenderPos.y, 3060, 2080, hMemDC, 0, 0, SRCCOPY);


    CObjMgr::Get_Instance()->Render(hDC);
    CCamera::Get_Instance()->Render(hDC);

}

void CSceneForest::Release()
{
}
