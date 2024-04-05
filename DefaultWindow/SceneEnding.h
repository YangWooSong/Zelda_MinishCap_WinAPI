#pragma once
#include "Scene.h"
class CSceneEnding :
    public CScene
{
public:
    CSceneEnding();
    virtual ~CSceneEnding();

public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

