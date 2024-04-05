#pragma once
#include "Obj.h"
class CSlot :
    public CObj
{
public:
    CSlot();
    virtual ~CSlot();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:

    void    Set_ItemId(ITEM_ID    _id) { m_eItemId = _id; }
    ITEM_ID    Get_ItemId() { return m_eItemId; }
    void    Set_Active(bool _b) { m_bItemGet = _b; }     //슬롯 활성화
    bool    Get_ItemGet() { return m_bItemGet; }       //아이템 획득 유무 확인
 //   void    Set_Select() { m_bSelect = !m_bSelect; }
    void    Set_Select(bool _b) { m_bSelect = _b; }
    bool    Get_Select() { return m_bSelect; }
private:
    bool    m_bItemGet;     //아이템 획특 유무
    bool    m_bSelect;      //창에서 선택한
    bool    m_bFinalSelect; //장착
    ITEM_ID m_eItemId;      //무기 종류 
};

