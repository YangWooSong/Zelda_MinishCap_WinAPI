#pragma once
#include "Scene.h"
class CSceneEnding :
    public CScene
{
public:
    CSceneEnding();
    virtual ~CSceneEnding();

public:
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

