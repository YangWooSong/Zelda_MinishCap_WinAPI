#pragma once
#include "Scene.h"
class CObj;
class CSceneHouse :
    public CScene
{
public:
    CSceneHouse();
    virtual ~CSceneHouse();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_SwordActive();
private:
    int m_iSowrdActiveCount;
    CObj* m_pSword;
};

