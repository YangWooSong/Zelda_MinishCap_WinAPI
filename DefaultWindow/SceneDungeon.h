#pragma once
#include "Scene.h"
class CObj;
class CSceneDungeon :
    public CScene
{
public:
    CSceneDungeon();
    virtual ~CSceneDungeon();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void    Set_KeyCount() { m_iKeyCount++; }
    void    Set_DoorActiveFalse() { m_bActiveDoor = false; }
    void    Set_MinusKeyCount() { m_iKeyCount--; }
    int    Get_KeyCount() {   return m_iKeyCount; }
private:
    void Active_Door();
    void Active_LeftKey();
    void Active_RightKey();
    void Key_Input();
    void Activate_Monster();
private:
    bool    m_bBossScene;
    bool    m_bVillageScene;

    bool    m_bLeftKeyActive;
    bool    m_bRightKeyActive;

    bool    m_bActiveDoor;
    bool    m_bActiveShieldMonster;
    int     m_iKeyCount;

    list<CObj*> m_LeftButtonList;
    list<CObj*> m_RightButtonList;
    list<CObj*> m_BrazierList;
    vector<CObj*> m_CopyTileList;

    CObj* m_pLeftKey;
    CObj* m_pRightKey;
    CObj* m_pKeyRock1;      //입구 막는 열쇠 모양 돌
    CObj* m_pKeyRock2;      //입구 막는 열쇠 모양 돌
    CObj* m_pRoadButton;    //바닥 생성 버튼
    CObj* m_pMovingRock;    //밀리는 돌
    CObj* m_pRoad;          //생겼다 없어지는 바닥
    CObj* m_pMovingFloor;    //움직이는 바닥
    CObj* m_pDoor;    //중간 보스 문
    CObj* m_pSieldMonster;    //중간 보스 
    CObj*  m_pUI;

    VEC2    m_vCopyPos[2] = {};
    int     m_iPosCount;

    DWORD				m_dwTime;
  
};

