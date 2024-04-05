#pragma once
#include "Scene.h"
class CSceneStore :
    public CScene
{
public:
    CSceneStore();
    virtual ~CSceneStore();
public:
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

