#pragma once
#include "Obj.h"
class CStoreNPC :
    public CObj
{
public:
    CStoreNPC();
    virtual ~CStoreNPC();
public:
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Motion_Change();
};

