#include "recvtable.h"
#include "stdafx.h"

cRecvTable gRecvTable;

offets* GetOffset;

void*hl2_offsets::m_iTeamNum = NULL;
void*hl2_offsets::m_vecOrigin = NULL;
void*hl2_offsets::m_angRotation = NULL;
void*hl2_offsets::m_clrRender = NULL;
void*hl2_offsets::m_nHitboxSet = NULL;
void*hl2_offsets::m_iFlags = NULL;
void*hl2_offsets::m_lifeState = NULL;
void*hl2_offsets::m_iHealth = NULL;
void*hl2_offsets::m_hActiveWeapon = NULL;
void*hl2_offsets::m_bInBombZone = NULL;
void*hl2_offsets::m_bIsDefusing = NULL;
void*hl2_offsets::m_bInBuyZone = NULL;
void*hl2_offsets::m_iArmor = NULL;
void*hl2_offsets::m_iEyeAnglesX = NULL;
void*hl2_offsets::m_iEyeAnglesY = NULL;
void*hl2_offsets::m_vecVelocityX = NULL;
void*hl2_offsets::m_vecVelocityY = NULL;
void*hl2_offsets::m_vecVelocityZ = NULL;
void*hl2_offsets::m_iFov = NULL;
void*hl2_offsets::m_vecViewOffsetX = NULL;
void*hl2_offsets::m_vecViewOffsetY = NULL;
void*hl2_offsets::m_vecViewOffsetZ = NULL;
void*hl2_offsets::m_bHasHelmet = NULL;
void*hl2_offsets::m_flFlashDuration = NULL;
void*hl2_offsets::m_flFlashMaxAlpha = NULL;
void*hl2_offsets::m_iPrimaryAddon = NULL;
void*hl2_offsets::m_iSecondaryAddon = NULL;
void*hl2_offsets::m_iAddonBits = NULL;
void*hl2_offsets::m_iObserverMode = NULL;
void*hl2_offsets::m_hObserverTarget = NULL;
void*hl2_offsets::m_vecPunchAngle = NULL;
void*hl2_offsets::m_bSilencerOn_USP = NULL;
void*hl2_offsets::m_bSilencerOn_M4A1 = NULL;
void*hl2_offsets::m_bBurstMode_Glock = NULL;
void*hl2_offsets::m_bBurstMode_Famas = NULL;
void*hl2_offsets::m_iState = NULL;
void*hl2_offsets::m_iClip1 = NULL;
void*hl2_offsets::m_iClip2 = NULL;


