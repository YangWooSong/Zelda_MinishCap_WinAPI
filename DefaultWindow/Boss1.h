#pragma once
#include "Monster.h"
class CScene;

class CBoss1 :
    public CMonster
{
public:
    CBoss1();
    virtual ~CBoss1();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;


public:
    void Set_bChagneAttack(bool _b) { m_bChangeAttack = _b; }
    void Minus_EyeCount() { m_iEyeBallCount -= 1; }
    void Minus_LaserEyeCount() { m_iLaserBallCount -= 1; }
    void Minus_BulletCount() { m_iBulletCount -= 1; }
    STATE Get_CurState() { return m_eCurState; }
    void Set_Scene(CScene* _target) { m_pScene = _target; }

private:
    void Pattern0_Teleport();       //순간이동
    void Pattern1_NormalBullet();            //일반 총알 와다다
    void Pattern3_EyeBall();            //눈동자 소환
    void Pattern4_LaserBall();            //눈동자 소환
    void Motion_Change();
    void Key_Input();
    void FallowPlayer();
    void Change_Attack(int _iSelect);


private:
    int   m_iPatternSelect;
    int     m_iEyeBallCount;
    int     m_iLaserBallCount;
    int     m_iBulletCount;
    DWORD				m_dwTime;
    int                 m_Repeat;
    bool                m_bMove;
    bool                m_bChangeAttack;
    bool                m_bDead;

    CScene*             m_pScene;

    list<CObj*>        m_pEyeBallList;
    list<CObj*>        m_pBulletList;
};

