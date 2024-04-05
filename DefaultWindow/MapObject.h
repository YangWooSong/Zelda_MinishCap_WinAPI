#pragma once
#include "Obj.h"
class CMapObject :
    public CObj
{
public:
    CMapObject();
    virtual ~CMapObject();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void    Set_iNum(int _iN) { m_iNum = _iN; }
private:
    int     m_iNum;
    int     m_iRenderX;
    int     m_iRenderY;
    int     m_iFrameEnd;
};

