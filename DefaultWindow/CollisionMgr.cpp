#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT   rcRect{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcRect, &(Dst->Get_Collider()), &(Src->Get_Collider())))
			{
				if (Dst->GetCollisionSet()->find(Src) == Dst->GetCollisionSet()->end())
				{
					Dst->OnCollisionEnter(Src);
					Src->OnCollisionEnter(Dst);
					Dst->GetCollisionSet()->insert(Src);
					Src->GetCollisionSet()->insert(Dst);
				}
				else if (Dst->GetCollisionSet()->find(Src) != Dst->GetCollisionSet()->end())
				{
					Dst->OnCollisionStay(Src);
					Src->OnCollisionStay(Dst);
				}
			}
			else
			{
				if (Dst->GetCollisionSet()->find(Src) != Dst->GetCollisionSet()->end())
				{
					Dst->OnCollisionExit(Src);
					Src->OnCollisionExit(Dst);
					Dst->GetCollisionSet()->erase(Src);
					Src->GetCollisionSet()->erase(Dst);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX > fY) // 상하 충돌
				{
					// 상 충돌
					if (Dst->Get_Pos().y< Src->Get_Pos().y)
					{
						Dst->Set_PosY(-fY);
					}
					// 하 충돌
					else
					{
						Dst->Set_PosY(fY);
					}
				}

				else 		// 좌우 충돌
				{
					// 우 충돌
					if (Dst->Get_Pos().x < Src->Get_Pos().x)
					{
						Dst->Set_PosX(-fX);
					}
					// 좌 충돌
					else if(Dst->Get_Collider().left < Src->Get_Collider().right)
					{
						Dst->Set_PosX(fX);
					}
				}
			}
		}
	}

}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{

	//콜라이더 중점 구하기
	float fDst_fCX = pDst->Get_Collider().right - pDst->Get_Collider().left;
	float fDst_fX = pDst->Get_Collider().left + fDst_fCX * 0.5f;

	float fSrc_fCX = pSrc->Get_Collider().right - pSrc->Get_Collider().left;
	float fSrc_fX = pSrc->Get_Collider().left + fSrc_fCX * 0.5f;

	float fDst_fCY = pDst->Get_Collider().bottom - pDst->Get_Collider().top;
	float fDst_fY = pDst->Get_Collider().bottom - fDst_fCY * 0.5f;

	float fSrc_fCY = pSrc->Get_Collider().bottom - pSrc->Get_Collider().top;
	float fSrc_fY = pSrc->Get_Collider().bottom - fSrc_fCY * 0.5f;

	float	fWidth = abs(fDst_fX - fSrc_fX);
	float	fHeight = abs(pDst->Get_Pos().x - pSrc->Get_Pos().x);

	float	fRadiusX = (fDst_fCX + fSrc_fCX) * 0.5f;
	float	fRadiusY = (fDst_fCY + fSrc_fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	float	fWidth = abs(pDst->Get_Pos().x - pSrc->Get_Pos().x);
	float	fHeight = abs(pDst->Get_Pos().y - pSrc->Get_Pos().y);

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDst->Get_Size().x + pSrc->Get_Size().x) * 0.5f;

	return fRadius >= fDiagonal;
}
