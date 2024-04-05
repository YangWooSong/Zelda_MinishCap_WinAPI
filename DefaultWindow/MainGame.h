#pragma once

#include "Define.h"

#include "Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();		
	void		Render();		
	void		Release();
	void		Late_Update();

private:
	void Insert_Bmp();
private:
	CObj*		m_pPlayer;
	HDC			m_hDC;

	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];
};

