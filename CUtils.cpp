/*
	Copyright 2008 UZI-I Production

	Contact : uzi-i@live.fr
	Web : uzi-i.new.fr

	GPL Code License :
		This file is part of SA Online.

		SA Online is free software; you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation; either version 2 of the License, or
		(at your option) any later version.

		SA Online is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with SA Online; if not, write to the Free Software
		Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

// - Include
/////////////////////
#include "stdafx.h"

// - Function
/////////////////////
void CUtils::DebugLog ( char* cSection, char* cText, ... )
{
#ifdef _DEBUG
	
	char Output[1024];

	char sz [ 1024 ] = { 0 };
	va_list va_alist;
	va_start ( va_alist, cText );
	vsnprintf ( sz, sizeof ( sz ), cText, va_alist );
	va_end ( va_alist );

	sprintf_s ( Output, "[%s]-> %s\r\n", cSection, sz );

	FILE* ioDebug =
		fopen ( "Debug.log", "a" );
		fwrite ( Output, 1, (int)strlen(Output), ioDebug );
		fclose ( ioDebug );
#endif
}

void CUtils::strcatf ( char* cText, char* format, ... )
{
	char sz [ 500 ] = { 0 };
	va_list va_alist;
	va_start ( va_alist, format );
	_vsnprintf_s ( sz, sizeof ( sz ), format, va_alist );
	va_end ( va_alist );
	strcat ( cText, sz );
}

int CUtils::isin ( char *string, char *find_string )
{ 
	char*r; 
	int result; 
	string = _strlwr( _strdup( string ) ); 
	find_string = _strlwr( _strdup( find_string ) ); 
	r = strstr( string,find_string ); 
	result = r - string + 1; 
	if( r != NULL ) 
		return result ; 
	else 
		return 0; 
}

void CUtils::Convert3DtoScreen ( CVector* vPos1, CVector* vPos2, int& iX, int& iY )
{
	CVector vRetn;
	CVector* v = &vRetn;
	DWORD dwFunc = 0x71DA00;
	bool bReturn = false;
	_asm
	{
		push	vPos1.fY
		push	vPos1.fX
		push	v
		push	vPos2
		call	dwFunc
		add		esp, 0x18
		sub		esp, 8
		mov		bReturn, al
	}
	iX = static_cast < int > ( vRetn.fX );
	iY = static_cast < int > ( vRetn.fY );
}

int CUtils::GetTextLength ( char *szString )
{
	char szText[512];
	memset(szText,0,512);
	strcpy(szText,szString);
	unsigned int i = 0, iStrLen = 0;
	while (i < strlen(szText))
	{
		switch(szText[i])
		{
		case ' ':
			iStrLen += 4;
			break;
		case 'e':
			iStrLen += 6;
			break;
		case 'i':
			iStrLen += 2;
			break;
		case 'j':
			iStrLen += 3;
			break;
		case 'k':
			iStrLen += 6;
			break;
		case 'l':
			iStrLen += 2;
			break;
		case 'm':
			iStrLen += 10;
			break;
		case 'r':
			iStrLen += 4;
		case 'v':
			iStrLen += 7;
			break;
		case 'w':
			iStrLen += 9;
			break;
		case 'y':
			iStrLen += 7;
			break;
		case 'A':
			iStrLen += 7;
			break;
		case 'C':
			iStrLen += 7;
			break;
		case 'H':
			iStrLen += 7;
			break;
		case 'I':
			iStrLen += 2;
			break;
		case 'K':
			iStrLen += 7;
			break;
		case 'M':
			iStrLen += 9;
			break;
		case 'O':
			iStrLen += 7;
			break;
		case 'P':
			iStrLen += 7;
			break;
		case 'Q':
			iStrLen += 7;
			break;
		case 'R':
			iStrLen += 6;
			break;
		case 'V':
			iStrLen += 7;
			break;
		case 'W':
			iStrLen += 11;
			break;
		case 'X':
			iStrLen += 8;
			break;
		case 'Y':
			iStrLen += 7;
			break;
		default:
			iStrLen += 5;
			break;
		}
		i++;
	}
	return iStrLen;
}

float CUtils::GetDistanceBetweenAB	( CVector vPosA, CVector vPosB )
{
	float	DistanceX = vPosA.fX - vPosB.fX,
			DistanceY = vPosA.fY - vPosB.fY,
			DistanceZ = vPosA.fZ - vPosB.fZ;

	return sqrt ( DistanceX * DistanceX + DistanceY * DistanceY + DistanceZ * DistanceZ );
}

char* CUtils::getParamStr ( char* p, char** result )
{
	int i, len;
	char* start, *s, *q;
	while (TRUE) {
		while ((p[0] != 0) && (p[0] <= ' ')) p++;
		if ((p[0] == '"') && (p[1] == '"')) 
			p += 2;
		else
			break;
	}
	len = 0;
	start = p;
	while (p[0] > ' ') {
		if (p[0] == '"') {
			p++;
			while ((p[0] != 0) && (p[0] != '"')) {
				q = p + 1;
				len += (q - p);
				p = q;
			}
			if (p[0] != 0) p++;
		}
		else {
			q = p + 1;
			len += q - p;
			p = q;
		}
	}
	*result = (char*) calloc(len + 1, sizeof(char));
	p = start;
	s = *result;
	i = 0;
	while (p[0] > ' ') {
		if (p[0] == '"') {
			p++;
			while ((p[0] != 0) && (p[0] != '"')) {
				q = p + 1;
				while (p < q) {
					s[i] = *p;
					p++;
					i++;
				}
			}
			if (p[0] != 0) p++;
		}
		else {
			q = p + 1;
			while (p < q) {
				s[i] = *p;
				p++;
				i++;
			}
		}
	}
	return p;
}

int CUtils::paramCount ( void )
{
	char* p = NULL, *s = NULL;
	int res = 0;
	p = GetCommandLine();
	while (TRUE) {
		p = getParamStr(p, &s);
		if (strncmp(s, "", 1) == 0) {
			free(s);
			break;
		}
		res++;
		free(s);
	}
	return res;
}

char* CUtils::paramStr ( int idx )
{
	char* p, *res = NULL;
	char buffer[MAX_PATH + 1];
	if (idx == 0) {
		GetModuleFileName(NULL, buffer, sizeof(buffer) * sizeof(char));
		int l = strlen(buffer) + 1;
		res = (char*) calloc(l, sizeof(char));
		strncpy(res, buffer, l);
	}
	else {
		p = GetCommandLine();
		while (TRUE) {
			p = getParamStr(p, &res);
			if ((idx == 0) || (strncmp(res, "", 1) == 0))
				break;
			idx--;
			free(res);
		}
	}
	return res;
}

void CUtils::PatchAddress ( DWORD dwAddress, BYTE* bPatch, size_t iSize )
{
	DWORD d, ds;

	VirtualProtect ( ( void* )dwAddress, iSize, PAGE_EXECUTE_READWRITE, &d );
	memcpy ( ( void* )dwAddress, bPatch, iSize);
	VirtualProtect ( ( void* )dwAddress, iSize, d, &ds );
}

void CUtils::PatchAddress ( DWORD dwAddress, BYTE bPatch )
{
	PatchAddress ( dwAddress, &bPatch, 1 );
}

void CUtils::NopAddress ( DWORD dwAddress, size_t iSize )
{
	DWORD d, ds;

	VirtualProtect ( ( void* )dwAddress, iSize, PAGE_EXECUTE_READWRITE, &d );
	memset ( ( void* ) dwAddress, 0x90, iSize);
	VirtualProtect ( ( void* )dwAddress, iSize, d, &ds );
}

void CUtils::NopAddress ( DWORD dwAddress )
{
	NopAddress ( dwAddress, 1 );
}

void CUtils::HookFunction ( DWORD dwAddress, DWORD dwFuntion )
{
	DWORD d, ds;

	VirtualProtect ( ( void* )dwAddress, 5, PAGE_EXECUTE_READWRITE, &d );
	
	switch( * ( BYTE* )( dwAddress ) )
	{
		case 0xE8:
			* ( DWORD* )( dwAddress + 0x01 ) = dwFuntion - ( dwAddress + 5 );
			break;
	}
	VirtualProtect ( ( void* )dwAddress, 5, d, &ds );
}

void CUtils::NopFunction ( DWORD dwAddress )
{
	DWORD d, ds;

	VirtualProtect ( ( void* )dwAddress, 5, PAGE_EXECUTE_READWRITE, &d);
	
	switch( * ( BYTE* )( dwAddress ) )
	{
		case 0xE8:
			memset ( ( void* )dwAddress, 0x90, 5 );
			break;
	}
	VirtualProtect ( ( void* )dwAddress, 5, d, &ds );
}

CVector CUtils::GetVectorInFrontOf ( CVector* vPos, float fAngle, float fVert, float fDistance )
{
	float fVX = fDistance * ( float ) ( sin ( fAngle / 57.3f ) );
	float fVY = fDistance * ( float ) ( cos ( fAngle / 57.3f ) );
	float fVZ = fDistance * ( float ) ( tan ( fVert / 57.3f ) );

	return CVector ( vPos->fX + fVX, vPos->fY + fVY, vPos->fZ + fVZ );
}