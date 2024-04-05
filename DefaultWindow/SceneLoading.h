#pragma once
#include "Scene.h"
class CSceneLoading :
    public CScene
{
public:
    CSceneLoading();
    virtual ~CSceneLoading();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

