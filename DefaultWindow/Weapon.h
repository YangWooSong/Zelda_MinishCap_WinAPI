#pragma once
#include "Obj.h"
class CWeapon :
    public CObj
{
public:

    CWeapon();
    CWeapon(ITEM_ID _id, VEC2 _v );
    virtual ~CWeapon();

public:

    // CObj을(를) 통해 상속됨
    void Initialize() override;

    int Update() override;

    void Late_Update() override;

    void Render(HDC hDC) override;

    void Release() override;

    void OnCollisionEnter(CObj* _pOther);

    void Set_ItemId(ITEM_ID _id) { m_eItemId = _id; }
    
    void Set_Render(bool _b) { m_bRender = _b; }
public:
    ITEM_ID Get_ITEMID() { return m_eItemId; }

private:
    ITEM_ID     m_eItemId;
    bool        m_bRender;
};

