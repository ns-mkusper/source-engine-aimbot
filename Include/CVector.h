
#pragma once

class CVector
{
	public:
		float				fX, fY, fZ;

							CVector					( void )							{ this->fX = 0.0f, this->fY = 0.0f, this->fZ = 0.0f; }
							CVector					( float fX, float fY, float fZ )	{ this->fX = fX, this->fY = fY, this->fZ = fZ; }
							CVector	operator =		( CVector v )						{ this->fX = v.fX, this->fY = v.fY, this->fZ = v.fZ; return *this; }
		bool				IsSame					( CVector v )						{ return ( this->fX == v.fX && this->fY == v.fY && this->fZ == v.fZ ); }
};
