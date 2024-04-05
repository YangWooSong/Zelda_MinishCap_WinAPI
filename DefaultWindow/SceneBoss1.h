#pragma once
#include "Scene.h"
class CObj;

class CSceneBoss1 :
    public CScene
{
public:
    CSceneBoss1();
    virtual ~CSceneBoss1();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Set_DoorActive(bool _b) { m_bDoorActive = _b; }
private:
    CObj*   m_pBoss;
    CObj*   m_pDoor;
    bool    m_bDoorActive;
};

