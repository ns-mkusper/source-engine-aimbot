#include "halflife2.h"

BaseHook	HalFLife2;

BaseHook::BaseHook()
{
	//HalFLife2.m_pHl2GameConsole =			new CConsole();
	HalFLife2.m_pMyPlayer =					new LocalPlayer();
	HalFLife2.m_pNeeded =					new Needed();	
//	HalFLife2.m_pEsp =						new Esp();
//	HalFLife2.m_pDrawzLayer =				new CDrawLayer();

	//HalFLife2.m_pAimbot =					new cCAimbot();
	//HalFLife2.m_pNoSpread =					new nospread();
}