#pragma once

#include "Obj.h"

class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual		void		Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	CObj* Get_Inven() 
	{ 
		if(m_pInven) 
			return  m_pInven; 
	}
	void		Set_Inven(CObj* _pInven) { m_pInven = _pInven; }
	void		Set_UI(CObj* _pUI) { m_pUI = _pUI; }
	int			Get_DefaultHp() { return  m_iDefaultHp; }
	int			Get_CurHp() { return  m_iCurHp; }
	int			Get_Rupe() { return  m_iRupe; }
	void		Set_Rupe(int _i) { m_iRupe += _i; }
	void		Set_DefaultHp(int _iHp) {  m_iDefaultHp += _iHp; }
	void		Set_CurHp(int _iHp) { m_iCurHp += _iHp; }
	void		Set_Hit(bool _b) { m_bHit = _b; }
	bool		Get_InvenActive() { return m_bInvenActive; }

	void OnCollisionExit(CObj* _pOther) override;
	void OnCollisionStay(CObj* _pOther) override;
	void OnCollisionEnter(CObj* _pOther) override;

	ITEM_ID Get_ITEMID() { return m_eCurItem; }
private:
	void		Key_Input();
	void		Motion_Change();
	void	Play_Sound();
	void	Shoot_Fire();

private:
	DWORD				m_dwTime;
	bool				m_bInvenActive;
	bool				m_bHit;
	int					m_iDefaultHp;
	int					m_iCurHp;
	int					m_iRupe;
	ITEM_ID				m_eAItem;
	ITEM_ID				m_eBItem;
	ITEM_ID				m_eCurItem;

	CObj* m_pInven;
	CObj* m_pUI;
	CObj* m_pItemCollider;
	CObj* m_pItemEffect;
};

