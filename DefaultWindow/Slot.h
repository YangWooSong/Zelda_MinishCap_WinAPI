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
    void    Set_Active(bool _b) { m_bItemGet = _b; }     //���� Ȱ��ȭ
    bool    Get_ItemGet() { return m_bItemGet; }       //������ ȹ�� ���� Ȯ��
 //   void    Set_Select() { m_bSelect = !m_bSelect; }
    void    Set_Select(bool _b) { m_bSelect = _b; }
    bool    Get_Select() { return m_bSelect; }
private:
    bool    m_bItemGet;     //������ ȹƯ ����
    bool    m_bSelect;      //â���� ������
    bool    m_bFinalSelect; //����
    ITEM_ID m_eItemId;      //���� ���� 
};

