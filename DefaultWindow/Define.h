#pragma once
#include<cassert>
extern	HWND		g_hWnd;

#define			WINCX		720
#define			WINCY		480

#define			PURE		= 0

#define			VK_MAX		0xff

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

enum SCENEID { SC_LOGO, SC_HOUSE, SC_FOREST, SC_VILLAGE, SC_STORE, SC_DUNGEON, SC_BOSS1, SC_LOAD, SC_ENDING, SC_END };
enum STATE { IDLE, WALK, ITEM_GET,ATTACK, HIT, DEAD, ROLL,FALL, SIZECHANGE, TELEPORT, ATTACKREADY, SHIELD, ST_END };
enum OBJID { OBJ_PLAYER, OBJ_ITEMCOLLIDER, OBJ_WALL, OBJ_NPC, OBJ_BULLET, OBJ_CEILLING,OBJ_MONSTER, OBJ_EYES, OBJ_ITEM, OBJ_EFFECT,OBJ_INVEN, OBJ_UI, OBJ_END };
enum ITEM_ID { ITEM_SWORD, ITEM_POT,  ITEM_WAND, ITEM_BOW, ITEM_SHIELD,  ITEM_STRONGSWORD, ITEM_Door, ITEM_END};
enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_CEILLING, RENDER_EFFECT,RENDER_INVEN, RENDER_UI, RENDER_END };
enum CHANNELID
{
    SOUND_EFFECT,
    SOUND_EFFECT2,
    SOUND_GET_ITEM,
    SOUND_BGM,
    SOUND_PLAYER,
    SOUND_BOSS,
    SOUND_MONSTER,
    SOUND_PLAYER_ATTACK,
    SOUND_INVEN,
    MAXCHANNEL
};


typedef struct tagInfo
{
	float		fX;
	float		fY;

	float		fCX;
	float		fCY;

}INFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

//template<typename T>
//void Safe_Delete_Array(T& Temp)
//{
//	if (Temp)
//	{
//		delete[] Temp;
//		Temp = nullptr;
//	}
//}


typedef struct tagFrame
{
	int		iFrameStart;	
	int		iFrameEnd;
	int		iMotion;

	DWORD	dwSpeed;
	DWORD	dwTime;

    bool		bIsPlayDone;
}FRAME;


struct DeleteMap
{
	template<typename T>
	void		operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};


class CStringCmp
{

public:
	CStringCmp(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}

private:
	const	TCHAR* m_pString;
};


typedef struct Vector
{
    Vector() {}
    Vector(float x, float y) : x(x), y(y) {}
    Vector(POINT pt) :x((float)pt.x), y((float)pt.y) {}

    //0벡터인지 확인(방향, 크기가 없는 벡터)
    bool IsZero()
    {
        if (x == 0.f && y == 0.f)
            return true;

        return false;
    }

    //더하기
    const Vector operator+(const Vector& other) const
    {
        return Vector(x + other.x, y + other.y);
    }

    //빼기
    Vector operator-(const Vector& other)
    {
        Vector ret;
        ret.x = x - other.x;
        ret.y = y - other.y;
        return ret;
    }

    //곱하기
    Vector operator*(float value)
    {
        Vector ret;
        ret.x = x * value;
        ret.y = y * value;
        return ret;
    }

    //나누기(벡터끼리)
    Vector operator /(Vector _vOther)
    {
        //0으로 나누지 않도록 오류 처리
        assert(!(0.f == _vOther.x || 0.f == _vOther.y));
        return  Vector(x / _vOther.x, y / _vOther.y);
    }

    //나누기(실수로)
    Vector operator /(float _f)
    {
        //0으로 나누지 않도록 오류 처리
        assert(!(0.f == _f));
        return  Vector(x / _f, y / _f);
    }

    void operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;
    }
    void operator-=(const Vector& other)
    {
        x -= other.x;
        y -= other.y;
    }
    void operator*=(float value)
    {
        x *= value;
        y *= value;
    }

    //빗변의 제곱
    float LengthSqured()
    {
        return x * x + y * y;
    }

    //빗변의 길이
    float Length()
    {
        return ::sqrt(LengthSqured());
    }

    //정규화(크기로 나눠서 방향 벡터로 만들어줌)
    Vector& Normalize()
    {
        float fLen;
        fLen = Length();
        if (fLen < 0.0001f)
            fLen = 0.0001f;
        //assert(fLen != 0.f);
        x /= fLen;
        y /= fLen;
        return *this;
    }

    //내적
    float Dot(Vector other)
    {
        return x * other.x + y * other.y;
    }

    //외적
    float Cross(Vector other)
    {
        return x * other.y - y * other.x;
    }

    float x = 0;
    float y = 0;
}VEC2;