#pragma once

#include "stdafx.h"

class CVerifiedUserCmd
{
public:
	CUserCmd	m_cmd;
	CRC32_t		m_crc;
};

extern DWORD g_dwOrgPaintTraverse;
void __stdcall new_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce);

extern DWORD g_dwOrgCreateMove;
void __stdcall new_CreateMove( int sequence_number, float input_sample_frametime, bool active );

extern DWORD g_dwOrgPush3DView;
void __stdcall new_Push3DView( const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes );

extern DWORD g_dwOrgHudUpdate;
void __stdcall new_HudUpdate ( bool bActive );

bool		bIsHoldingAttack;


C_BaseCombatWeapon* GetBaseCombatActiveWeapon( CBaseEntity* pBaseEntity );