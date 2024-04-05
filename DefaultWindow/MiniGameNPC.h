#pragma once
#include "Obj.h"
class CMiniGameNPC :
    public CObj
{
public:
    CMiniGameNPC();
    virtual ~CMiniGameNPC();
public:
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Motion_Change();
};

