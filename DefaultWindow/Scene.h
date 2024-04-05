#pragma once
#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;

public:
	void Move_Frame();
protected:
	FRAME		m_tFrame;
	const TCHAR* m_pFrameKey = L"";

	VEC2		m_vCameraRenderPos;

	RENDERID		m_eRender;
	bool	m_bSceneChange;
};

