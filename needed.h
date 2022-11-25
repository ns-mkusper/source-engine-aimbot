#ifndef __NEEDED_H__
#define __NEEDED_H__

#include "sdk.h"

class Needed
{
public:
	void FontInit( void );
	bool ScreenTransform( const Vector &point, Vector &screen );
	bool WorldToScreen( const Vector &vOrigin, Vector &vScreen );
	void FillRGBA( int x, int y, int w, int h, DWORD dwColor );
	void DrawString( int x, int y, DWORD dwColor, const char *pszText, ... );
	void GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter );
	C_BaseCombatWeapon* Needed::GetBaseCombatActiveWeapon ( C_BaseEntity* pEntity );

public:
	vgui::HFont m_ESPFont;//esp
};

#endif
