#pragma once
#include "Obj.h"
class CButton :
    public CObj
{
public:
    CButton();
    virtual ~CButton();
public:
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

public:
   bool  Get_Active() { return m_bActive; }
public:
    void OnCollisionEnter(CObj* _pOther);
    void OnCollisionExit(CObj* _pOther);
private:
    bool    m_bActive;
};

