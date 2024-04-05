#pragma once
#include "Monster.h"
class CBossFireBall :
    public CMonster
{
public:
    CBossFireBall();
    virtual ~CBossFireBall();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    void Motion_Change();
};

