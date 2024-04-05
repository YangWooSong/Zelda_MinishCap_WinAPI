#pragma once
#include "Obj.h"
class CStoreNPC :
    public CObj
{
public:
    CStoreNPC();
    virtual ~CStoreNPC();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Motion_Change();
};

