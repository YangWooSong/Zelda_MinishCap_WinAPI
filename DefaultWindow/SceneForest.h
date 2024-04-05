#pragma once
#include "Scene.h"
class CObj;
class CSceneForest :
    public CScene
{
public:
    CSceneForest();
    virtual ~CSceneForest();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    CObj* m_pSnake;
};

