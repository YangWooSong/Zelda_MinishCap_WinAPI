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
    CObj* m_pKeyRock1;      //�Ա� ���� ���� ��� ��
    CObj* m_pKeyRock2;      //�Ա� ���� ���� ��� ��
    CObj* m_pRoadButton;    //�ٴ� ���� ��ư
    CObj* m_pMovingRock;    //�и��� ��
    CObj* m_pRoad;          //����� �������� �ٴ�
    CObj* m_pMovingFloor;    //�����̴� �ٴ�
    CObj* m_pDoor;    //�߰� ���� ��
    CObj* m_pSieldMonster;    //�߰� ���� 
    CObj*  m_pUI;

    VEC2    m_vCopyPos[2] = {};
    int     m_iPosCount;

    DWORD				m_dwTime;
  
};

