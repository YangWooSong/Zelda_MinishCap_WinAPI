#pragma once
#include "Obj.h"
class CUIWeapon :
    public CObj
{
public:

    CUIWeapon();
    CUIWeapon(ITEM_ID _id, VEC2 _v);
    virtual ~CUIWeapon();

public:


    // CObj을(를) 통해 상속됨
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

    void OnCollisionEnter(CObj* _pOther);

    void Set_ItemId(ITEM_ID _id) { m_eItemId = _id; }

private:
    ITEM_ID     m_eItemId;
    bool        m_bRender;

};

