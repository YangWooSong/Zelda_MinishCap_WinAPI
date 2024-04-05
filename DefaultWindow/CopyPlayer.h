#pragma once
#include "Player.h"
class CCopyPlayer :
    public CPlayer
{
public:
	CCopyPlayer();
	virtual ~CCopyPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual		void		Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void OnCollisionExit(CObj* _pOther);
	void OnCollisionStay(CObj* _pOther);
	void OnCollisionEnter(CObj* _pOther);
private:
	void		Key_Input();
	void		Motion_Change();
};

