#pragma once
#include "Obj.h"
class CPlayerBullet :
    public CObj
{
public:
    CPlayerBullet();
    virtual ~CPlayerBullet();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollisionEnter(CObj* _pOther);
public:
    void Motion_Change();
    
};

