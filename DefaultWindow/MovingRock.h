#pragma once
#include "Obj.h"
class CMovingRock :
    public CObj
{
public:
    CMovingRock();
    virtual ~CMovingRock();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollisionStay(CObj* _pOther);

};

