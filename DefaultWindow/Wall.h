#pragma once
#include "Obj.h"
class CWall :
    public CObj
{
public:
    CWall();
    virtual ~CWall();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollisionExit(CObj* _pOther)override;
    void OnCollisionStay(CObj* _pOther) override;
    void OnCollisionEnter(CObj* _pOther);
};