void cRecvTable::parse_offset_table( char* lpClassName, RecvTable*prt )
{
        for( int TableIndex = 0; TableIndex < prt->GetNumProps(); TableIndex++ )
        {
                RecvProp* prp = (RecvProp*)prt->GetProp( TableIndex );
                if ( !prp )
                {
                        continue;
                }

                char* lpName = (char*)prp->GetName();
                if ( !lpName )
                {
                        continue;
                }

                int iType = (int)prp->GetType();

                if(!strcmp( lpClassName, "CBaseEntity" ) || !strcmp( lpClassName, "DT_BaseEntity" ) )
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_iTeamNum" ) )
                        {
                                hl2_offsets::m_iTeamNum = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iTeamNum);
                        }
                        else if( iType == DPT_Vector && !strcmp( lpName, "m_vecOrigin" ) )
                        {
                                hl2_offsets::m_vecOrigin = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_vecOrigin);
                        }
                        else if( iType == DPT_Vector && !strcmp( lpName, "m_angRotation" ) )
                        {
                                hl2_offsets::m_angRotation = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_angRotation);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_clrRender" ) )
                        {
                                hl2_offsets::m_clrRender = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_clrRender);
                        }
                }
                else if(!strcmp( lpClassName, "CBaseAnimating" ) || !strcmp( lpClassName, "DT_BaseAnimating" ) )
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_nHitboxSet" ) )
                        {
                                hl2_offsets::m_nHitboxSet = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_nHitboxSet);
                        }
                }
                else if(!strcmp( lpClassName, "CBasePlayer" ) || !strcmp( lpClassName, "DT_BasePlayer" ) )
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_fFlags" ) )
                        {
                                hl2_offsets::m_iFlags = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iFlags);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_lifeState" ) )
                        {
                                hl2_offsets::m_lifeState = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_lifeState);
                        }
                }
                else if(!strcmp( lpClassName, "C_BaseHLPlayer" )|| !strcmp( lpClassName, "CHL1_Player" )
                        ||    !strcmp( lpClassName, "CCSPlayer" )||      !strcmp( lpClassName, "DT_CSPlayer" )
                        ||    !strcmp( lpClassName, "CHL2_Player")||     !strcmp( lpClassName, "DT_HL2_Player" )
                        ||    !strcmp( lpClassName, "CDOD_Player" )||    !strcmp( lpClassName, "CDODPlayer" )
                        ||    !strcmp( lpClassName, "CSDKPlayer" )||     !strcmp( lpClassName, "C_SDKPlayer" )
                        ||    !strcmp( lpClassName, "CSP_Player" )||     !strcmp( lpClassName, "DT_SDKPlayer" )
                        ||    !strcmp( lpClassName, "CINSPlayer" )||     !strcmp( lpClassName, "DT_INSPlayer" )
                        ||    !strcmp( lpClassName, "CTFPlayer" )||      !strcmp( lpClassName, "DT_TFPlayer" )
                        ||    !strcmp( lpClassName, "player" ))
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_iHealth" ) )
                        {
                                hl2_offsets::m_iHealth = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iHealth);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_hActiveWeapon" ) )
                        {
                                hl2_offsets::m_hActiveWeapon = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_hActiveWeapon);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_bInBombZone" ) )
                        {
                                hl2_offsets::m_bInBombZone = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bInBombZone);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_bIsDefusing" ) )
                        {
                                hl2_offsets::m_bIsDefusing = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bIsDefusing);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_bInBuyZone" ) )
                        {
                                hl2_offsets::m_bInBuyZone = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bInBuyZone);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_ArmorValue" ) )
                        {
                                hl2_offsets::m_iArmor = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iArmor);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName,    "m_angEyeAngles[0]" ) )
                        {
                                hl2_offsets::m_iEyeAnglesX = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iEyeAnglesX);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName,    "m_angEyeAngles[1]" ) )
                        {
                                hl2_offsets::m_iEyeAnglesY = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iEyeAnglesY);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_vecVelocity[0]" ) )
                        {
                                hl2_offsets::m_vecVelocityX = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_vecVelocityX);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_vecVelocity[1]" ) )
                        {
                                hl2_offsets::m_vecVelocityY = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_vecVelocityY);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_vecVelocity[2]" ) )
                        {
                                hl2_offsets::m_vecVelocityZ = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_vecVelocityZ);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_iFOV" ) )
                        {
                                hl2_offsets::m_iFov = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iFov);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_vecViewOffset[0]" ) )
                        {
                                hl2_offsets::m_vecViewOffsetX = (void*)prp->GetOffset( );
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_vecViewOffsetX);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_vecViewOffset[1]" ) )
                        {
                                hl2_offsets::m_vecViewOffsetY = (void*)prp->GetOffset( );
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_vecViewOffsetY);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_vecViewOffset[2]" ) )
                        {
                                hl2_offsets::m_vecViewOffsetZ = (void*)prp->GetOffset( );
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_vecViewOffsetZ);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_bHasHelmet" ) )
                        {
                                hl2_offsets::m_bHasHelmet = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bHasHelmet);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_flFlashDuration" ) )
                        {
                                hl2_offsets::m_flFlashDuration = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_flFlashDuration);
                        }
                        else if( iType == DPT_Float && !strcmp( lpName, "m_flFlashMaxAlpha" ) )
                        {
                                hl2_offsets::m_flFlashMaxAlpha = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_flFlashMaxAlpha);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_iPrimaryAddon" ) )
                        {
                                hl2_offsets::m_iPrimaryAddon = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iPrimaryAddon);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_iSecondaryAddon" ) )
                        {
                                hl2_offsets::m_iSecondaryAddon = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iSecondaryAddon);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_iAddonBits" ) )
                        {
                                hl2_offsets::m_iAddonBits = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iAddonBits);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_iObserverMode" ) )
                        {
                                hl2_offsets::m_iObserverMode = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iObserverMode);
                        }
                        else if( iType == DPT_Int && !strcmp( lpName, "m_hObserverTarget" ) )
                        {
                                hl2_offsets::m_hObserverTarget = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_hObserverTarget);
                        }
                        else if( iType >= 5/*DPT_DataTable*/ )
                        {
                                RecvTable*prtLocal = prp->GetDataTable();
                                if ( !prtLocal )
                                {
                                        continue;
                                }

                                if( !strcmp( lpName, "m_Local" )  ||
                                    !strcmp( lpName, "m_HL2Local" ) ||
                                    !strcmp( lpName, "m_TFLocal" )  ||
                                    !strcmp( lpName, "m_INSLocal" ) )
                                {
                                        for( int j = 0; j < prtLocal->GetNumProps(); j++ )
                                        {
                                                RecvProp* prpLocal    =    (RecvProp*)prtLocal->GetProp( j );
                                                if ( !prpLocal )
                                                {
                                                        continue;
                                                }
                                                int iTypeLocal        =    (int)prpLocal->GetType();
                                                char* lpNameLocal    =    (char*)prpLocal->GetName();

                                                if( iTypeLocal == DPT_Vector && !strcmp( lpNameLocal,    "m_vecPunchAngle" ) )
                                                {
                                                        hl2_offsets::m_vecPunchAngle = (void*)((DWORD)prp->GetOffset( ) + prpLocal->GetOffset());
                                                        Trace("%s:%s:%X",lpName,lpNameLocal,hl2_offsets::m_vecPunchAngle);
                                                }
                                        }
                                }
                                else
                                {
                                        parse_offset_table( lpClassName, prtLocal );
                                }
                        }
                }
                else if(!strcmp( lpClassName, "CWeaponUSP" )||!strcmp( lpClassName, "DT_WeaponUSP" ) )
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_bSilencerOn" ) )
                        {
                                hl2_offsets::m_bSilencerOn_USP = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bSilencerOn_USP);
                        }
                }
                else if(!strcmp( lpClassName, "CWeaponM4A1" )||!strcmp( lpClassName, "DT_WeaponM4A1" ) )
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_bSilencerOn" ) )
                        {
                                hl2_offsets::m_bSilencerOn_M4A1 = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bSilencerOn_M4A1);
                        }
                }
                else if(!strcmp( lpClassName, "CWeaponGlock" )||!strcmp( lpClassName, "DT_WeaponGlock" ))
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_bBurstMode" ) )
                        {
                                hl2_offsets::m_bBurstMode_Glock = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bBurstMode_Glock);
                        }
                }
                else if(!strcmp( lpClassName, "CWeaponMedigun" )||!strcmp( lpClassName, "CWeaponMedigun" ) )
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_flChargeLevel" ) )
                        {
                                hl2_offsets::m_bBurstMode_Famas = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_bBurstMode_Famas);
                        }
                }
                else if(!strcmp( lpClassName, "CBaseCombatWeapon" )||!strcmp( lpClassName, "DT_BaseCombatWeapon" ))
                {
                        if( iType == DPT_Int && !strcmp( lpName, "m_iState" ) )
                        {
                                hl2_offsets::m_iState = (void*)prp->GetOffset();
                                Trace("%s:%s:%X",lpClassName,lpName,hl2_offsets::m_iState);
                        }
                        else if( iType >= 5/*DPT_DataTable*/ )
                        {
                                RecvTable*prtWeapon = prp->GetDataTable();

                                if(    !strcmp( lpName, "LocalWeaponData" )
                                       ||!strcmp( lpName, "DT_LocalWeaponData" ) )
                                {
                                        for( int j = 0; j < prtWeapon->GetNumProps(); j++ )
                                        {
                                                RecvProp*prpWeapon =    (RecvProp*)prtWeapon->GetProp( j );
                                                if ( !prpWeapon )
                                                {
                                                        continue;
                                                }
                                                int iTypeWeapon =        (int)prpWeapon->GetType();
                                                char* lpNameWeapon =    (char*)prpWeapon->GetName();

                                                if( iTypeWeapon == DPT_Int && !strcmp( lpNameWeapon,"m_iClip1" ) )
                                                {
                                                        hl2_offsets::m_iClip1 = (void*)((DWORD)prp->GetOffset( ) + prpWeapon->GetOffset());
                                                        Trace("%s:%s:%s:%X",lpClassName,lpName,lpNameWeapon,hl2_offsets::m_iClip1);
                                                }
                                                else if( iTypeWeapon == DPT_Int && !strcmp( lpNameWeapon,"m_iClip2" ) )
                                                {
                                                        hl2_offsets::m_iClip2 = (void*)((DWORD)prp->GetOffset( ) + prpWeapon->GetOffset());
                                                        Trace("%s:%s:%s:%X",lpClassName,lpName,lpNameWeapon,hl2_offsets::m_iClip2);
                                                }
                                        }
                                }
                                else
                                {
                                        parse_offset_table( lpClassName, prtWeapon );
                                }
                        }
                }
        }
}

