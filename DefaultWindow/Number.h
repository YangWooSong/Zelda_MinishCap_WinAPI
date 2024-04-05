#pragma once
#include "Obj.h"
class CNumber :
    public CObj
{
public:
    CNumber();
    virtual ~CNumber();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_Full(int _iNum) { m_iNum = _iNum; }
private:
    int m_iNum;
};

