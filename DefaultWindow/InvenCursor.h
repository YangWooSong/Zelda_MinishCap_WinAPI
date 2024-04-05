#pragma once
#include "Obj.h"
class CInvenCursor :
    public CObj
{
public:
    CInvenCursor();
    virtual ~CInvenCursor();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    void Move_Right();
    void Move_Left();
    void Move_Up();
    void Move_Down();
};

