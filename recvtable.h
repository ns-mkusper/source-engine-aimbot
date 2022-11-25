#ifndef RECVTABLE
#define RECVTABLE

#include "sdk.h"

class cRecvTable
{
public:
	void parse_offset_table( char* lpClassName, RecvTable*prt );
	void dump_offset_table( char* t, RecvTable*prt, int iDepth );
	bool grab_adress_and_offsets(bool logg);

};

struct offets
{
	DWORD m_lifestate;
};
extern offets* GetOffset;
extern cRecvTable gRecvTable;

#endif
