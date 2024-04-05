#pragma once
#include "Obj.h"
class CStoreBox :
    public CObj
{
public:
    CStoreBox();
    virtual ~CStoreBox();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void OnCollisionEnter(CObj* _pOther);
    void OnCollisionExit(CObj* _pOther);
    void OnCollisionStay(CObj* _pOther);

public:
    void Set_Item(ITEM_ID _i) { m_eITemId = _i; }
private:
    void KeyInput();

private:
    ITEM_ID m_eITemId;
    bool m_bButItem;
    CObj* m_pItem;
};

