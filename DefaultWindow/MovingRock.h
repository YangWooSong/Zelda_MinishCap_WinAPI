#pragma once
#include "Obj.h"
class CMovingRock :
    public CObj
{
public:
    CMovingRock();
    virtual ~CMovingRock();
public:
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void OnCollisionStay(CObj* _pOther);

};

