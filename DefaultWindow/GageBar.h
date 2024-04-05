#pragma once
#include "Obj.h"
class CGageBar :
    public CObj
{
public:
    CGageBar();
    virtual ~CGageBar();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_m_bChangeLength(bool _b) { m_bChangeLength = _b; }
    int Get_RenderLength() { return m_iRenderLength; }
    void  Set_RenderLength(int _i) { m_iRenderLength = _i; }
private:
    DWORD m_time;
    DWORD m_time2;
    int     m_iStart;
    bool    m_bChangeLength;
    int     m_iRenderLength;
};

