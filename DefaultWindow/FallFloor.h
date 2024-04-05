#pragma once
#include "Obj.h"
class CFallFloor :
    public CObj
{
public:
    CFallFloor();
    virtual ~CFallFloor();
public:
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

};

