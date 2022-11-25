#pragma once

#include <windows.h>

#ifndef CLIENT_DLL
#define CLIENT_DLL
#endif

#include "sdk.h"
#include "stdafx.h"

#include "SDK/public/cdll_int.h"
#include "SDK/public/icliententitylist.h"
#include "SDK/public/icliententity.h"
#include "SDK/game/client/cbase.h"
#include "SDK/game/server/cbase.h"
#include "SDK/utils/captioncompiler/cbase.h"
#include "SDK/game/client/c_basecombatweapon.h"
#include "SDK/public/view_shared.h"
#include "SDK/game/shared/usercmd.h"
#include "SDK/game/shared/in_buttons.h"
#include "SDK/game/client/input.h"
#include "SDK/public/engine/ivmodelinfo.h"
#include "SDK/public/engine/IEngineTrace.h"
#include "SDK/public/vgui/ISurface.h"
#include "SDK/public/VGuiMatSurface/IMatSystemSurface.h"
#include "SDK/public/vgui/IPanel.h"

extern DWORD g_dwOrgFrameStageNotify;
extern DWORD dwEngine_Size = 0x2af000;
extern DWORD dwClient_Size = 0x610000;

void	__stdcall new_FrameStageNotify( ClientFrameStage_t curStage );

void __cdecl add_log(const char * fmt, ...);
long long timeval_diff(struct timeval *difference, struct timeval *end_time, struct timeval *start_time );
void Trace(LPCSTR format, ...);
#include <time.h>
