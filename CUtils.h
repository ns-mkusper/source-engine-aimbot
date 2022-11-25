#pragma once

#include "stdafx.h"
// - Class
/////////////////////
class CUtils
{
	public:
		void		DebugLog				( char* cSection, char *cText, ... );
		void		strcatf					( char* cText, char* format, ... );
		int			isin					( char *string, char *find_string );

		void		Convert3DtoScreen		( CVector* vPos1, CVector* vPos2, int& iX, int& iY );
		int			GetTextLength			( char *szString );
		float		GetDistanceBetweenAB	( CVector vPosA, CVector vPosB );

		char*		getParamStr				( char* p, char** result );
		int			paramCount				( void );
		char*		paramStr				( int idx );

		void		PatchAddress			( DWORD dwAddress, BYTE* bPatch, size_t iSize );
		void		PatchAddress			( DWORD dwAddress, BYTE bPatch );
		void		NopAddress				( DWORD dwAddress, size_t iSize );
		void		NopAddress				( DWORD dwAddress );
		void		HookFunction			( DWORD dwAddress, DWORD dwFuntion );
		void		NopFunction				( DWORD dwAddress );

		CVector		GetVectorInFrontOf		( CVector* vPos, float fAngle, float fVert, float fDistance );

};
