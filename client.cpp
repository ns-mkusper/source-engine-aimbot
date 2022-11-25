#include "stdafx.h"
#include "client.h"
#include "extrafunctions.h"

struct CRadarPlayer
{
	__int32 bIsValid; //0000  -> not updating that much?!
	char unknown0[12];
	char Unknown1[32]; //0010
	__int32 iTeam; //0030
	__int32 iHealth; //0034
	Vector vOrigin; //0038
	QAngle qViewAngles; //0044
};


DWORD g_dwOrgPaintTraverse;
void __stdcall new_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
	_asm
	{
		PUSH allowForce
			PUSH forceRepaint
			PUSH vguiPanel
			CALL g_dwOrgPaintTraverse
	}
}

DWORD g_dwOrgCreateMove;
void __stdcall new_CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	_asm
	{
		PUSH active
			PUSH input_sample_frametime
			PUSH sequence_number
			CALL g_dwOrgCreateMove
	}

	GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();
	if( HalFLife2.m_pEngineClient->IsConnected() == false || HalFLife2.m_pEngineClient->IsLevelMainMenuBackground( ) || HalFLife2.m_pEngineClient->IsDrawingLoadingImage( ) || !HalFLife2.m_pEngineClient->IsInGame( ) || !HalFLife2.m_pInput || HalFLife2.m_pEngineClient->Con_IsVisible() == true || *pMe->pl()->deadflag() != 0 )
		return;

	bool bIsInAttack = false;
	bool bCanBackstab = false;
	player_info_t pinfo;

	GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pMe;

	CInput::CVerifiedUserCmd *pVerified = *((CInput::CVerifiedUserCmd**)( (DWORD)HalFLife2.m_pInput + 0xB8 ));
	CUserCmd* pCmd = HalFLife2.m_pInput->GetUserCmd( sequence_number );


	IClientEntity* pWeaponEnt = (IClientEntity*)HalFLife2.m_pEntList->GetClientEntity(pMe->hActiveWeapon()->GetEntryIndex());
	C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)pWeaponEnt;
	//reinterpret_cast< GenDT_BaseAttributableItem* >( pWeapon )->AttributeManager()->Item()->AttributeList();
	
	GenDT_TFWeaponBase *pTFWeaponBase = (GenDT_TFWeaponBase*)pWeapon;
	//float flWeaponTime = *pTFWeaponBase->LocalActiveTFWeaponData()->flReloadPriorNextFire();
	//float flLastFireTime = *pTFWeaponBase->LocalActiveTFWeaponData()->flLastFireTime();
	//bool bReload = *pTFWeaponBase->bReloadedThroughAnimEvent();
	// 
	//HalFLife2.m_pEngineClient->Con_NPrintf(20, "WeaponTime:\t%f", flWeaponTime);
	//HalFLife2.m_pEngineClient->Con_NPrintf(21, "LastFireTime:\t%f", flLastFireTime);
	//HalFLife2.m_pEngineClient->Con_NPrintf(22, "Reload?:\t%s", (bReload)?"true":"false");

	if (pCmd)
	{
		if ( pCmd->buttons & IN_ATTACK && !GetAsyncKeyState(VK_SHIFT) )
		{
			bIsInAttack = true;
			if ( pWeapon->GetClientClass()->m_ClassID == WPN_Huntsman )
				pCmd->buttons |= IN_ATTACK;
			else
				pCmd->buttons &= ~IN_ATTACK;
		}

		if (bIsInAttack)
		{
			bIsInAttack = !bIsInAttack;

			if ( pWeapon->GetClientClass()->m_ClassID == WPN_Huntsman )
			{
				float flProjectileSpeed = HalFLife2.m_pAimbot->GetProjectileSpeed( pWeapon );
				if (flProjectileSpeed > 2300.0f)
					HalFLife2.m_pAimbot->AimAtTarget( pCmd );
			}
			else
			{
				HalFLife2.m_pAimbot->AimAtTarget( pCmd );
			}

		}
	}

	//if ( *TFME->PlayerClass()->iClass() == TF_SPY )
	//{
	//	GenDT_TFWeaponKnife* pKnife = (GenDT_TFWeaponKnife*)pWeapon;

	//	HalFLife2.m_pEngineClient->Con_NPrintf(20, "Backstab:\t%s", (*pKnife->bReadyToBackstab())?"true":"false");

	//	if (*pKnife->bReadyToBackstab())
	//		pCmd->buttons |= IN_ATTACK;
	//}

	if (*pMe->pl()->deadflag() == 0)
	{
		//Trace("%f", HalFLife2.m_pGlobals->curtime);
		HalFLife2.m_pEngineClient->Con_NPrintf(14, "Weapon:\t%i", pWeapon->GetClientClass()->m_ClassID);

		HalFLife2.m_pEngineClient->Con_NPrintf(15, "BaseEnt:\t%X", HalFLife2.m_pMyPlayer->BaseEnt());
		HalFLife2.m_pEngineClient->Con_NPrintf(16, "WeaponEnt:\t%X", pWeapon);


		HalFLife2.m_pEngineClient->Con_NPrintf(18, "SETVIEW: %s", (HalFLife2.m_pAimbot->bSetViewAngles)?"true":"false");

		//HalFLife2.m_pEngineClient->Con_NPrintf(20, "X:\t%f", pMe->vecOrigin()->x);
		//HalFLife2.m_pEngineClient->Con_NPrintf(21, "Y:\t%f", pMe->vecOrigin()->y);
		//HalFLife2.m_pEngineClient->Con_NPrintf(22, "Z:\t%f", pMe->vecOrigin()->z);

		//HalFLife2.m_pEngineClient->Con_NPrintf(25, "0:\t%f", pCmd->viewangles[0]);
		//HalFLife2.m_pEngineClient->Con_NPrintf(26, "1:\t%f", pCmd->viewangles[1]);
	}

	if ( pVerified ){
		pVerified[sequence_number % MULTIPLAYER_BACKUP].m_cmd		  = *pCmd;
		pVerified[sequence_number % MULTIPLAYER_BACKUP].m_crc		  = pCmd->GetChecksum();
		HalFLife2.m_pInput->m_pVerifiedCommands = pVerified;
	}
} 

