#pragma once
#include "Obj.h"
class CBallNPC :
    public CObj
{
public:
    CBallNPC();
    virtual ~CBallNPC();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Motion_Change();
};

