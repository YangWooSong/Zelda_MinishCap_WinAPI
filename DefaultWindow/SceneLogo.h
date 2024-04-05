#pragma once
#include "Scene.h"

class CSceneLogo :
    public CScene
{
public:
    CSceneLogo();
    virtual ~CSceneLogo();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

