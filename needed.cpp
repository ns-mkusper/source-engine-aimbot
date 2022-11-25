#include "Needed.h"
#include "stdafx.h"

void Needed::FontInit( void )
{
	//font init
	m_ESPFont = HalFLife2.m_pMatSurface->CreateFont();	
	HalFLife2.m_pMatSurface->SetFontGlyphSet( m_ESPFont, "Arial", 16, 450, 0, 0, 0x200 );
}

bool Needed::ScreenTransform( const Vector &point, Vector &screen )
{
	float w;
	const VMatrix &worldToScreen = HalFLife2.m_pEngineClient->WorldToScreenMatrix();
	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w		 = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}
	return behind;
}

bool Needed::WorldToScreen( const Vector &vOrigin, Vector &vScreen )
{
	if( ScreenTransform(vOrigin , vScreen) == false )
	{
		int iScreenWidth, iScreenHeight;

		HalFLife2.m_pEngineClient->GetScreenSize( iScreenWidth, iScreenHeight );
		float x = iScreenWidth / 2;
		float y = iScreenHeight / 2;
		x += 0.5 * vScreen.x * iScreenWidth + 0.5;
		y -= 0.5 * vScreen.y * iScreenHeight + 0.5;
		vScreen.x = x;
		vScreen.y = y;
		return true;
	}
	return false;
}

void Needed::FillRGBA( int x, int y, int w, int h, DWORD dwColor )
{
	HalFLife2.m_pMatSurface->DrawSetColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
	HalFLife2.m_pMatSurface->DrawFilledRect( x, y, x + w, y + h );
}

void Needed::DrawString( int x, int y, DWORD dwColor, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf( szBuffer, pszText, va_alist );
	va_end( va_alist );

	HalFLife2.m_pMatSurface->DrawColoredText( m_ESPFont, x, y, RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor), "%s", szBuffer );
}

void Needed::GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter )
{
	if ( pBaseEnt )
	{
		Vector vMin, vMax;
		pBaseEnt->GetRenderBounds( vMin, vMax );
		vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
		vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;
	}
}
//-------------------------------------------------------------------------------------------------------------------------//
C_BaseCombatWeapon* Needed::GetBaseCombatActiveWeapon ( C_BaseEntity* pEntity )
{
	C_BaseCombatWeapon* hResult = NULL;
	__asm
	{
		MOV  EAX, pEntity;
		MOV  EDI, EAX;
		MOV  EAX, DWORD PTR DS :[EDI];
		MOV  ECX, EDI;
		CALL DWORD PTR DS :[EAX+0x2C8]
		mov  hResult, EAX;
	}
	return hResult;
}

//-------------------------------------------------------------------------------------------------------------------------------------//