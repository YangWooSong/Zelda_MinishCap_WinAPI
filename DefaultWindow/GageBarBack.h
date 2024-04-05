#pragma once
#include "Obj.h"

class CGageBarBack :
    public CObj
{
public:
    CGageBarBack();
    virtual ~CGageBarBack();

public:
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    CObj* Get_bar() { return m_pGageBar; }
private:
    CObj* m_pGageBar;
};