DWORD g_dwOrgPush3DView;
void __stdcall new_Push3DView( const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes )
{
	CViewSetup nview;
	memcpy( &nview, &view, sizeof( CViewSetup ) );

	C_BaseEntity *pLocal =  HalFLife2.m_pEntList->GetClientEntity(HalFLife2.m_pEngineClient->GetLocalPlayer() )->GetBaseEntity();
	GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();
	GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pMe;

	char *lifestate = (char*) ( ( DWORD )pLocal + ( DWORD )0x8b );

	if( pLocal && lifestate == LIFE_ALIVE )
	{
		Vector vecPunchAngle = *pMe->localdata()->Local()->vecPunchAngle();
		QAngle pAngle = QAngle(vecPunchAngle.x, vecPunchAngle.y, vecPunchAngle.z);
		nview.angles -= pAngle;
	}

	memcpy( (void*)&view, &nview, sizeof( CViewSetup ) );

	_asm
	{
		PUSH frustumPlanes
			PUSH pRenderTarget
			PUSH nFlags
			PUSH view
			CALL g_dwOrgPush3DView
	}	
}

DWORD g_dwOrgHudUpdate;
void __stdcall new_HudUpdate ( bool bActive )
{
	_asm
	{
		PUSH bActive
			CALL g_dwOrgHudUpdate
	}
}

DWORD g_dwOrgDrawModel;

C_BaseCombatWeapon* GetBaseCombatActiveWeapon( CBaseEntity* pBaseEntity )
{
	C_BaseCombatWeapon* pActiveWeapon = NULL;
	__asm
	{
		MOV  EAX, pBaseEntity          ; eax = pBaseEntity
			MOV  EDI, EAX                  ; edi = eax
			MOV  EAX, DWORD PTR DS :[EDI]  ; eax = pointer to edi
			MOV  ECX, EDI                  ; ecx = edi 
			CALL DWORD PTR DS :[EAX+0x34C] ; call GetActiveWeapon
			MOV  pActiveWeapon, EAX;       ; save the returned pointer to the weaponhandle in pActiveWeapon
	}
	return pActiveWeapon;                 // return the weapon handle 
}