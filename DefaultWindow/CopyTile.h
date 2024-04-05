#pragma once
#include "Obj.h"
class CCopyTile :
    public CObj
{
public:
    CCopyTile();
    virtual ~CCopyTile();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    bool    Get_IsCopy() { return m_bCopy; }
    void    Set_IsCaopyFalse() { m_bCopy = false; }
    void OnCollisionEnter(CObj* _pOther);
    void OnCollisionExit(CObj* _pOther);

private:
    bool    m_bCopy;
};

