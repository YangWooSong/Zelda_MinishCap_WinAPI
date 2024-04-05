#pragma once
#include "Scene.h"
class CSceneVillage :
    public CScene
{
public:
    CSceneVillage();
    virtual ~CSceneVillage();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    bool    m_bSceneDungeon;
    bool    m_bSceneStore;

};

