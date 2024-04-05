#pragma once
#include "Obj.h"
class CUI_HP :
    public CObj
{
public:
    CUI_HP();
    virtual ~CUI_HP();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_Full(bool _bFull) { m_bFull = _bFull; }
    void Set_FullCount(int _icount) { m_iFullCount = _icount; }

private:
    bool        m_bFull;
    int         m_iFullCount;
 
};