void cRecvTable::dump_offset_table( char* t, RecvTable*prt, int iDepth )
{
        //try
        //{
        //char sTmp[1024]; 
        //
        //memset(sTmp,0,1024); 
        //memset(sTmp,'\t',iDepth); 
        //Trace( "%s - %s ", t,prt->GetName( ) ); 

        //for( int i = 0; i < prt->GetNumProps(); i++ )
        //{
        //	RecvProp*prp = prt->GetProp( i ); 
        //	Trace( "\t%s offset: 0x%X ",prp->GetName( ),prp->GetOffset( )); 

        //	if( prp->GetType( ) == 5 ) //DPT_DataTable
        //	{
        //		dump_offset_table( (char*)prt->GetName( ), prp->GetDataTable( ), iDepth+1 ); 
        //	}
        //}
        //  Trace( "%s(/ %s __ %s )\n\n",sTmp, t,    prt->GetName( )    ); 
        //}
        //catch(...)
        //{	
        //	 Trace( "exception" ); 

        //}
}

bool cRecvTable::grab_adress_and_offsets(bool logg)
{
        //grab offset
        if ( !HalFLife2.m_pClient )
        {
                Trace("grab_adress_and_offsets -> m_pClient is null");
                return false;
        }

        __TRY;
        ClientClass* m_phk_ClientClass = HalFLife2.m_pClient->GetAllClasses();
		Trace("m_phk_ClientClass");

        while ( m_phk_ClientClass )
        {
                if ( m_phk_ClientClass->GetName()[0] != 0 )
                {
                        if ( logg )
                        {
                                dump_offset_table(
                                        (char*)m_phk_ClientClass->GetName(),
                                        m_phk_ClientClass->m_pRecvTable,
                                        1
                                        );
                        }
                        parse_offset_table(
                                (char*)m_phk_ClientClass->GetName(),
                                m_phk_ClientClass->m_pRecvTable
                                );
                }
                m_phk_ClientClass = m_phk_ClientClass->m_pNext;
        };
        return true;
        __CATCH;

        return false;
}
