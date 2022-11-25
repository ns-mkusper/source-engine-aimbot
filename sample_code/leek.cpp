//  >> Code leaked by MACHETE
//    >> From Dos Christian's code

//    >> enjoy


#include "main.h"

//void new_CSPlayer_EyeAngleX( const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//    float Pitch = pData->m_Value.m_Float;
//    //C_BaseEntity* pEnt = (C_BaseEntity*)pStruct;
//
//    if(Pitch > 89.5 && Pitch <= 180.5)
//    //if(!(Pitch > 271 && Pitch <= 360.f) && !(Pitch >= 180 && Pitch < 89))
//    {
//        Pitch = 89.5;
//        g_cAimbot.AA[static_cast<C_BaseEntity*>(pStruct)->index] = true;
//    }
//    else if( Pitch > 180.5 && Pitch < 270.5 )
//    {
//        Pitch = 270.5;
//        g_cAimbot.AA[static_cast<C_BaseEntity*>(pStruct)->index] = true;
//    }
//    else
//        g_cAimbot.AA[static_cast<C_BaseEntity*>(pStruct)->index] = false;
//    *(float*)pOut = Pitch;
//    //pEnt->OnDataChanged( DATA_UPDATE_DATATABLE_CHANGED );
//}

//void HookPropRecv( const CRecvProxyData *pData, void *pStruct, void *pOut )
//{
//    float p = pData->m_Value.m_Float;
//    if( p > 180.0f )
//    p -= 360.0f;
//    if( p < -180.0f )
//    p = 360.0f;
//    if( p > -90 || p < 90 )
//    p = 89.0f;
//    else
//    if( p > 180 && p < 270 )
//    p = 270.0f;
//    *(float*)pOut = p;
//}

void HookPropRecv( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
        float Pitch = pData->m_Value.m_Float;
        if( Pitch > 89.1 && Pitch <= 180.08793f )
        {
                Pitch = 89.1;
                g_cAimbot.AA[static_cast<C_BaseEntity*>(pStruct)->index] = true;
        }
        else if( Pitch > 180.5 && Pitch < 270.5 )
        {
                Pitch = 270.5;
                g_cAimbot.AA[static_cast<C_BaseEntity*>(pStruct)->index] = true;
        }
        else
                g_cAimbot.AA[static_cast<C_BaseEntity*>(pStruct)->index] = false;
        *(float*)pOut = Pitch;
}

void new_CSPlayer_FlashVariables( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
        if(gCvar.rem_noflash)
                *(float*)pOut = 0.0f;
}

void StealNames()
{
        static ConVar* pName;

        if( !pName )
        {
                pName = g_pCvar->FindVar( "name" );
                pName->m_fnChangeCallback = NULL;
        }

        player_info_t pInfo;
   
        int index = rand() % g_pGlobals->maxClients;
        if(!g_pEntList->GetClientEntity(index) || g_pEngine->GetLocalPlayer() == index)
                return;
   
        g_pEngine->GetPlayerInfo( index, &pInfo );
        pName->SetValue(pInfo.name);
}

void StealNames1()
{
        static ConVar* pName;

        if( !pName )
        {
                pName = g_pCvar->FindVar( "name" );
                pName->m_fnChangeCallback = NULL;
        }

        player_info_t pInfo;
   
        int index = rand() % g_pGlobals->maxClients;
        if(!g_pEntList->GetClientEntity(index) || g_pEngine->GetLocalPlayer() == index)
                return;
   
        g_pEngine->GetPlayerInfo( index, &pInfo );
        pName->SetValue(pInfo.guid);
}

void StealNames2()
{
        static ConVar* pName;

        if( !pName )
        {
                pName = g_pCvar->FindVar( "name" );
                pName->m_fnChangeCallback = NULL;
        }

        player_info_t pInfo;
   
        int index = rand() % g_pGlobals->maxClients;
        if(!g_pEntList->GetClientEntity(index) || g_pEngine->GetLocalPlayer() == index)
                return;
   
        g_pEngine->GetPlayerInfo( index, &pInfo );
        pName->SetValue(pInfo.userID);
}


void new_ParticleSmokeGrenade_flSpawnTime( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
        if(gCvar.rem_nosmoke)
                *(float*)pOut = 0.0f;
}

DWORD g_dwOrgInKeyEvent;
int __stdcall new_IN_KeyEvent ( int eventcode, ButtonCode_t keynum, const char *pszCurrentBinding )
{
        int RetValue;
        __asm
        {
                PUSH pszCurrentBinding
                        PUSH keynum
                        PUSH eventcode
                        CALL g_dwOrgInKeyEvent
                        MOV RetValue, EAX;
        }

        //Mouse & GUI
        if( gMouse.ActiveMouse && (keynum >= 107 && keynum <= 113) && keynum!=72 )
        {
                return 0;
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

        if ( !g_pEngine->IsInGame() || !g_pInput )
                return;

        CInput::CVerifiedUserCmd *g_pVerifiedCommands = *(CInput::CVerifiedUserCmd**)( (DWORD)g_pInput + 0xB8 );

        if ( !g_pVerifiedCommands )
                return;

        CInput::CVerifiedUserCmd *pVerified = &g_pVerifiedCommands[ sequence_number % MULTIPLAYER_BACKUP ];

        CUserCmd* pCmd = g_pInput->GetUserCmd( sequence_number );

        //pCmd == CUserCmd
        if ( !pCmd || !pVerified )
                return; 

        //store the current movement vectors
        Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);// FJERN z HVIS DU GoR SKVT LOLLLL
        float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw, flPitch;
        QAngle qMove, qRealView(pCmd->viewangles);
        VectorAngles(vMove, qMove);
        static bool bShoot = true;
        //----------------------------------//

        if(gCvar.misc_speedhack)
        {
                ConVar *cheats = g_pCvar->FindVar( "sv_cheats" ); ConVar *consistency = g_pCvar->FindVar( "sv_consistency" );
                cheats->SetValue(1);
                consistency->SetValue(0);
                ConVar *framerate = g_pCvar->FindVar("host_timescale");
                if(GetAsyncKeyState(69))
                {
                        framerate->SetValue(8);
                }
                else
                {
                        framerate->SetValue(1);
                }
        }

        if( pCmd->buttons & IN_ATTACK && gCvar.aim_spraydown )
        {
                pCmd->viewangles.x += 0.09f;
                g_pEngine->SetViewAngles(pCmd->viewangles);
        }

        C_BaseEntity*pBaseEntity = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );

        if(GetAsyncKeyState(1));
        {
                g_cAimbot.Main(pCmd);
        }

        int iFlags = *(PINT)((DWORD)pBaseEntity + 0x2E4);

        if(g_cAimbot.TriggerBot(pCmd, pBaseEntity) && gCvar.aim_triggerbot)
                pCmd->buttons |= IN_ATTACK;

        // Bhop
        if( pCmd->buttons &IN_JUMP && !( iFlags&FL_ONGROUND ) && gCvar.misc_bunnyhop )
        {
                pCmd->buttons &= ~IN_JUMP;
        }

        bool isAttackingBeforeFix = ( pCmd->buttons& IN_ATTACK );

        if ( isAttackingBeforeFix && !gUtils.CanFire( pBaseEntity ) )
        {
                pCmd->buttons &= ~IN_ATTACK;// lets test
        }

        if(gCvar.esp_wc)
        {
                g_pCvar->FindVar("mat_showmiplevels")->SetValue("2");
        }
        else
        {
                g_pCvar->FindVar("mat_showmiplevels")->SetValue("0");
        }

        if(gCvar.vis_badq)
        {
                g_pCvar->FindVar("mat_showlowresimage")->SetValue("1");
        }
        else
        {
                g_pCvar->FindVar("mat_showlowresimage")->SetValue("0");
        }

        if(gCvar.misc_spycam)
        {
                g_pCvar->FindVar("mat_showframebuffertexture")->SetValue("1");
        }
        else
        {
                g_pCvar->FindVar("mat_showframebuffertexture")->SetValue("0");
        }

        if(pCmd->buttons & IN_ATTACK & gCvar.rem_norecoil && !gCvar.aim_smooth)
        {
                QAngle punchAngle = *(QAngle*)((DWORD)pBaseEntity + 0xDA8);
                QAngle qPunch = punchAngle; float Length = VectorNormalize(qPunch.Base());
                Length-= (10.0 + Length * 0.5) * g_pGlobals->interval_per_tick; qPunch *= Length;
                pCmd->viewangles -= qPunch + qPunch;
                //float flLength = VectorNormalize(punchAngle.Base());
                //flLength-= (10.0 + flLength * 0.5) * g_pGlobals->interval_per_tick;
                //punchAngle *= flLength;

                //pCmd->viewangles.x += punchAngle.x *2;
                //pCmd->viewangles.y -= punchAngle.y *2;
                //pCmd->viewangles.z -= punchAngle.z *2;
        }

        if(pCmd->buttons & IN_ATTACK & gCvar.rem_nospread)
        {
                gNospread.GetSpreadFix(pCmd,pBaseEntity);
        }

        if(gCvar.aim_pred)
        {
                gNospread.RCS(pCmd,pBaseEntity);
        }


        //    if(!(pCmd->buttons & IN_ATTACK) && !(pCmd->buttons & IN_ATTACK2) && !(pCmd->buttons & IN_USE) & gCvar.misc_spinbot)
        //    {   
        //    float forward    = pCmd->forwardmove;
        //    float right        = pCmd->sidemove;
        //    float up        = pCmd->upmove;
        //    int rand_factor = -360;


        //    Vector vForward,vRight,vUp,aForward,aRight,aUp,nForward,nRight,nUp;
        //    AngleVectors(pCmd->viewangles, &vForward, &vRight, &vUp);
        //    float time = g_pEngine->Time();

        //    pCmd->viewangles.y = fmod(GetTickCount() / 0.001f * 360.f, 360.f);

        //    AngleVectors(pCmd->viewangles,&aForward,&aRight,&aUp);
        //    g_cAimbot.Normalize(vForward,nForward);
        //    g_cAimbot.Normalize(vRight,nRight);
        //    g_cAimbot.Normalize(vUp,nUp);
        //    pCmd->forwardmove = DotProduct(forward * nForward,aForward) + DotProduct(right * nRight,aForward) + DotProduct(up * nUp,aForward);
        //    pCmd->sidemove = DotProduct(forward * nForward,aRight) + DotProduct(right * nRight,aRight) + DotProduct(up * nUp,aRight);
        //    pCmd->upmove = DotProduct(forward * nForward,aUp) + DotProduct(right * nRight,aUp) + DotProduct(up * nUp,aUp);

        //    //flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);

        //    //pCmd->forwardmove = -cos(flYaw) * flSpeed;

        //    //pCmd->sidemove *= -1;

        //    pCmd->sidemove = sin(flYaw) * flSpeed;
        //}

        //if(!(pCmd->buttons & IN_ATTACK) & gCvar.aa_on)
        //{
        //    Vector Velocity = *(Vector*)((DWORD)pBaseEntity + 0xF0);
        //    bool flipY = ( ( Velocity.Length() == 0 ) && ( ( RandomInt( 0, 100 ) % 2 ) != 1 ) );

        //    //pCmd->viewangles.y -= 180;

        //    //pCmd->viewangles.y -= ( !flipY ) ? ( ( ( RandomInt( 0, 100 ) % 2 ) == 0 ) ? 180.f : 180.f ) : 0.f;
        //    pCmd->viewangles.x = 180;
        //    pCmd->viewangles.y -= ( !flipY ) ? ( ( ( RandomInt( 0, 100 ) % 2 ) == 0 ) ? -180.f : 180.f ) : 0.f;

        //    //pCmd->viewangles.y -= ( ( (RandomInt(0, 100 ) % 2 ) == 0 ) );
        //    //pCmd->viewangles.x -= ( ( (RandomInt(0, 100 ) % 2 ) == 0 ) );
        //    //pCmd->viewangles.z -= RandomFloat(90,270);

        //   // pCmd->forwardmove *= -1;

        //    //pCmd->sidemove *= -1;

        //    float yaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);

        //    pCmd->forwardmove = -cos(yaw) *flSpeed;

        //    //pCmd->forwardmove = -cos(yaw) *flSpeed;

        //    pCmd->sidemove = sin(yaw) *flSpeed;

        //    //pCmd->sidemove = sin(flYaw) * flSpeed;

        //    //if ( flipY )
        //    //{
        //    //pCmd->forwardmove *= -1;
        //    //}
        //}
        //else if(!(pCmd->buttons & IN_ATTACK) & gCvar.aa_on)
        //{
        //    Vector Velocity = *(Vector*)((DWORD)pBaseEntity + 0xF0);
        //    bool flipY = ( ( Velocity.Length() == 0 ) && ( ( RandomInt( 0, 100 ) % 2  ) != 0 ) );
        //       
        //    //QAngle qRecoil, SpreadFix;
        //    //qRecoil = gNospread.Recoil(pBaseEntity);
        //    //gNospread.GetSpreadFix(pCmd->random_seed, pCmd->viewangles,SpreadFix);
        //   
        //    //pCmd->viewangles.y -= 180;

        //    pCmd->viewangles.y += ( !flipY ) ? ( ( ( RandomInt( 0, 100 ) % 2 ) == 0 ) ? 180.f : -180.f ) : 0.f;
        //    pCmd->viewangles.x = 180;

        //    //pCmd->viewangles.y -= ( ( (RandomInt(0, 100 ) % 2 ) == 0 ) );
        //    //pCmd->viewangles.x -= ( ( (RandomInt(0, 100 ) % 2 ) == 0 ) );

        //    //pCmd->viewangles.y -= ( !flipY ) ? -180.f : 180.f ? ( !flipY ) : 0.f;

        //    flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);

        //    pCmd->forwardmove = -cos(flYaw) * flSpeed;

        //    pCmd->sidemove *= -1;

        //    if ( flipY )
        //    {
        //    pCmd->forwardmove *= -1;
        //    }
        //}



        if(!(pCmd->buttons & IN_ATTACK))
        {   

                Vector Velocity = *(Vector*)((DWORD)pBaseEntity + 0xF0);
                bool flipY = ( ( Velocity.Length() == 0 ) && ( ( RandomInt( 0, 100 ) % 2  ) != 0 ) );

                bool lol = ( ( RandomInt(0, 100) % 2 ) != 0 );

                //    //QAngle qRecoil, SpreadFix;
                //    //qRecoil = gNospread.Recoil(pBaseEntity);
                //    //gNospread.GetSpreadFix(pCmd->random_seed, pCmd->viewangles,SpreadFix);
                /*pCmd->viewangles.x = 155;
                  pCmd->viewangles.y -= 180;*/
                //pCmd->viewangles.x = 180;

                RandomSeed( pCmd->random_seed );
                pCmd->viewangles.x = 180;
                pCmd->viewangles.y -= ( !flipY ) ? ( ( ( RandomInt( 0, 100 ) % 2 ) == 0 ) ? -180 : 180 ) : 0.f;
                //    //pCmd->viewangles.y -= pCmd->viewangles.z;

                if ( flipY )
                {
                        pCmd->forwardmove *= -1;
                }

                flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);

                pCmd->forwardmove = -cos(flYaw) * flSpeed;

                pCmd->sidemove = sin(flYaw) * flSpeed;
        }
        ////else if (!(pCmd->buttons & IN_ATTACK) & if(pCmd->buttons & IN_DUCK)
        else if(!(pCmd->buttons & IN_ATTACK ))
        {
                Vector Velocity = *(Vector*)((DWORD)pBaseEntity + 0xF0);
                bool flipY = ( ( Velocity.Length() == 0 ) && ( ( RandomInt( 0, 100 ) % 2  ) != 0 ) );

                //    //QAngle qRecoil, SpreadFix;
                //    //qRecoil = gNospread.Recoil(pBaseEntity);
                //    //gNospread.GetSpreadFix(pCmd->random_seed, pCmd->viewangles,SpreadFix);

                RandomSeed( pCmd->random_seed );

                //    QAngle angles;   
                ////    pCmd->viewangles.y -= !flipY ? ( ( ( RandomInt( 0, 100 ) % 2 ) == 0 ) ): pCmd->viewangles.y - 180.f;
                ////    pCmd->viewangles.x = 180;
                //    angles.Init(0.0f,pCmd->viewangles.y, 240.0f);
                //    angles.Init(0.0f,pCmd->viewangles.x, 110.0f);

                //pCmd->viewangles.y -= 180;
           
                pCmd->viewangles.y -= ( !flipY ) ? ( ( ( RandomInt( 0, 100 ) % 2 ) == 0 ) ? pCmd->viewangles.y : -180 ) : 0.f;
                //pCmd->viewangles.y -= ( !flipY ) ? ( ( ( RandomInt( 0, 100 ) % 2 ) == 0 ) ? -180 : pCmd->viewangles.y ) : 0.f;
                pCmd->viewangles.x = 180;
                //pCmd->viewangles.x = ( 88.f + RandomFloat( 0.f, 1.f ) );

                //    //pCmd->viewangles.y -= pCmd->viewangles.z;
                //    //pCmd->viewangles.z -= pCmd->viewangles.x;
                //    //pCmd->viewangles.x -= pCmd->viewangles.z;

                if ( flipY )
                {
                        pCmd->forwardmove *= -1;
                }

                flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);

                pCmd->forwardmove = -cos(flYaw) * flSpeed;

                //    pCmd->forwardmove *= -1;

                pCmd->sidemove *= -1;

                //pCmd->sidemove = sin(flYaw) * flSpeed;
        }
        if(gCvar.misc_namestealer)
                StealNames();

        if(gCvar.misc_namestealer1)
                StealNames1();

        if(gCvar.misc_namestealer2)
                StealNames2();

        pVerified->m_cmd = *pCmd;
        pVerified->m_crc =  pCmd->GetChecksum();
}


//if( !( pCmd->buttons &IN_ATTACK && gCvar.aa_on ) /*&& gNospread.getWeaponID() != WP_KNIFE*/ )
//{
//    //gAimbot.m_nTarget = -1;
//    /*
//    Vector vMove( pUserCmd->forwardmove, pUserCmd->sidemove, pUserCmd->upmove );
//    float flSpeed = vMove.Length();
//    QAngle Move, RealView( pUserCmd->viewangles );
//    VectorAngles( vMove, Move );
//    */
//
//        pCmd->viewangles.x = 180;
//        pCmd->viewangles.y -= 180;
//
//        //ZBLOCK FIX
//        *(float*)((DWORD)pBaseEntity + 0x13F8) = pCmd->viewangles.x; //m_angEyeAngles[0]
//        *(float*)((DWORD)pBaseEntity + 0x13FC) = pCmd->viewangles.y; //m_angEyeAngles[1]
//
//        //pBaseEntity->OnDataChanged( DATA_UPDATE_DATATABLE_CHANGED );
//
//        /*
//        float flPitch = DEG2RAD( pUserCmd->viewangles.x - RealView.x + Move.x );
//        float flYaw = DEG2RAD( pUserCmd->viewangles.y - RealView.y + Move.y );
//        float flRoll = DEG2RAD( pUserCmd->viewangles.z - RealView.z + Move.z );
//
//        pUserCmd->forwardmove = -( cos( flYaw ) * flSpeed );
//        pUserCmd->sidemove = -( ( sin( flYaw ) * -cos( flRoll ) + -cos( flPitch ) * sin( flYaw ) ) * flSpeed );
//        pUserCmd->upmove = ( ( sin( flPitch ) * -cos( flRoll ) ) * flSpeed );
//        */
//
//        flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
//
//        pCmd->forwardmove = -cos(flYaw) * flSpeed;
//
//        pCmd->sidemove = sin(flYaw) * flSpeed;
//
//        if ( pBaseEntity->GetMoveType( ) == MOVETYPE_LADDER );
//        //{
//        //    pCmd->sidemove *= -1;
//        //}
//}
//    if(gCvar.misc_namestealer)
//        StealNames();
//
//    if(gCvar.misc_namestealer1)
//        StealNames1();
//
//    if(gCvar.misc_namestealer2)
//        StealNames2();
//
//    pVerified->m_cmd = *pCmd;
//    pVerified->m_crc =  pCmd->GetChecksum();
//}

//if( !( pCmd->buttons &IN_ATTACK ) )
//{
//    pCmd->viewangles.y -= 179;
//    pCmd->viewangles.x = 179;
//
//    flYaw = DEG2RAD(pCmd->viewangles.y - qRealView.y + qMove.y);
//
//    pCmd->forwardmove = -cos(flYaw) * flSpeed;
//
//    pCmd->sidemove = sin(flYaw) * flSpeed;
//
//}
//if(gCvar.misc_namestealer)
//    StealNames();
//
//if(gCvar.misc_namestealer1)
//    StealNames1();
//
//if(gCvar.misc_namestealer2)
//    StealNames2();
//
//pVerified->m_cmd = *pCmd;
//pVerified->m_crc =  pCmd->GetChecksum();
//}

//DWORD g_dwOrgFrameStageNotify;
//void __stdcall new_FrameStageNotify( ClientFrameStage_t curStage )
//{
//
//    _asm
//    {
//        PUSH curStage
//            CALL g_dwOrgFrameStageNotify
//    }
//
//    if(!g_pEngine->IsInGame() || g_pEngine->IsHLTV() == true || g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer()) == NULL)
//        return;
//
//    CBaseEntity *pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
//
//    if(curStage == FRAME_RENDER_START && pLocal != NULL && gCvar.rem_novisrecoil)
//    {
//        QAngle view;
//        g_pEngine->GetViewAngles(view);
//        QAngle* RenderAngle = ( QAngle* )( (DWORD)GetModuleHandle("client.dll") + 0x6F9B74 );
//        QAngle qDifference = QAngle(view.x - RenderAngle->x, view.y - RenderAngle->y, view.z - RenderAngle->z);
//
//        if((qDifference.x || qDifference.y))
//        {
//            RenderAngle->x += qDifference.x;
//            RenderAngle->y += qDifference.y;
//        }
//    }
//}

DWORD g_dwOrgFrameStageNotify;
void __stdcall new_FrameStageNotify( ClientFrameStage_t curStage )
{
        C_BaseEntity *pMe;
        QAngle *PunchAngle, OldPunch;
        bool bShouldRestore = false;

        if( g_pEngine->IsInGame() )
        {
                pMe = dynamic_cast<C_BaseEntity*>( g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() ) );
        }

        if(gCvar.rem_novisrecoil)
        {
                if( curStage == FRAME_RENDER_START )
                {
                        if( g_pEngine->IsInGame() )
                        {
                                if( pMe && !pMe->IsDormant() )
                                {
                                        if( g_cAimbot.IsAlive( pMe ) )
                                        {
                                                PunchAngle = reinterpret_cast<QAngle*>( (size_t)pMe + 0xDA8 );
                                                if( *PunchAngle != QAngle( 0, 0, 0 ) )
                                                {
                                                        OldPunch = *PunchAngle;
                                                        *PunchAngle = QAngle( 0, 0, 0 );
                                                        bShouldRestore = true;
                                                }
                                        }
                                }
                        }
                }
        }

        _asm
        {
                PUSH curStage
                        MOV ECX, g_pClient
                        CALL g_dwOrgFrameStageNotify
                        }

        if( curStage == FRAME_RENDER_START )
        {
                if( bShouldRestore )
                {
                        *PunchAngle = OldPunch;
                }
        }
}

void FillRGBA( int x, int y, int w, int h, DWORD colour ){
        g_pMatSystemSurface->DrawSetColor( RED(colour), GREEN(colour), BLUE(colour), ALPHA(colour) );
        g_pMatSystemSurface->DrawFilledRect( x, y, x + w, y + h );
}
bool ScreenTransforme( const Vector &point, Vector &screen ){
        float w;
        const VMatrix &worldToScreen = g_pEngine->WorldToScreenMatrix();
        screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
        screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
        w         = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
        screen.z = 0.0f;
        bool behind = false;
        if( w < 0.001f ){
                behind = true;
                screen.x *= 100000;
                screen.y *= 100000;
        }
        else{
                behind = false;
                float invw = 1.0f / w;
                screen.x *= invw;
                screen.y *= invw;
        }
        return behind;
}
void GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter ){
        if ( pBaseEnt ){
                Vector vMin, vMax;
                pBaseEnt->GetRenderBounds( vMin, vMax );
                vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
                vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;
        }
}
bool WorldToScreen( const Vector &vOrigin, Vector &vScreen ){
        if( ScreenTransforme(vOrigin , vScreen) == false ){
                int iScreenWidth, iScreenHeight;
                g_pEngine->GetScreenSize( iScreenWidth, iScreenHeight );
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
bool TransformVector( Vector v, Vector &s ){
        if( ScreenTransforme( v, s ) == false ){
                int sw, sh;
                g_pEngine->GetScreenSize( sw, sh );
                float x = sw / 2;
                float y = sh / 2;
                x += 0.5 * s.x * sw + 0.5;
                y -= 0.5 * s.y * sh + 0.5;
                s.x = x;
                s.y = y;
                return true;
        }
        return false;
}
void DrawHealthBox( int x, int y, DWORD colour, int CurHealth, int MaxHealth ){
        if( CurHealth == 0 || MaxHealth == 0 )
                return;
        float mx = MaxHealth / 4;
        float wx = CurHealth / 4;
        if( mx == 0 ) return;
        x -= ( mx / 2 );
        FillRGBA(x-1,y-1,mx + 2,4+2,COLORCODE(0,0,0,255));
        FillRGBA( x, y, wx, 4,colour );
}//well make rs later
void CustomBorder(int x,int y,int w, int h, DWORD dwBorderColor){
        FillRGBA( x-1, y-1, w+2, 1 ,dwBorderColor); //top
        FillRGBA( x-1, y, 1, h-1 ,dwBorderColor );    //left
        FillRGBA( x+w, y, 1, h-1 ,dwBorderColor);    //right
        FillRGBA( x-1, y+h-1, w+2, 1 ,dwBorderColor);}
void DrawBoundingBox( float flYaw, const Vector vMins, const Vector vMaxs, const Color BoxColour, const Vector vPosition, C_BaseEntity *pEnt, DWORD colour ){
        Vector mon, nom;
        nom = pEnt->GetAbsOrigin();
        C_BaseEntity*pMenig = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
        int flags = *(int*)((DWORD)pMenig + 0x2E4);
        int health = *(int*)((DWORD)pEnt + 0x90);
        if(flags & FL_DUCKING)
                mon = nom + Vector( 0, 0, 50.f );
        else
                mon = nom + Vector( 0, 0, 70.f );
        Vector bot, top;
        if( TransformVector( nom, bot ) && TransformVector( mon, top ) ){
                float h = ( bot.y - top.y );
                float w = h / 4.f;
                if(gCvar.esp_box)
                        CustomBorder(top.x - w, top.y, w * 2, ( bot.y - top.y ), colour );
                if(gCvar.esp_healthbar)
                        DrawHealthBox(top.x - w,top.y+w*0+0,COLORCODE(0,255,0,255),health,100.0f);
        }
        Vector vPoints[8];

        //bool bShouldDisableDepthTest = !g_cAimbot.( vMyPosition, vPosition );

        Vector vRight, vUp, vForward;
        AngleVectors( QAngle( 0, flYaw, 0 ), &vForward, &vRight, &vUp );

        Vector Delta = ( ( vMaxs - vMins ) * .5f );

        vRight *= Delta.y;
        vForward *= Delta.x;

        Vector vTop = vPosition;
        vTop.z += ( Delta.z * 2 );

        vPoints[0] = vTop + vRight + vForward;
        vPoints[1] = vTop + vRight - vForward;
        vPoints[2] = vTop - vRight - vForward;
        vPoints[3] = vTop - vRight + vForward;

        vPoints[4] = vPosition + vRight + vForward;
        vPoints[5] = vPosition + vRight - vForward;
        vPoints[6] = vPosition - vRight - vForward;
        vPoints[7] = vPosition - vRight + vForward;

        if ( BoxColour != Color(255,0,0) && BoxColour != Color(0,0,255))
        {
                return;
        }

        for( int nIndex = 0; nIndex < 8; ++nIndex )
        {
                int nNext = nIndex + 1;
                if( ( nIndex % 4 ) == 3 )
                {
                        nNext -= 4;
                }

                g_pDebugOverlay->AddLineOverlay( vPoints[nIndex], vPoints[nNext], BoxColour.r(), BoxColour.g(), BoxColour.b(), true, ( g_pGlobals->frametime + g_pGlobals->frametime ) );
        }

        for( int nIndex = 0; nIndex < 4; ++nIndex )
        {
                int nNext = nIndex + 4;

                g_pDebugOverlay->AddLineOverlay( vPoints[nIndex], vPoints[nNext], BoxColour.r(), BoxColour.g(), BoxColour.b(), true, ( g_pGlobals->frametime + g_pGlobals->frametime ) );
        }
}

CBaseEntity* GetEntityByIndexes( int idx ){
        if( g_pEntList == NULL ) return NULL;
        IClientEntity *pClient = g_pEntList->GetClientEntity( idx );
        if( pClient == NULL ) return NULL;
        return pClient->GetBaseEntity();
}

QAngle &GetEyeAngles(C_BaseEntity* pEntity)
{
        Vector m_VecOrigin = *(Vector*)((DWORD)pEntity + 0x2CC);
        Vector m_vecViewOffset = *(Vector*)((DWORD)pEntity + 0x0E4);
        Vector vEyePosition = (m_VecOrigin + m_vecViewOffset);
        QAngle qEyePostion = QAngle(0,0,0);
        VectorAngles(vEyePosition, qEyePostion);
        return qEyePostion;
}

matrix3x4_t &GetBoneMatrix(int iBone, C_BaseEntity* pBaseEnt)
{
        matrix3x4_t pMatrix[MAXSTUDIOBONES];
        pBaseEnt->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0);
        return pMatrix[iBone];
}   

Vector GetBonePosition(int bone_index, C_BaseEntity *pLocal, C_BaseEntity *pBaseEnt)
{
        Vector pos;
        QAngle EyeAngles = GetEyeAngles( pLocal );
        matrix3x4_t& BoneMatrix = GetBoneMatrix(bone_index, pBaseEnt);
        MatrixAngles(BoneMatrix,EyeAngles,pos);
        return pos;
}

void DrawString( int x, int y, int r, int g,int b, bool bCenter, const char *pszText, ... )
{
        va_list va_alist;
        char szBuffer[1024] = { '\0' };
        wchar_t wbuf[1024] = { '\0' };
        va_start( va_alist, pszText );
        vsprintf( szBuffer, pszText, va_alist );
        va_end( va_alist );
        wsprintfW( wbuf, L"%S", szBuffer );
        int iWidth, iHeight;
        g_pMatSystemSurface->GetTextSize( font, wbuf, iWidth, iHeight );
        g_pMatSystemSurface->DrawSetTextFont( font );
        g_pMatSystemSurface->DrawSetTextColor( r, g, b, 255);
        g_pMatSystemSurface->DrawSetTextPos( x - ( bCenter ? iWidth / 2 : 0 ), y );
        g_pMatSystemSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

void EntityEsp( void )
{

        if(!gCvar.esp_entity)//// lol
                return;


        for ( int index = 0; index < g_pEngine->GetMaxClients(); index++ )
        {

                if ( index == g_pEngine->GetLocalPlayer() )
                        continue;

                IClientEntity* ClientEntity = (IClientEntity*)g_pEntList->GetClientEntity( index );

                if ( ClientEntity == NULL || ClientEntity->IsDormant() )
                        continue;

                C_BaseEntity* TargetEntity = (C_BaseEntity*)ClientEntity->GetBaseEntity();

                if ( TargetEntity == NULL || TargetEntity->IsDormant() )
                        continue;

                if(g_cAimbot.IsAlive(TargetEntity))
                {

                        Vector vMins = *reinterpret_cast<Vector*>( (size_t)TargetEntity + ( 0x168 + 0x8 ) );
                        Vector vMaxs = *reinterpret_cast<Vector*>( (size_t)TargetEntity + ( 0x168 + 0x14 ) );

                        Color teamcolor;

                        if ( g_cAimbot.GetTeamNumber( TargetEntity ) == 3 )
                                teamcolor.SetColor(0,0,255);
                        else if ( g_cAimbot.GetTeamNumber( TargetEntity ) == 2 )
                                teamcolor.SetColor(255,0,0);
                        //0x13fc
                        float flYaw = *reinterpret_cast<float*>( (size_t)TargetEntity + 0x140C );// weapon esp er os til.. O
                        Vector RenderMins, RenderMaxs;
                        DWORD skede;
                        TargetEntity->GetRenderBounds( RenderMins, RenderMaxs );
                        vMins.z = RenderMins.z;
                        vMaxs.z = RenderMaxs.z;

                        DrawBoundingBox( flYaw, vMins, vMaxs, teamcolor, TargetEntity->GetRenderOrigin(), TargetEntity, skede);

                        //det her vil ikke virke alligevel..
                        /*
                          const char* modelName = g_pModelinfo->GetModelName(TargetEntity->GetModel());

                          if( modelName )
                          {
                          //Starting of Weapon Entity Detection...
                          if( strstr( modelName, "w_" ) )
                          {   
                          CBaseCombatWeapon* pWeap = static_cast<CBaseCombatWeapon*>(TargetEntity);//<-- failure anyway try now!!! OMG SRSLY??!?!??!

                          if( pWeap )
                          {
                          Vector vWeapScreen, vWeapWorldPos;
                          GetWorldSpaceCenter( TargetEntity, vWeapWorldPos );

                          if ( WorldToScreen( vWeapWorldPos, vWeapScreen ) )
                          {
                          int m_iState = *(int*)((DWORD)pWeap + 0x16A4);

                          if ( m_iState == WEAPON_IS_CARRIED_BY_PLAYER )
                          {

                          }
                          else
                          {
                          if(m_iState == WEAPON_NOT_CARRIED) // Weapon is on the ground
                          {
                          if(strstr(modelName, "knife"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,true,"%s","Knife");
                          if(strstr(modelName, "m4"))
                          {
                          if(strstr(modelName,"silenced"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","M4A1 Silenced");
                          else
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","M4A1");
                          }
                          if(strstr(modelName, "ak"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","AK-47");
                          if(strstr(modelName, "tmp"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","TMP");
                          if(strstr(modelName, "aug"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","AUG");
                          if(strstr(modelName, "g3sg1"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","G3SG1");
                          if(strstr(modelName, "m3super90"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","M3");
                          if(strstr(modelName, "mac10"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Mac 10");
                          if(strstr(modelName, "p90"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","P90");
                          if(strstr(modelName, "scout"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Scout");
                          if(strstr(modelName, "sg500"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","SG500");
                          if(strstr(modelName, "usp"))
                          {
                          if(strstr(modelName,"silenced"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","USP Silenced");
                          else
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","USP");
                          }
                          if(strstr(modelName, "elites"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Dual Elites");
                          if(strstr(modelName, "ump45"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","UMP45");
                          if(strstr(modelName, "awp"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Awp");
                          if(strstr(modelName, "famas"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Famas");
                          if(strstr(modelName, "galil"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Galil");
                          if(strstr(modelName, "mp5"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Mp5");
                          if(strstr(modelName, "m249para"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","M249");
                          if(strstr(modelName, "sg552"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","SG552");
                          if(strstr(modelName, "xm1014"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","XM1014");
                          if(strstr(modelName, "glock18"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Glock");
                          if(strstr(modelName, "deagle"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Deagle");
                          if(strstr(modelName, "p228"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","P228");
                          if(strstr(modelName, "fiveseven"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Fiveseven");//red green blue
                          if(strstr(modelName, "c4"))
                          {
                          if(strstr(modelName,"planted"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,0,0,false,"%s","*-Bomb Planted-*");
                          else
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,0,0,false,"%s","*-Bomb-*");
                          }
                          if(strstr(modelName, "frag"))
                          {
                          if(strstr(modelName,"thrown"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,0,0,false,"%s","Frag Grenade Thrown");
                          else
                          DrawString(vWeapScreen.x,vWeapScreen.y,0,255,0,false,"%s","Frag Grenade");
                          }
                          if(strstr(modelName, "smoke"))
                          {
                          if(strstr(modelName,"thrown"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,0,0,false,"%s","Smokegrenade Thrown");
                          else
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Smokegrenade");
                          }
                          if(strstr(modelName, "flash"))
                          {
                          if(strstr(modelName,"thrown"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,0,0,false,"%s","Flashbang Thrown");
                          else
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,false,"%s","Flashbang");
                          }
                          if(strstr(modelName, "defuser"))
                          DrawString(vWeapScreen.x,vWeapScreen.y,255,255,255,true,"%s","Defuse Kit");
                          }
                          }
                          }
                          }
                          }
                          }
                        */
                }
        }
}

DWORD g_dwOrgPaintTraverse;
void __stdcall new_PaintTraverse(vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce){//drawing
        _asm
        {
                PUSH allowForce
                        PUSH forceRepaint
                        PUSH vguiPanel
                        MOV ECX, g_pPanel
                        CALL g_dwOrgPaintTraverse
                        }


        gEvent.RegisterSelf();
        int iScreenSize[2];
        g_pEngine->GetScreenSize(iScreenSize[0], iScreenSize[1]);
        int iScreenCenter[2] = { iScreenSize[0] * 0.5, iScreenSize[1] * 0.5 };
        const char* pszPanelName = g_pPanel->GetName(vguiPanel);
        if(pszPanelName[0] == 'M'
           && pszPanelName[3] == 'S'
           && pszPanelName[9] == 'T'
           && pszPanelName[12] == 'P')
        {
       
                // draw a simple crosshair
                if(gCvar.vis_crosshair){
                        g_pMatSystemSurface->DrawSetColor(255, 0, 0, 255);
                        g_pMatSystemSurface->DrawFilledRect(iScreenCenter[0] - 15, iScreenCenter[1], iScreenCenter[0] + 17, iScreenCenter[1] + 2);
                        g_pMatSystemSurface->DrawFilledRect(iScreenCenter[0], iScreenCenter[1] - 17, iScreenCenter[0] + 2, iScreenCenter[1] + 15);
                        g_pEngine->ExecuteClientCmd("crosshair 0");
           
                }

                gGui.DrawMenu(gCvar.pos_bx, gCvar.pos_by, gCvar.pos_bw, gCvar.pos_bh, "DelupeAim VIP");
                gMouse.DrawMouse();
                gMouse.ClickHandler();

                C_BaseEntity*pLocal = (C_BaseEntity*)g_pEntList->GetClientEntity( g_pEngine->GetLocalPlayer() );
                for(int index = 1; index <= g_pEngine->GetMaxClients(); index++)
                {
                        C_BaseEntity* pBaseEnt = GetEntityByIndexes(index);
                        if(pBaseEnt == NULL)
                                continue;
                        if( pBaseEnt->index == pLocal->index )
                                continue;
                        if( stricmp( pBaseEnt->GetClientClass()->GetName(), "CCSPlayer" ) == 0 ){
                                player_info_t pinfo;
                                char lifeState = *(char*)((DWORD)pBaseEnt + 0x8F);
                                int health = *(int*)((DWORD)pBaseEnt + 0x90);
                                if( lifeState != LIFE_ALIVE )
                                        continue;
                                if( health <= 0 )
                                        continue;
                                if( g_pEngine->GetPlayerInfo( pBaseEnt->index, &pinfo ) == false )
                                        continue;
                                Vector m_vecWorld,vScreen;
                                GetWorldSpaceCenter(pBaseEnt,m_vecWorld);
                                if(WorldToScreen(m_vecWorld,vScreen)){
                                        int teamnum = *(int*)((DWORD)pBaseEnt + 0x98);
                                        DWORD colour = COLORCODE(255,255,255,255);
                                        if(g_cAimbot.GetVisible(g_cAimbot.GetPredictedEyePosition(pLocal),pBaseEnt, pBaseEnt)){
                                                if(teamnum == 2)//T
                                                        colour = COLORCODE(255,0,0,255);
                                                if(teamnum == 3)//CT
                                                        colour = COLORCODE(0,0,255,255);}
                                        else if(!g_cAimbot.GetVisible(g_cAimbot.GetPredictedEyePosition(pLocal),pBaseEnt, pBaseEnt)){
                                                if(teamnum == 2)//T
                                                        colour = COLORCODE(255,255,0,255);
                                                if(teamnum == 3)//CT
                                                        colour = COLORCODE(0,255,0,255);


                                                Color teamcolor;
                                                DrawBoundingBox(0,0,0,teamcolor,colour,pBaseEnt,colour);       

                                                if(gCvar.vis_skeleton == 1)
                                                {

                                                        int r, g, b;
                                                        Vector &vPos = (Vector&)pBaseEnt->GetAbsOrigin();
                                                        r = 255;
                                                        g = 255;
                                                        b = 255;

                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(0, pLocal, pBaseEnt), GetBonePosition(9, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(9, pLocal, pBaseEnt), GetBonePosition(10, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(10, pLocal, pBaseEnt), GetBonePosition(11, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(11, pLocal, pBaseEnt), GetBonePosition(12, pLocal, pBaseEnt), r, g, b, true, 0.019f);

                                                        //Neck + head
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(12, pLocal, pBaseEnt), GetBonePosition(13, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(13, pLocal, pBaseEnt), GetBonePosition(14, pLocal, pBaseEnt), r, g, b, true, 0.019f);

                                                        //Left Arm
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(12, pLocal, pBaseEnt), GetBonePosition(15, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(15, pLocal, pBaseEnt), GetBonePosition(16, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(16, pLocal, pBaseEnt), GetBonePosition(17, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(17, pLocal, pBaseEnt), GetBonePosition(18, pLocal, pBaseEnt), r, g, b, true, 0.019f);

                                                        //Right Arm
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(12, pLocal, pBaseEnt), GetBonePosition(28, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(28, pLocal, pBaseEnt), GetBonePosition(29, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(29, pLocal, pBaseEnt), GetBonePosition(30, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(30, pLocal, pBaseEnt), GetBonePosition(31, pLocal, pBaseEnt), r, g, b, true, 0.019f);

                                                        //Left leg
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(0, pLocal, pBaseEnt), GetBonePosition(1, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(1, pLocal, pBaseEnt), GetBonePosition(2, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(2, pLocal, pBaseEnt), GetBonePosition(3, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(3, pLocal, pBaseEnt), GetBonePosition(4, pLocal, pBaseEnt), r, g, b, true, 0.019f);

                                                        //Right leg
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(0, pLocal, pBaseEnt), GetBonePosition(5, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(5, pLocal, pBaseEnt), GetBonePosition(6, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(6, pLocal, pBaseEnt), GetBonePosition(7, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                        g_pDebugOverlay->AddLineOverlay(GetBonePosition(7, pLocal, pBaseEnt), GetBonePosition(8, pLocal, pBaseEnt), r, g, b, true, 0.019f);
                                                }

                                        }
                                }
                        }
                        //if(g_pEngine->IsInGame()){
                        //gMenu.DrawMenu();
                        //    gMenu.InitMenu();
                        EntityEsp();
                }
        }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


#include "main.h"

cAimbot g_cAimbot;

cAimbot::cAimbot()
{
        DropTarget();
}

void cAimbot::DropTarget()
{
        m_flBestDist = 99999.9f;
        m_nTarget = -1;
        m_vPosition = 0.0f;
}

void cAimbot::CalcAngle(Vector &vSource, Vector &vDestination, QAngle &qAngle)
{
        Vector vDelta(vSource - vDestination);
        float flHyp = sqrt((vDelta.x * vDelta.x) + (vDelta.y * vDelta.y));

        qAngle.x = RAD2DEG(atan(vDelta.z / flHyp));
        qAngle.y = RAD2DEG(atan(vDelta.y / vDelta.x));

        if(vDelta.x >= 0.0f)
                qAngle.y += 180.0f;
}

float GetDistance(Vector &vAbsStart, Vector &vAbsStop)
{
        float flLength = Vector(vAbsStop - vAbsStart).Length();
        float flDistance = sqrt(flLength);

        if(flDistance < 1.0f)
                flDistance = 1.0f;

        return flDistance;
}

//inline float GetInterpolationAmount( void )
//{
//    static INetChannelInfo* net_Info = g_pEngine->GetNetChannelInfo();
//    float net_Latency = ( net_Info->GetAvgLatency( FLOW_OUTGOING ) + net_Info->GetAvgLatency( FLOW_INCOMING ) ) * 0.5f;
//
//    return ( (g_pCvar->FindVar( "cl_interp_ratio" )->GetFloat() / g_pCvar->FindVar( "cl_updaterate" )->GetFloat()) + net_Latency);
//}
//
//EstimateAbsVelocityFn pfnEstimateAbsVelocity;
//Vector GetVelocity( C_BaseEntity* current_Entity )
//{
//    float current_LaggedMovementValue = *reinterpret_cast<float*>( (size_t)current_Entity + 0x11AC ); //m_flLaggedMovementValue
//    float current_Time = ( ( g_pGlobals->interval_per_tick * GetInterpolationAmount() ) * current_LaggedMovementValue );
//
//    float ent_gravity;
//
//    if (current_Entity->GetGravity() > 0.01)
//        ent_gravity = current_Entity->GetGravity();
//    else
//        ent_gravity = 1.0;
//
//    Vector current_Velocity;
//    pfnEstimateAbsVelocity(current_Entity->GetIClientEntity(), current_Velocity);
//    int current_Flags = *reinterpret_cast<int*>( (size_t)current_Entity + 0x2E4 );
//
//    if( !( current_Flags & FL_ONGROUND ) )
//    {
//        current_Velocity.z -= ( ent_gravity * g_pCvar->FindVar( "sv_gravity" )->GetFloat( ) * current_Time * 0.5f );
//    }
//
//    float current_VelocityModifier = *reinterpret_cast<float*>( (size_t)current_Entity + 0x13B8 ); //m_flVelocityModifier
//    current_Velocity *= ( current_VelocityModifier * current_Time );
//
//    return current_Velocity;
//}
////
//EstimateAbsVelocityFn pfnEstimateAbsVelocity;
//void cAimbot::PredictTarget(C_BaseEntity* pEnemy, Vector& vPos)
//{
//Vector vVelocity;
//pfnEstimateAbsVelocity(pEnemy, vVelocity);
//Vector vTargetVelocity =  ( vVelocity * g_pGlobals->interval_per_tick ) * 2;
//float frametime = 1.0f / g_pGlobals->frametime;
//float interp_ratio = g_pCvar->FindVar("cl_interp_ratio")->GetFloat() / g_pCvar->FindVar("cl_updaterate")->GetFloat();
//vPos += (vTargetVelocity / frametime) * interp_ratio;
//}

//EstimateAbsVelocityFn pfnEstimateAbsVelocity;
//void cAimbot::PredictTarget(int index)
//{
//    C_BaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
//    ConVar* psv_gravity = g_pCvar->FindVar( "sv_gravity" );
//    float interp = max(g_pCvar->FindVar("cl_interp")->GetFloat(), g_pCvar->FindVar("cl_interp_ratio")->GetFloat() / g_pCvar->FindVar("cl_updaterate")->GetFloat());
//    Vector vTargetVel;
//    pfnEstimateAbsVelocity(g_pEntList->GetClientEntity(index), vTargetVel);
//    if( !( pLocal->GetFlags() & FL_ONGROUND ) )
//    {
//    vTargetVel.z -= psv_gravity->GetFloat() * 0.5f * g_pGlobals->frametime;
//    vTargetVel.z += pLocal->GetBaseVelocity().z * g_pGlobals->frametime;
//    }
//    m_vPosition += vTargetVel * g_pGlobals->interval_per_tick * interp;
//}

//void cAimbot::PredictTarget(C_BaseEntity* pBaseEntity, Vector &vEyePos, C_BaseEntity *pMe)
//{
//    Vector vOld[65];
//    Vector vOldMe;
//    Vector vAccel[65];
//    Vector vMyAccel;
//    Vector vecEnemyVelocity = *(Vector*)((DWORD)pBaseEntity + 0xF0);
//    Vector vMyVel = *(Vector*)((DWORD)pMe + 0xF0);
//    Vector vDelta = vecEnemyVelocity - vOld[pBaseEntity->index];
//    vOld[pBaseEntity->index] = vecEnemyVelocity;
//    if(vDelta != Vector(0,0,0))
//        vAccel[pBaseEntity->index] = vDelta;
//
//    Vector vDeltaMe = vMyVel - vOldMe;
//    vOldMe = vMyVel;
//    if(vDeltaMe != Vector(0,0,0))
//        vMyAccel = vDeltaMe;
//
//    if(vAccel[pBaseEntity->index] != Vector(0,0,0) || vMyAccel != Vector(0,0,0))
//        m_vPosition += ( 1 / 2 * (vAccel[pBaseEntity->index] - vMyAccel) * Square(g_pGlobals->interval_per_tick) + (vecEnemyVelocity - vMyVel) * g_pGlobals->interval_per_tick + m_vPosition - vEyePos);
//}

//EstimateAbsVelocityFn pfnEstimateAbsVelocity;
//void cAimbot::PredictTarget(int index)
//{
//    C_BaseEntity* pEnt = g_pEntList->GetClientEntity(index)->GetBaseEntity();
//    Vector vLocalVel, vTargetVel;
//    pfnEstimateAbsVelocity(pEnt->GetIClientEntity(), vTargetVel);
//    pfnEstimateAbsVelocity(g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetIClientEntity(), vLocalVel);
//    Vector vTargetVelocity =  ( vTargetVel * g_pGlobals->interval_per_tick ) * 2;
//    Vector vLocalVelocity =  vLocalVel * g_pGlobals->interval_per_tick;
//    Vector vDeltaVelocity = vTargetVelocity - vLocalVelocity;
//    m_vPosition += vDeltaVelocity;
//}

//EstimateAbsVelocityFn pfnEstimateAbsVelocity;
//void cAimbot::PredictTarget(int index, Vector vTargetVel)
//{
//    Vector vLocalVel;
//    Vector vTargetVelocity =  ( vTargetVel * g_pGlobals->interval_per_tick ) * 2;
//    Vector vLocalVelocity =  vLocalVel * g_pGlobals->interval_per_tick;
//    Vector vDeltaVelocity = vTargetVelocity - vLocalVelocity;
//    m_vPosition += vDeltaVelocity;
//
//    float lol = g_pGlobals->interval_per_tick * 2;
//    m_vPosition += lol;
//
//    float test = g_pGlobals->frametime * 2;
//    m_vPosition += test;
//}

//
//inline float GetInterpolationAmount( void )
//{
//    //static INetChannelInfo* net_Info = g_pEngine->GetNetChannelInfo( );
//    //float net_Latency = ( net_Info->GetAvgLatency( FLOW_OUTGOING ) + net_Info->GetAvgLatency( FLOW_INCOMING ) ) * 0.5f;
//
//    return ( (g_pCvar->FindVar( "cl_interp_ratio" )->GetFloat() / g_pCvar->FindVar( "cl_updaterate" )->GetFloat()));
//}
//
//EstimateAbsVelocityFn pfnEstimateAbsVelocity;
//Vector GetVelocity( C_BaseEntity* current_Entity )
//{
//    float current_LaggedMovementValue = *reinterpret_cast<float*>( (size_t)current_Entity + 0x119C ); //m_flLaggedMovementValue
//    float current_Time = ( ( g_pGlobals->interval_per_tick * GetInterpolationAmount() ) * current_LaggedMovementValue );
//
//    float ent_gravity;
//
//    if (current_Entity->GetGravity() > 0.01)
//        ent_gravity = current_Entity->GetGravity();
//    else
//        ent_gravity = 1.0;
//
//    Vector current_Velocity;
//    pfnEstimateAbsVelocity(current_Entity->GetIClientEntity(), current_Velocity);
//    int current_Flags = *reinterpret_cast<int*>( (size_t)current_Entity + 0x2E4 );
//
//    if( !( current_Flags & FL_ONGROUND ) )
//    {
//        current_Velocity.z -= ( ent_gravity * g_pCvar->FindVar( "sv_gravity" )->GetFloat( ) * current_Time * 0.5f );
//    }
//
//    float current_VelocityModifier = *reinterpret_cast<float*>( (size_t)current_Entity + 0x13A8 ); //m_flVelocityModifier
//    current_Velocity *= ( current_VelocityModifier * current_Time );
//
//    return current_Velocity;
//}
//
//void cAimbot::PredictTarget(C_BaseEntity* pEnemy, Vector& vPos)
//{
//    Vector VelocityEnemy = GetVelocity(pEnemy);
//    vPos += VelocityEnemy;
//}

//inline float GetInterpolationAmount( void )
//{
//    static INetChannelInfo* net_Info = g_pEngine->GetNetChannelInfo( );
//    float net_Latency = ( net_Info->GetAvgLatency( FLOW_OUTGOING ) + net_Info->GetAvgLatency( FLOW_INCOMING ) ) * 0.5f;
//
//    return ( (g_pCvar->FindVar( "cl_interp_ratio" )->GetFloat() / g_pCvar->FindVar( "cl_updaterate" )->GetFloat()));
//}
//
//EstimateAbsVelocityFn pfnEstimateAbsVelocity;
//Vector GetVelocity( C_BaseEntity* current_Entity )
//{
//    float current_LaggedMovementValue = *reinterpret_cast<float*>( (size_t)current_Entity + 0x119C ); //m_flLaggedMovementValue
//    float current_Time = ( ( g_pGlobals->interval_per_tick * GetInterpolationAmount() ) * current_LaggedMovementValue );
//
//    float ent_gravity;
//
//    if (current_Entity->GetGravity() > 0.01)
//        ent_gravity = current_Entity->GetGravity();
//    else
//        ent_gravity = 1.0;
//
//    Vector current_Velocity;
//    pfnEstimateAbsVelocity(current_Entity->GetIClientEntity(), current_Velocity);
//    int current_Flags = *reinterpret_cast<int*>( (size_t)current_Entity + 0x2E4 );
//
//    if( !( current_Flags & FL_ONGROUND ) )
//    {
//        current_Velocity.z -= ( ent_gravity * g_pCvar->FindVar( "sv_gravity" )->GetFloat( ) * current_Time * 0.5f );
//    }
//
//    float current_VelocityModifier = *reinterpret_cast<float*>( (size_t)current_Entity + 0x13A8 ); //m_flVelocityModifier
//    current_Velocity *= ( current_VelocityModifier * current_Time );
//
//    return current_Velocity;
//}
//
//void cAimbot::PredictTarget(int index)
//{
// C_BaseEntity* pEnt = g_pEntList->GetClientEntity(index)->GetBaseEntity();
// Vector velocity = GetVelocity(pEnt);
// m_vPosition += velocity;
//}

//bool CGameTrace::DidHitWorld()const
//{
//    return m_pEnt == g_pEntList->GetClientEntity(0);
//}

//bool cAimbot::GetVisible(const Vector &vecStart, const Vector &vecEnd, unsigned int nMask, ITraceFilter* pTraceFilter, C_BaseEntity* pBaseEntity)//odd
//{
//    trace_t Trace;
//    Ray_t ray;
//    ray.Init(vecStart,vecEnd);
//    g_pEnginetrace->TraceRay(ray,nMask,pTraceFilter,&Trace);
//
//    if(Trace.fraction == 1.0f)
//        return true;
//
//    return false;
//}

bool cAimbot::GetVisible(Vector &vAbsStart, CBaseEntity* pLocal, CBaseEntity* pBaseEntity)
{
        trace_t Trace;
        Ray_t Ray;

        DWORD dwTemp[5];
        this->TraceFilter( dwTemp, pBaseEntity, pLocal, 0 );

        Ray.Init(vAbsStart, m_vPosition);
        g_pEnginetrace->TraceRay( Ray, 0x200400B, (CTraceFilterSkipTwoEntities*)&dwTemp, &Trace );

        if(Trace.fraction >= 0.97f)
                return true;

        if(Trace.fraction <= 0.70f)
                return false;

        if(Trace.startsolid || Trace.allsolid)
                return false;

        return false;
}


//void __fastcall cAimbot::VectorTransform(const Vector& in1, const matrix3x4_t &in2, Vector &out)
//{
//    out.x = math.fastDotProduct(&in1.x, in2[0]) + in2[0][3];
//    out.y = math.fastDotProduct(&in1.x, in2[1]) + in2[1][3];
//    out.z = math.fastDotProduct(&in1.x, in2[2]) + in2[2][3];
//}

//    if(Trace.fraction == 1.0f)
//        return true;
//
//    return false;
//}

//enum {
//    FAR_LEFT_BOTTOM,
//    FAR_LEFT_TOP,
//    FAR_RIGHT_TOP,
//    FAR_RIGHT_BOTTOM,
//    NEAR_RIGHT_BOTTOM,
//    NEAR_LEFT_BOTTOM,
//    NEAR_LEFT_TOP,
//    NEAR_RIGHT_TOP,
//    BOX_CORNERS
//};
//
//#define SET_BOUNDS_VALUE( _ARRAY, _INDEX, _X, _Y, _Z ) _ARRAY[_INDEX].x = _X; _ARRAY[_INDEX].y = _Y; _ARRAY[_INDEX].z = _Z; ++_INDEX;
//
//void cAimbot::GetBoxPoints( const Vector vMins, const Vector vMaxs, Vector *pOut, bool bShouldIncludeCenter )
//{
//    /*
//      2-----3
//     /|    / |
//    / |   /  |
//    6-----5  |
//    |  1--|--4
//    | /   | /
//    |/    |/
//    7-----8
//    */
//
//    int cornerIndex = 0;
//
//    if ( bShouldIncludeCenter )
//    {
//        pOut[0] = ( ( vMins + vMaxs ) * .5f );
//        ++cornerIndex;
//    }
//
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMins.x, vMins.y, vMins.z );//Min
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMins.x, vMaxs.y, vMins.z );
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMaxs.x, vMaxs.y, vMins.z );
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMaxs.x, vMins.y, vMins.z );
//
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMaxs.x, vMaxs.y, vMaxs.z );//Max
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMins.x, vMaxs.y, vMaxs.z );
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMins.x, vMins.y, vMaxs.z );
//    SET_BOUNDS_VALUE( pOut, cornerIndex, vMaxs.x, vMins.y, vMaxs.z );
//}
//
bool cAimbot::GetBonePosition ( int iBone, Vector& vecOrigin, QAngle qAngles, int index )
{
        matrix3x4_t pmatrix[MAXSTUDIOBONES];

        IClientEntity* ClientEntity = g_pEntList->GetClientEntity( index );

        if ( ClientEntity == NULL )
                return false;

        if ( ClientEntity->IsDormant() )
                return false;

        matrix3x4_t Matrix[MAXSTUDIOBONES];
        if( ClientEntity->GetBaseEntity()->SetupBones( Matrix, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0))
        {
                studiohdr_t *pStudioHeader = g_pModelinfo->GetStudiomodel( ClientEntity->GetBaseEntity()->GetModel() );
                if( pStudioHeader )
                {
                        if (iBone < 0 || iBone >= pStudioHeader->numbones)
                                return false;

                        QAngle qAngles;
                        MatrixAngles(Matrix[iBone],qAngles,vecOrigin);
                }
        }
        return true;
}
////
//void cAimbot::GetAimPoints( C_BaseEntity *pEntity, Vector *pOut, bool ShouldPredict )
//{
//    matrix3x4_t Matrix[MAXSTUDIOBONES];
//    float flSimulationTime = *reinterpret_cast<float*>( reinterpret_cast<DWORD>( pEntity ) + 0x68 );
//    if( !pEntity->SetupBones( Matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, flSimulationTime ) )
//    {
//        return;
//    }
//
//    studiohdr_t *pStudioHeader = g_pModelinfo->GetStudiomodel( pEntity->GetModel() );
//    if( !pStudioHeader )
//    {
//        return;
//    }
//
//    mstudiohitboxset_t *pHitBoxSet = pStudioHeader->pHitboxSet( *reinterpret_cast<int*>( reinterpret_cast<DWORD>( pEntity ) + 0x4b4 ) );
//    mstudiobbox_t *pBox = pHitBoxSet->pHitbox( 12 );
//
//    Vector vPoints[9];
//    GetBoxPoints( pBox->bbmin, pBox->bbmax, vPoints, true );
//
//    /*for( int nIndex = 0; nIndex <= 8; ++nIndex )*/
//
//    //Vector highPosition = ( ( AimPoints[pEntity->index][4] + AimPoints[pEntity->index][5] ) * .5f );
//   
//    //Vector upDirection = ( highPosition - AimPoints[pEntity->index][CENTER] );
//    //float maxHeight = upDirection.NormalizeInPlace() * ( 1 + (1/3) );
//    for( int cornerIndex = 0; cornerIndex <= 8; ++cornerIndex )//.....fail
//    {
//        if( cornerIndex != 0 )
//        {
//            vPoints[cornerIndex] = ( ( vPoints[cornerIndex] + vPoints[0] ) * .5f );
//        }
//
//        //PredictTarget(pEntity, vPoints[cornerIndex]);
//
//        VectorTransform( vPoints[cornerIndex], Matrix[pBox->bone], pOut[cornerIndex] );
//    }
//}
//
//bool cAimbot::GetHitboxPosition(int nIndex)
//{
//    matrix3x4_t pMatrix[MAXSTUDIOBONES];
//    Vector vMin, vMax;
//    mstudiohitboxset_t* pHitboxSet;
//    mstudiobbox_t* pBox;
//    const model_t* pModel = pEnemyClient->GetModel();
//    studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
//    float flSimulationTime = *reinterpret_cast<float*>( reinterpret_cast<DWORD>( pEnemyClient ) + 0x68 );
//    if(pEnemyClient->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, flSimulationTime))
//    {
//        pHitboxSet = pStudioHdr->pHitboxSet(*reinterpret_cast<int*>( reinterpret_cast<DWORD>( pEnemyClient ) + 0x4b4 ) );
//        pBox = pHitboxSet->pHitbox(nIndex);
//        VectorTransform(pBox->bbmin, pMatrix[pBox->bone], vMin);
//        VectorTransform(pBox->bbmax, pMatrix[pBox->bone], vMax);
//        m_vPosition = (vMin + vMax) * 0.5f;
//
//        if ( this->AA[pEnemyClient->GetBaseEntity()->index] == true )
//        {
//            m_vPosition.z += 3.4;
//            //m_vPosition.y -= 0.2;
//        }
//        //PredictTarget(nIndex);
//        return true;
//    }
//    return false;
//}

//enum Bones_t
//{
//    BONE_PELVIS,
//    BONE_LEFT_THIGH,
//    BONE_LEFT_CALF,
//    BONE_LEFT_FOOT,
//    BONE_LEFT_TOE,
//    BONE_RIGHT_THIGH,
//    BONE_RIGHT_CALF,
//    BONE_RIGHT_FOOT,
//    BONE_RIGHT_TOE,
//    BONE_SPINE,
//    BONE_SPINE1,
//    BONE_SPINE3,
//    BONE_SPINE4,
//    BONE_NECK,
//    BONE_HEAD,
//    BONE_LEFT_CLAVICLE,
//    BONE_LEFT_UPPER_ARM,
//    BONE_LEFT_FOREARM,
//    BONE_LEFT_HAND,
//    BONE_LEFT_FINGER2,
//    BONE_LEFT_FINGER21,
//    BONE_LEFT_FINGER22,
//    BONE_LEFT_FINGER1,
//    BONE_LEFT_FINGER11,
//    BONE_LEFT_FINGER12,
//    BONE_LEFT_FINGER0,
//    BONE_LEFT_FINGER01,
//    BONE_LEFT_FINGER02,
//    BONE_RIGHT_CLAVICLE,
//    BONE_RIGHT_UPPER_ARM,
//    BONE_RIGHT_FOREARM,
//    BONE_RIGHT_HAND,
//    BONE_RIGHT_FINGER2,
//    BONE_RIGHT_FINGER21,
//    BONE_RIGHT_FINGER22,
//    BONE_RIGHT_FINGER1,
//    BONE_RIGHT_FINGER11,
//    BONE_RIGHT_FINGER12,
//    BONE_RIGHT_FINGER0,
//    BONE_RIGHT_FINGER01,
//    BONE_RIGHT_FINGER02,
//    BONE_RIGHT_WRIST,
//    BONE_LEFT_WRIST,
//    BONE_LEFT_ULNA,
//    BONE_RIGHT_ULNA,
//    BONE_WEAPON_BONE,
//    BONE_WEAPON_BONE_RIGHT_HAND,
//    BONE_WEAPON_BONE_LEFT_HAND,
//    BONE_WEAPON_BONE_CLIP,
//    BONE_FORWARD
//};

//Vector cAimbot::GetBoneVector( int iBoneNum  )
//{
//    QAngle qAngle;
//    Vector vBoneVec;
//    matrix3x4_t pMatrix[MAXSTUDIOBONES];
//
//    IClientEntity* pEnemyClient = g_pEntList->GetClientEntity(iBoneNum);
//    if( pEnemyClient->SetupBones( pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, GetTickCount() ))
//        MatrixAngles( pMatrix[ iBoneNum ], qAngle, vBoneVec );
//
//    return vBoneVec;
//
//}

bool cAimbot::GetHitboxPosition(int nIndex)
{
        matrix3x4_t pMatrix[MAXSTUDIOBONES];
        Vector vMin, vMax, Bone;
        QAngle qAngle;
        mstudiohitboxset_t* pHitboxSet;
        mstudiobbox_t* pBox;
        IClientEntity* pEnemyClient = g_pEntList->GetClientEntity(nIndex);
        const model_t* pModel = pEnemyClient->GetModel();
        studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
        if(pEnemyClient->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0 ))
        {
                MatrixAngles( pMatrix[ nIndex ], qAngle, Bone );
                pHitboxSet = pStudioHdr->pHitboxSet(0);
                pBox = pStudioHdr->pHitbox(12, 0);
                VectorTransform(pBox->bbmin, pMatrix[pBox->bone], vMin);
                VectorTransform(pBox->bbmax, pMatrix[pBox->bone], vMax);
                m_vPosition = (vMin + vMax) * 0.5f;
       
                if ( this->AA[pEnemyClient->GetBaseEntity()->index] == true )
                {
                        m_vPosition.z += 4.5;//look boy det :o?yash ser mit aaa fint ud?
                }
                return true;
        }
        return false;
}

//bool __fastcall cAimbot::Triggerbot(CUserCmd* pCmd, C_BaseEntity* pMe)
//{
//CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pMe);
//    C_BasePlayer* pPlayer = (C_BasePlayer*)pMe;
//
//    if(pWeapon == NULL) return false;
//
//    QAngle qRecoil = gNospread.GetRecoil(pMe);
//    QAngle qSpreadAngles = pCmd->viewangles + qRecoil;
//
//    Vector vecForward;
//    gNospread.GetSpreadVector(pCmd->random_seed, qSpreadAngles, vecForward);
//
//    Vector vecStart = GetPredictedEyePosition(pMe);
//    Vector vecEnd = vecStart + vecForward * 8192;
//
//    //PredictTarget(pMe, vecEnd);
//
//    Ray_t ray;
//    ray.Init(vecStart, vecEnd);
//
//    DWORD dwTemp[5];
//    this->TraceFilter( dwTemp,0, pMe, 0 );
//
//    trace_t hullTrace;
//    g_pEnginetrace->TraceRay(ray, MASK_SHOT, (CTraceFilterSkipTwoEntities*)&dwTemp, &hullTrace);
//
//    if(hullTrace.m_pEnt
//        && !hullTrace.m_pEnt->IsDormant()
//        && hullTrace.m_pEnt->IsPlayer()
//        && hullTrace.m_pEnt->IsAlive()
//        && hullTrace.m_pEnt->GetTeamNumber() != pMe->GetTeamNumber())
//    {
//        C_BaseEntity* m_pAimEnt = hullTrace.m_pEnt;
//
//        trace_t playerTrace[2];
//
//        ray.Init(vecStart, vecEnd);
//        g_pEnginetrace->TraceRay(ray, MASK_SHOT, (CTraceFilterSkipTwoEntities*)&dwTemp, &playerTrace[0]);
//        g_pEnginetrace->ClipRayToEntity(ray, MASK_SHOT|CONTENTS_HITBOX, m_pAimEnt, &playerTrace[1]);
//
//        if(playerTrace[1].fraction < playerTrace[0].fraction)
//            playerTrace[0] = playerTrace[1];
//
//        if(playerTrace[0].m_pEnt != m_pAimEnt)
//            return false;
//
//        m_pAimEnt = playerTrace[0].m_pEnt;
//        float m_flFraction = playerTrace[0].fraction;
//
//        int iHitboxToHit = playerTrace[0].hitbox;
//
//        matrix3x4_t boneMatrix[MAXSTUDIOBONES];
//        float flSimulationTime = *reinterpret_cast<float*>( reinterpret_cast<DWORD>( pMe ) + 0x68 );
//        if(!m_pAimEnt->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, flSimulationTime))
//            return false;
//
//        const model_t* pModel = m_pAimEnt->GetModel();
//        if(!pModel) return false;
//
//        studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
//        if(!pStudioHdr) return false;
//
//        mstudiohitboxset_t* pHitboxSet = pStudioHdr->pHitboxSet(*reinterpret_cast<int*>( reinterpret_cast<DWORD>( pMe ) + 0x4B4 ));
//        mstudiobbox_t* pBox = pHitboxSet->pHitbox(iHitboxToHit);
//
//        Vector vMin = pBox->bbmin, vMax = pBox->bbmax;
//       
//        int m_iFov = *(int*)((DWORD)pPlayer + 0xF48);
//        if(gNospread.GetWeaponID(pWeapon) == 17 && m_iFov != 90)
//        {
//            vMin *= 0.90f; vMax *= 0.90f;
//        }
//        else
//        {
//            vMin *= 0.70f; vMax *= 0.70f;
//        }
//
//        trace_t boxTrace;
//        if(IntersectRayWithOBB(ray, boneMatrix[pBox->bone], vMin, vMax, 0.f, &boxTrace))
//        {
//            Vector vPos;
//            QAngle angles;
//            MatrixAngles( boneMatrix[pBox->bone], angles, vPos);
//            g_pDebugOverlay->AddBoxOverlay(vPos, pBox->bbmin, pBox->bbmax, angles, 25, 200, 25, 50.f, 0.05f);
//            return true;
//        }
//    }
//    return false;
//}

//bool __fastcall cAimbot::TriggerBot(CUserCmd* pCmd, C_BaseEntity* pMe)
//{
//    //trace_t tr;
//    //Ray_t ray;
//
//    //C_BaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pMe);
//
//    //if(!pWeapon)
//    //    return false;
//
//    //QAngle qRecoil = gNospread.GetRecoil(pMe);
//    //QAngle qSpreadAngles = pCmd->viewangles + qRecoil;
//
//    //Vector vecForward;
//    //
//    //gNospread.LegitNS(pCmd->random_seed, vecForward);
//
//    //gNospread.GetSpreadVector(pCmd->random_seed, qSpreadAngles, vecForward);
//
//    //Vector vecStart = GetPredictedEyePosition(pMe);
//    //Vector vecEnd = vecStart + (vecForward * 8192.0f);
//
//    //QAngle qFinal;
//    //VectorAngles(vecEnd, qFinal);
//
//    //DWORD dwTemp[5];
//    //DWORD dwCall = this->dwTraceFilter;
//    //_asm
//    //{
//    //    PUSH COLLISION_GROUP_NONE
//    //        PUSH NULL
//    //        PUSH pMe
//    //        LEA ECX, dwTemp
//    //        CALL dwCall
//    //}
//
//    //ray.Init(vecStart, vecEnd);
//    //g_pEnginetrace->TraceRay(ray, MASK_SHOT, (ITraceFilter*)&dwTemp, &tr);
//
//    //if( tr.m_pEnt->GetIClientEntity() == NULL )
//    //    return false;
//    //C_BasePlayer* pPlayer = dynamic_cast<C_BasePlayer*>(tr.m_pEnt->GetIClientEntity());
//    //IClientEntity* pRemoteEnt = (IClientEntity*)g_pEntList->GetClientEntity( tr.m_pEnt->index );
//    //CBaseEntity* pRemoteBEnt = (CBaseEntity*)pRemoteEnt->GetBaseEntity();
//    //if( pRemoteBEnt->GetTeamNumber() == pMe->GetTeamNumber() )
//    //    return false;
//    //if( pPlayer == NULL )
//    //    return false;
//    //if( !pPlayer->IsAlive() || !pPlayer->GetTeamNumber() )
//    //    return false;
//
//    //matrix3x4_t pMatrix[MAXSTUDIOBONES];
//    //Vector vecPosition, vMin, vMax;
//    //QAngle angles;
//    //mstudiohitboxset_t* pHitboxSet;
//    //mstudiobbox_t* pBox;
//    //const model_t* pModel = pRemoteBEnt->GetModel();
//    //studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
//    //float flSimulationTime = *reinterpret_cast<float*>( reinterpret_cast<DWORD>( pRemoteBEnt ) + 0x68 );
//    //if(pRemoteBEnt->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, flSimulationTime))
//    //{
//    //    pHitboxSet = pStudioHdr->pHitboxSet(*reinterpret_cast<int*>( reinterpret_cast<DWORD>( pRemoteBEnt ) + 0x4B4 ));
//    //    pBox = pHitboxSet->pHitbox(tr.hitbox);
//    //    MatrixAngles(pMatrix[pBox->bone], angles, vecPosition);
//    //    VectorTransform(pBox->bbmin, pMatrix[pBox->bone], vMin);
//    //    VectorTransform(pBox->bbmax, pMatrix[pBox->bone], vMax);
//    //    if(IntersectRayWithOBB(ray, pMatrix[pBox->bone], vMin, vMax, 0.f, &tr))
//    //    {
//    //        //if(AutoWall(vecStart, (vMin + vMax) * 0.5, pRemoteBEnt))
//    //        {
//    //            g_pDebugOverlay->AddBoxOverlay(vecPosition, pBox->bbmin, pBox->bbmax, angles, 36, 200, 45, 125, 0.05f);
//    //            return true;
//    //        }
//    //    }
//    //}
//
//    //return false;
//   
//    CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pMe);
//    C_BasePlayer* pPlayer = (C_BasePlayer*)pMe;
//
//    if(pWeapon == NULL) return false;
//
//    QAngle qRecoil = gNospread.GetRecoil(pMe);
//    QAngle qSpreadAngles = pCmd->viewangles + qRecoil;
//
//    Vector vecForward;
//   
//    gNospread.LegitNS(pCmd->random_seed, vecForward);
//    gNospread.GetSpreadVector(pCmd->random_seed, qSpreadAngles, vecForward);
//
//    Vector vecStart = GetPredictedEyePosition(pMe);
//    Vector vecEnd = vecStart + vecForward * 8192;
//
//    PredictTarget(pMe, vecEnd);
//
//    Ray_t ray;
//    ray.Init(vecStart, vecEnd);
//
//    DWORD dwTemp[5];
//    DWORD dwCall = this->dwTraceFilter;
//    _asm
//    {
//        PUSH COLLISION_GROUP_NONE
//            PUSH NULL
//            PUSH pMe
//            LEA ECX, dwTemp
//            CALL dwCall
//    }
//
//    trace_t hullTrace;
//    g_pEnginetrace->TraceRay(ray, 0x4600400B, (ITraceFilter*)&dwTemp, &hullTrace);
//
//    if(hullTrace.m_pEnt
//        && !hullTrace.m_pEnt->IsDormant()
//        && hullTrace.m_pEnt->IsPlayer()
//        && hullTrace.m_pEnt->IsAlive()
//        && hullTrace.m_pEnt->GetTeamNumber() != pMe->GetTeamNumber())
//    {
//        C_BaseEntity* m_pAimEnt = hullTrace.m_pEnt;
//
//        trace_t playerTrace[2];
//
//        ray.Init(vecStart, vecEnd);
//        g_pEnginetrace->TraceRay(ray, 0x4600400B, (ITraceFilter*)&dwTemp, &playerTrace[0]);
//        g_pEnginetrace->ClipRayToEntity(ray, 0x4600400B|CONTENTS_HITBOX, m_pAimEnt, &playerTrace[1]);
//
//        if(playerTrace[1].fraction < playerTrace[0].fraction)
//            playerTrace[0] = playerTrace[1];
//
//        if(playerTrace[0].m_pEnt != m_pAimEnt)
//            return false;
//
//        m_pAimEnt = playerTrace[0].m_pEnt;
//        float m_flFraction = playerTrace[0].fraction;
//
//        int iHitboxToHit = playerTrace[0].hitbox;
//
//        matrix3x4_t boneMatrix[MAXSTUDIOBONES];
//        float flSimulationTime = *reinterpret_cast<float*>( reinterpret_cast<DWORD>( pMe ) + 0x68 );
//        if(!m_pAimEnt->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, flSimulationTime))
//            return false;
//
//        const model_t* pModel = m_pAimEnt->GetModel();
//        if(!pModel) return false;
//
//        studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
//        if(!pStudioHdr) return false;
//
//        mstudiohitboxset_t* pHitboxSet = pStudioHdr->pHitboxSet(*reinterpret_cast<int*>( reinterpret_cast<DWORD>( pMe ) + 0x4B4 ));
//        mstudiobbox_t* pBox = pHitboxSet->pHitbox(iHitboxToHit);
//
//        Vector vMin = pBox->bbmin, vMax = pBox->bbmax;
//       
//        int m_iFov = *(int*)((DWORD)pPlayer + 0xF48);
//        if(gNospread.GetWeaponID(pWeapon) == 17 && m_iFov != 90)
//        {
//            vMin *= 0.90f; vMax *= 0.90f;
//        }
//        else
//        {
//            vMin *= 0.70f; vMax *= 0.70f;
//        }
//
//        trace_t boxTrace;
//        if(IntersectRayWithOBB(ray, boneMatrix[pBox->bone], pBox->bbmin, pBox->bbmax, 0.f, &boxTrace))
//        {
//            Vector vPos;
//            QAngle angles;
//            MatrixAngles( boneMatrix[pBox->bone], angles, vPos);
//            g_pDebugOverlay->AddBoxOverlay(vPos, pBox->bbmin, pBox->bbmax, angles, 25, 200, 25, 50.f, 0.05f);
//            return true;
//        }
//    }
//    return false;
//}


//bool __fastcall cAimbot::Triggerbot(CUserCmd* pCmd, C_BaseEntity* pMe)
//{
//    trace_t tr;
//    Ray_t ray;
//
//    C_BaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pMe);
//
//    if(!pWeapon)
//        return false;
//
//    QAngle qRecoil = gNospread.GetRecoil(pMe);
//    QAngle qSpreadAngles = pCmd->viewangles + qRecoil;
//
//    Vector vecForward;
//   
//    gNospread.LegitNS(pCmd->random_seed, vecForward);
//    gNospread.GetSpreadVector(pCmd->random_seed, qSpreadAngles, vecForward);
//
//    Vector vecStart = GetPredictedEyePosition(pMe);
//    Vector vecEnd = vecStart + (vecForward * 8192.0f);
//
//    QAngle qFinal;
//    VectorAngles(vecEnd, qFinal);
//
//    DWORD dwTemp[5];
//    DWORD dwCall = this->dwTraceFilter;
//    _asm
//    {
//        PUSH COLLISION_GROUP_NONE
//            PUSH NULL
//            PUSH pMe
//            LEA ECX, dwTemp
//            CALL dwCall
//    }
//
//    ray.Init(vecStart, vecEnd);
//    g_pEnginetrace->TraceRay(ray, MASK_NPCWORLDSTATIC|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_DEBRIS|CONTENTS_HITBOX, (ITraceFilter*)&dwTemp, &tr);
//
//    if( tr.m_pEnt->GetIClientEntity() == NULL )
//        return false;
//    C_BasePlayer* pPlayer = dynamic_cast<C_BasePlayer*>(tr.m_pEnt->GetIClientEntity());
//    IClientEntity* pRemoteEnt = (IClientEntity*)g_pEntList->GetClientEntity( tr.m_pEnt->index );
//    CBaseEntity* pRemoteBEnt = (CBaseEntity*)pRemoteEnt->GetBaseEntity();
//    if( pRemoteBEnt->GetTeamNumber() == pMe->GetTeamNumber() )
//        return false;
//    if( pPlayer == NULL )
//        return false;
//    if( !pPlayer->IsAlive() || !pPlayer->GetTeamNumber() )
//        return false;
//
//    matrix3x4_t pMatrix[MAXSTUDIOBONES];
//    Vector vecPosition, vMin, vMax;
//    QAngle angles;
//    mstudiohitboxset_t* pHitboxSet;
//    mstudiobbox_t* pBox;
//    const model_t* pModel = pRemoteBEnt->GetModel();
//    studiohdr_t* pStudioHdr = g_pModelinfo->GetStudiomodel(pModel);
//    float flSimulationTime = *reinterpret_cast<float*>( reinterpret_cast<DWORD>( pRemoteBEnt ) + 0x68 );
//    if(pRemoteBEnt->SetupBones(pMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, flSimulationTime))
//    {
//        pHitboxSet = pStudioHdr->pHitboxSet(*reinterpret_cast<int*>( reinterpret_cast<DWORD>( pRemoteBEnt ) + 0x4B4 ));
//        pBox = pHitboxSet->pHitbox(tr.hitbox);
//        MatrixAngles(pMatrix[pBox->bone], angles, vecPosition);
//        VectorTransform(pBox->bbmin, pMatrix[pBox->bone], vMin);
//        VectorTransform(pBox->bbmax, pMatrix[pBox->bone], vMax);
//        if(IsRayIntersectingOBB(ray, vecPosition, qFinal, pBox->bbmin, pBox->bbmax)/* || AutoWall(vecStart, (vMin + vMax) * 0.5, pRemoteBEnt)*/)
//        {
//            Vector vMin = pBox->bbmin, vMax = pBox->bbmax;
//
//            int m_iFov = *(int*)((DWORD)pPlayer + 0xF48);
//            if(gNospread.GetWeaponID(pWeapon) == 17 && m_iFov != 90)
//            {
//                vMin *= 0.90f; vMax *= 0.90f;
//            }
//            else
//            {
//                vMin *= 0.70f; vMax *= 0.70f;
//            }
//
//            trace_t boxTrace;
//            if(IntersectRayWithOBB(ray, pMatrix[pBox->bone], vMin, vMax, 0.f, &boxTrace))
//            {
//                Vector vPos;
//                QAngle angles;
//                MatrixAngles( pMatrix[pBox->bone], angles, vPos);
//                g_pDebugOverlay->AddBoxOverlay(vPos, pBox->bbmin, pBox->bbmax, angles, 25, 200, 25, 50.f, 0.05f);
//                return true;
//            }
//        }
//    }
//        return false;
//    }


//bool __fastcall cAimbot::TriggerbotSpread(CUserCmd* pCmd, C_BaseEntity* pMe)
//{       
//    player_info_t pinfo;
//    trace_t tr;
//    Ray_t ray;
//    Vector vStart,vEnd,vForward,Origin;
//    QAngle vCurAngles;
//    vStart = gUtils.GetEyePosition(gUtils.GetLocalEntity());
//    g_pEngine->GetViewAngles(vCurAngles);
//    gNospread.GetSpreadVector(pCmd->random_seed, vCurAngles, vForward);
//    gNospread.LegitNS(pCmd->random_seed, vForward);
//    vEnd = vStart + (vForward * 8192);
//    ray.Init(vStart, vEnd);
//    int hitboxy = CONTENTS_HITBOX == 12;
//    g_pEnginetrace->TraceRay ( ray, MASK_NPCWORLDSTATIC|CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX,NULL, &tr );
//    if(gCvar.trigger_box){
//    if(tr.hitbox < gCvar.trigger_box){
//        return false;
//    }
//    if(tr.hitbox == gCvar.trigger_box){
//        return true;
//    }
//    }
//    if( tr.m_pEnt->GetIClientEntity() == NULL )
//        return false;
//    C_BasePlayer* pPlayer  =  dynamic_cast<C_BasePlayer*>(tr.m_pEnt->GetIClientEntity());
//    IClientEntity* pRemoteEnt = (IClientEntity*)g_pEntList->GetClientEntity( tr.m_pEnt->index/*index*/  );
//   
//    CBaseEntity* pRemoteBEnt = (CBaseEntity*)pRemoteEnt->GetBaseEntity();
//    //we done same team fix xd
//   
//    //if( gUtils.GetBaseEntityTeamNum(pRemoteBEnt) == gUtils.GetBaseEntityTeamNum(gUtils.GetLocalEntity() ))
//    //return false;
//    if( pRemoteBEnt->GetTeamNumber() == pMe->GetTeamNumber() )
//        return false;
//
//    if( pPlayer == NULL )
//    return false;
//       
//    if( !pPlayer->IsAlive() || !pPlayer->GetTeamNumber() )
//        return false;
//   
//   
//    return true;
//   
//}

bool __fastcall cAimbot::TriggerBot(CUserCmd* pCmd, C_BaseEntity* pMe)
{
        trace_t tr;
        Ray_t ray;

        C_BaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pMe);

        if(!pWeapon)
                return false;

        QAngle qRecoil = gNospread.GetRecoil(pMe);
        QAngle qSpreadAngles = pCmd->viewangles + qRecoil;

        Vector vecForward;
   
        gNospread.LegitNS(pCmd->random_seed, vecForward);
        gNospread.GetSpreadVector(pCmd->random_seed, qSpreadAngles, vecForward);

        Vector vecStart = GetPredictedEyePosition(pMe);

        Vector vecEnd = vecStart + vecForward * 8192.0f;

        ray.Init(vecStart, vecEnd);
        g_pEnginetrace->TraceRay(ray, MASK_SHOT, 0, &tr);

        if( tr.m_pEnt->GetIClientEntity() == NULL )
                return false;
        C_BasePlayer* pPlayer = dynamic_cast<C_BasePlayer*>(tr.m_pEnt->GetIClientEntity());
        IClientEntity* pRemoteEnt = (IClientEntity*)g_pEntList->GetClientEntity( tr.m_pEnt->index );
        CBaseEntity* pRemoteBEnt = (CBaseEntity*)pRemoteEnt->GetBaseEntity();
        if( pRemoteBEnt->GetTeamNumber() == pMe->GetTeamNumber() )
                return false;
        if( pPlayer == NULL )
                return false;
        if( !pPlayer->IsAlive() || !pPlayer->GetTeamNumber() )
                return false;

        return true;
}

void cAimbot::MakeVector(QAngle angle, QAngle& vector)
{
        float pitch;
        float yaw;
        float tmp;           
        pitch    = (float)(angle[0] * M_PI/180);
        yaw        = (float)(angle[1] * M_PI/180);
        tmp        = (float) cos(pitch);
        vector[0] = (float) (-tmp * -cos(yaw));
        vector[1] = (float) (sin(yaw)*tmp);
        vector[2] = (float) -sin(pitch);
}

typedef void ( __thiscall* GetEyePosition_t )( void* thisptr, Vector& velocity );
////
//Vector& cAimbot::GetPredictedEyePosition(C_BaseEntity* pEntity)
//{
//    //Vector m_VecOrigin = *(Vector*)((DWORD)pEntity + 0x2CC);
//    //Vector m_vecViewOffset = *(Vector*)((DWORD)pEntity + 0x0E4);
//    //Vector vEyePosition = (m_VecOrigin + m_vecViewOffset);
//    //return vEyePosition;
//
//    assert( player );
//
//    Vector eyepos;
//    ( (GetEyePosition_t)( *(int*)( *(int*)pEntity + 0x214 ) ) )( pEntity, eyepos );
//
//    return eyepos;
//}

Vector &cAimbot::GetPredictedEyePosition(C_BaseEntity* pEntity)
{
        Vector m_VecOrigin = *(Vector*)((DWORD)pEntity + 0x2CC);
        Vector m_vecViewOffset = *(Vector*)((DWORD)pEntity + 0x0E4);
        Vector vEyePosition = (m_VecOrigin + m_vecViewOffset);
        return vEyePosition;
}

bool cAimbot::IsAlive(C_BaseEntity* pEntity)
{
        char szLifeState = *(char*)((DWORD)pEntity + 0x8f);

        return (szLifeState == LIFE_ALIVE);
}

int cAimbot::GetTeamNumber(C_BaseEntity* pEntity)
{
        int m_iTeamNum = *(int*)((DWORD)pEntity + 0x98);
        return m_iTeamNum;
}

int cAimbot::GetHealth(C_BaseEntity* pEntity)
{
        int m_iHealth = *(int*)((DWORD)pEntity + 0x90);
        return m_iHealth;
}

bool cAimbot::KnifeBot ( Vector& vecAbsOrigin, Vector& vecEndPos, CBaseEntity *pBaseEntity )
{
        float flDist = GetDistance(vecEndPos, vecAbsOrigin);
        if(flDist < 7.5)
                return true;

        return false;
}

float cAimbot::GetRadius( Vector MyEyePosition, C_BaseEntity* pEntity )
{
        QAngle View;
        g_pEngine->GetViewAngles( View );

        Vector Direction;
        AngleVectors( View, &Direction );

        Vector EnemyEyePosition = ( pEntity->GetAbsOrigin() + *reinterpret_cast<Vector*>( (size_t)pEntity + 0xe4 ) );

        Vector EyeDelta = ( EnemyEyePosition - MyEyePosition );
        EyeDelta.NormalizeInPlace();

        float Distance = RAD2DEG( acos( Direction.Dot( EyeDelta ) ) );

        if ( Distance > 0 )
        {
                return Distance;
        }
        else
        {
                return 0;
        }
}

void cAimbot::Normalize(Vector &vIn, Vector &vOut)
{
        float flLen = vIn.Length();
        if(flLen == 0){
                vOut.Init(0, 0, 1);
                return;
        }
        flLen = 1 / flLen;
        vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}
//
void pTraceLine( const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter *pFilter, trace_t *ptr )
{
        Ray_t ray;
        ray.Init( vecAbsStart, vecAbsEnd );

        g_pEnginetrace->TraceRay( ray, mask, pFilter, ptr );
}

//bool cAimbot::Rofl(const Vector &vAbsStart, C_BaseEntity* pMe, C_BaseEntity* pPlayer, Vector End)
//{
//    trace_t Trace;
//
//    Ray_t Ray;
//
//    float flPenetrationDistance = 0.0f, flPenetrationPower = 0.0f, flDamageModifier = 20.0f, flPenetrationPowerModifier = 0.0f;
//
//    int m_nBulletType;
//
//    int nPenetration;
//
//    int m_nDamage;
//
//    int iBulletType;
//
//    float m_flRangeModifier;
//
//    int nBulletType = nPenetration /*= g_cAccuracy.m_nPenetration*/ = 3, nCurrentDamage;
//
//    nCurrentDamage += ((-2 - (rand() % 2)) + (rand() % (4 + (rand() % 6))));
//
//    int nOriginalDamage = nCurrentDamage;
//
//    DWORD dwTemp[5];
//
//    this->TraceFilter( dwTemp, pPlayer, pMe, 0 );
//
//    if(GetVisible(vAbsStart, End, MASK_SHOT, (CTraceFilterSkipTwoEntities*)&dwTemp,pMe,pPlayer))
//        return true;
//
//    else
//    {
//        _asm
//        {
//            LEA ECX, flPenetrationDistance
//                PUSH ECX
//                LEA EDX, flPenetrationPower
//                PUSH EDX
//                PUSH iBulletType
//                CALL g_cAimbot.dwGetBulletTypeParameters
//        }
//
//        surfacedata_t* pSurfaceData;
//
//        int nMaterial;
//
//        Vector vStart = vAbsStart, vEnd, vTmp;
//
//        Vector vHypneuse;
//
//        VectorSubtract(m_vPosition, vAbsStart, vHypneuse);
//
//        float flHypneuseLength = VectorLength(vHypneuse), flTmpLength = 0.0f, flRangeModifier;
//
//        VectorDivide(vHypneuse, flHypneuseLength, vHypneuse);
//
//        while(nPenetration || nCurrentDamage > 0)
//        {
//            vEnd = (vStart + (vHypneuse * 8.0f));
//
//            Ray.Init(vStart, vEnd);
//            g_pEnginetrace->TraceRay(Ray, 0x4600400b, (CTraceFilterSkipTwoEntities*)&dwTemp, &Trace);
//
//            pSurfaceData = g_pPhysicAPI->GetSurfaceData(Trace.surface.surfaceProps);
//            nMaterial = pSurfaceData->game.material;
//
//            _asm
//            {
//                LEA EAX, flDamageModifier
//                    LEA ECX, flPenetrationPowerModifier
//                    MOV EDX, nMaterial
//                    CALL g_cAimbot.dwGetTextureInformation
//            }
//
//            if(Trace.fraction != 1.0f)
//            {
//                if(Trace.allsolid)
//
//                {
//                    return false;
//                }
//
//                VectorSubtract(Trace.endpos, vAbsStart,  vTmp);
//
//                flTmpLength = VectorLength(vTmp);
//
//                if(flTmpLength  >= flHypneuseLength)
//                {
//                    nCurrentDamage *= pow(flRangeModifier, (flHypneuseLength / 500));
//
//                    nCurrentDamage *= flDamageModifier;
//
//                    if(nCurrentDamage >= 10)
//
//                    {
//                        return true;
//                    }
//                }
//                nPenetration--;
//            }
//            vStart = vEnd;
//        }
//    }
//    return false;
//}

//bool cAimbot::AutoWall(Vector Start, C_BaseEntity* pBaseEnt, Vector End )
//{
//    trace_t Trace,Traces;
//    Ray_t Ray,Rays;
//    float flPenetrationDistance, flPenetrationPower, flDamageModifier,
//        flPenetrationPowerModifier,flDistance,flRangeModifier;
//    int iBulletType,iPenetration,iCurrentDamage;
//    C_BaseEntity*pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
//    Vector tmpVec;
//
//    CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocal);
//
//    if( !pWeapon )
//    {
//        return false;
//    }
//
//    int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));
//    C_BaseEntity *pMe = pLocal;
//
//    DWORD dwTemp[5];
//    this->TraceFilter( dwTemp, pBaseEnt, pLocal, 0 );
//
//    //_asm
//    //{
//    //    MOV EDX, pMe
//    //    MOV EAX, pBaseEnt;
//    //    PUSH 0;
//    //    PUSH EDX;
//    //    PUSH EAX;
//    //    LEA ECX, dwTemp;
//    //    CALL g_cAimbot.dwTraceFilter;
//    //}
//    if(GetVisible(Start, End, MASK_SHOT,(CTraceFilterSkipTwoEntities*)&dwTemp, pBaseEnt, pLocal))
//    {
//        return true;
//    }
//    else
//    {
//        if(!gCvar.aim_autowall)
//            return false;
//
//        if(!gNospread.GetWeaponInfo(pWeapon,iWeaponID,iBulletType,iPenetration,iCurrentDamage,flDistance,flRangeModifier))
//            return false;
//
//        _asm
//        {
//            LEA ECX, flPenetrationDistance
//                PUSH ECX
//                LEA EDX, flPenetrationPower
//                PUSH EDX
//                PUSH iBulletType
//                CALL g_cAimbot.dwGetBulletTypeParameters
//        }
//
//        surfacedata_t* pSurfaceData;
//        Vector vStart = Start, vEnd, vecDir;
//        VectorSubtract(End, Start, vecDir);
//        float flLength = VectorLength(vecDir),flTmpLength,flNewTempLength,flRange = flDistance,
//            flPowed,flSumDist,flCurrentDamage = (float)iCurrentDamage;
//        vecDir /= flLength;
//
//        vEnd = vStart + (vecDir * flRange);
//
//        while(iPenetration)
//        {
//            Ray.Init(vStart, vEnd);
//            g_pEnginetrace->TraceRay(Ray, MASK_SHOT, (CTraceFilterSkipTwoEntities*)&dwTemp, &Trace);   
//
//            pSurfaceData = g_pPhysicAPI->GetSurfaceData(Trace.surface.surfaceProps);
//
//            if( Trace.allsolid )
//                return false;
//
//            if(Trace.fraction != 1.0f)
//            {
//                flTmpLength = (flRange * Trace.fraction) + flSumDist;
//
//                if(flLength > flPenetrationDistance)
//                    return false;
//
//                int nMaterial = pSurfaceData->game.material;
//
//                char sMaterial = (char)nMaterial;
//
//                switch ( sMaterial )
//                {
//                case 'D':
//                case 'M':
//                    flPenetrationPowerModifier = 0.5;
//                    flDamageModifier = 0.3;
//                    break;
//                case 'C':
//                    flPenetrationPowerModifier = 0.4;
//                    flDamageModifier = 0.25;
//                    break;
//                case 'G':
//                    flPenetrationPowerModifier = 1.0;
//                    flDamageModifier = 1.0;
//                    break;
//                case 'V':
//                    flPenetrationPowerModifier = 0.5;
//                    flDamageModifier = 0.45;
//                    break;
//                case 'T':
//                    flPenetrationPowerModifier = 0.65;
//                    flDamageModifier = 0.3;
//                    break;
//                case 'P':
//                    flPenetrationPowerModifier = 0.4;
//                    flDamageModifier = 0.45;
//                    break;
//                case 'W':
//                    flPenetrationPowerModifier = 1.0;
//                    flDamageModifier = 0.6;
//                    break;
//                default:
//                    flPenetrationPowerModifier = 1.0;
//                    flDamageModifier = 0.5;
//                    break;
//                }
//                //switch ( materialType )
//                //               {
//                //               case 'D':
//                //               case 'M':
//                //                       flPenetration = 0.5;
//                //                       flDamage = 0.300000011920929;
//                //                       break;
//                //               case 'C':
//                //                       flPenetration = 0.4000000059604645;
//                //                       flDamage = 0.25;
//                //                       break;
//                //               case 'G':
//                //                       flPenetration = 1.0;
//                //                       flDamage = 0.9900000095367432;
//                //                       break;
//                //               case 'V':
//                //                       flPenetration = 0.5;
//                //                       flDamage = 0.449999988079071;
//                //                       break;
//                //               case 'T':
//                //                       flPenetration = 0.6499999761581421;
//                //                       flDamage = 0.300000011920929;
//                //                       break;
//                //               case 'P':
//                //                       flPenetration = 0.4000000059604645;
//                //                       flDamage = 0.449999988079071;
//                //                       break;
//                //               case 'W':
//                //                       flPenetration = 1.0;
//                //                       flDamage = 0.6000000238418579;
//                //                       break;
//                //               default:
//                //                       flPenetration = 1.0;
//                //                       flDamage = 0.5;
//                //                       break;
//                //               }
//
//                Ray.Init(End,Trace.endpos);
//
//                g_pEnginetrace->TraceRay(Ray, MASK_SHOT, (ITraceFilter*)&dwTemp, &Traces);   
//
//                if(g_pPhysicAPI->GetSurfaceData(Traces.surface.surfaceProps)->game.material == nMaterial && (nMaterial == 87 || nMaterial == 77))
//                    flPenetrationPowerModifier = flPenetrationPowerModifier + flPenetrationPowerModifier;
//
//                flNewTempLength = VectorLength(Traces.endpos - Trace.endpos);
//
//                if(flNewTempLength > (flPenetrationPowerModifier * flPenetrationPower))
//                    return false;
//
//                flPenetrationPower = flPenetrationPower - (flNewTempLength / flPenetrationPowerModifier);
//
//                vStart = Traces.endpos;
//
//                flCurrentDamage *= pow(flRangeModifier, (flTmpLength * 0.002f));
//                flPowed = flCurrentDamage;
//                flCurrentDamage *= flDamageModifier;
//
//                if((flDamageModifier * flPowed) > 0)
//                    return true;
//
//                flSumDist = flTmpLength + flNewTempLength;
//
//                flRange = (flRange - (flTmpLength + flNewTempLength)) * 0.5f;
//
//                --iPenetration;
//            }
//            return true;
//        }
//    }
//    return false;
//}

//bool __fastcall cAimbot::AutoWall( Vector vStart, Vector vEnd, C_BaseEntity *pBaseEntity )
//{
//    trace_t tr,tr2;
//    Vector vecSrc,vecEnd,vecDir,tmpVec;
//    float flRangeModifier,flPenetrationDistance,flCurrentDistance = 0.0f;
//    int iPenetration;
//    float iCurrentDamage = 0;
//    int iPenetrationPower = 0;
//    float flLength = 0.0f;
//    float flTempLength = 0.0f;
//    int iBulletType = 0;
//    float flTravelledDistance = 0.0f;
//
//    C_BaseEntity*pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
//
//    if( !pLocal )
//        return false;
//
//    CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocal);
//    int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));
//
//    DWORD dwTemp[5];
//    DWORD dwTraceFilter = this->dwTraceFilter;
//    DWORD dwGetBulletTypeParameters = this->dwGetBulletTypeParameters;
//    DWORD dwGetTextureInformation = this->dwGetTextureInformation;
//
//    __asm
//    {
//        MOV EDX,pLocal;
//        MOV EAX,pBaseEntity;
//
//        PUSH 0;
//        PUSH EDX;
//        PUSH EAX;
//        LEA ECX,dwTemp;
//        CALL dwTraceFilter;
//    }
//
//    //math.fastMemCopy(&vStart,&vecSrc,sizeof(Vector));
//    VectorCopy(vStart,vecSrc);
//    vecDir = vEnd - vStart;
//    flLength = sqrt ( vecDir.x * vecDir.x + vecDir.y * vecDir.y + vecDir.z * vecDir.z );
//    vecDir /= flLength;
//    VectorNormalize(vecDir);
//
//    if(!gNospread.GetWeaponInfo(pWeapon,iWeaponID,iBulletType,iPenetration,iCurrentDamage,flCurrentDistance,flRangeModifier))
//        return false;
//
//    float fPenetrationPower = 0.0f;
//
//    __asm
//    {
//        LEA ECX, flPenetrationDistance
//            PUSH ECX
//            LEA EDX, fPenetrationPower
//            PUSH EDX
//            PUSH iBulletType
//            CALL dwGetBulletTypeParameters
//    }
//
//    iPenetrationPower = (int)fPenetrationPower;
//
//    float flDamageModifier = 20.0f;
//
//    while(iPenetration || iCurrentDamage > 0.f)
//    {
//        vecEnd = vecSrc + vecDir * 10.0f;
//
//        if(flTravelledDistance > flCurrentDistance)
//            return false;
//
//        pTraceLine( vecSrc, vecEnd, 0x200400B, (ITraceFilter*)&dwTemp, &tr);
//
//        surfacedata_t *g_pSurfaceData = g_pPhysicAPI->GetSurfaceData( tr.surface.surfaceProps );
//        int iMaterial = g_pSurfaceData->game.material;
//
//        float flPenetrationPowerModifier = 0.0f;
//        __asm
//        {
//            LEA EAX, flDamageModifier
//                LEA ECX, flPenetrationPowerModifier
//                MOV EDX, iMaterial
//                CALL dwGetTextureInformation
//        }
//
//        iPenetrationPower *= flPenetrationPowerModifier;
//
//        flTravelledDistance += 10.f;
//
//        if(tr.fraction != 1.0)
//        {
//            if( tr.allsolid )
//                return false;
//
//            VectorSubtract ( tr.endpos, vStart, tmpVec );
//            flTempLength = sqrt(tmpVec.x * tmpVec.x + tmpVec.y * tmpVec.y+ tmpVec.z * tmpVec.z);
//
//            if ( flTempLength >= flLength )
//            {
//                if ( iCurrentDamage > 10.f )
//                    return true;
//            }
//
//            iCurrentDamage *= (powf (flRangeModifier, (tr.fraction * flTempLength) / 500.f));
//            iCurrentDamage *= flDamageModifier;
//
//            iPenetration--;
//        }
//        else
//        {
//            VectorSubtract ( tr.endpos, vStart, tmpVec );
//            flTempLength = sqrt(tmpVec.x * tmpVec.x + tmpVec.y * tmpVec.y + tmpVec.z * tmpVec.z);
//
//            if ( flTempLength >= flLength )
//            {
//                if ( iCurrentDamage > 10.f )
//                    return true;
//            }
//        }
//        vecSrc = vecEnd;
//    }
//    return true;
//}

bool __fastcall cAimbot::AutoWallz( Vector vStart, Vector vEnd, C_BaseEntity *pBaseEntity )
{
        trace_t tr,tr2;
        Vector vecSrc,vecEnd,vecDir,tmpVec;
        float flRangeModifier,flPenetrationDistance,flCurrentDistance = 0.0f;
        int iPenetration;
        float iCurrentDamage = 0;
        int iPenetrationPower = 0;
        float flLength = 0.0f;
        float flTempLength = 0.0f;
        int iBulletType = 0;
        float flTravelledDistance = 0.0f;

        C_BaseEntity*pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();

        if( !pLocal )
                return false;

        CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocal);
        int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));

        DWORD dwTemp[5];
        this->TraceFilter( dwTemp, pBaseEntity, pLocal, 0 );
/*    DWORD dwTraceFilter = this->dwTraceFilter;
      DWORD dwGetBulletTypeParameters = this->dwGetBulletTypeParameters;
      DWORD dwGetTextureInformation = this->dwGetTextureInformation*/;

        //math.fastMemCopy(&vStart,&vecSrc,sizeof(Vector));
        VectorCopy(vStart,vecSrc);
        vecDir = vEnd - vStart;
        flLength = sqrt ( vecDir.x * vecDir.x + vecDir.y * vecDir.y + vecDir.z * vecDir.z );
        vecDir /= flLength;
        VectorNormalize(vecDir);

        if(!gNospread.GetWeaponInfo(pWeapon,iWeaponID,iBulletType,iPenetration,iCurrentDamage,flCurrentDistance,flRangeModifier))
                return false;

        float fPenetrationPower = 0.0f;

        __asm
        {
                LEA ECX, flPenetrationDistance
                        PUSH ECX
                        LEA EDX, fPenetrationPower
                        PUSH EDX
                        PUSH iBulletType
                        CALL g_cAimbot.dwGetBulletTypeParameters
                        }

        iPenetrationPower = (int)fPenetrationPower;

        float flDamageModifier = 20.0f;

        while(iPenetration || iCurrentDamage > 0.f)
        {
                vecEnd = vecSrc + vecDir * 10.0f;

                if(flTravelledDistance > flCurrentDistance)
                        return false;

                pTraceLine( vecSrc, vecEnd, 0x200400B, (CTraceFilterSkipTwoEntities*)&dwTemp, &tr);

                surfacedata_t *g_pSurfaceData = g_pPhysicAPI->GetSurfaceData( tr.surface.surfaceProps );
                int iMaterial = g_pSurfaceData->game.material;

                float flPenetrationPowerModifier = 0.0f;
                __asm
                {
                        LEA EAX, flDamageModifier
                                LEA ECX, flPenetrationPowerModifier
                                MOV EDX, iMaterial
                                CALL g_cAimbot.dwGetTextureInformation
                                }

                iPenetrationPower *= flPenetrationPowerModifier;

                flTravelledDistance += 10.f;

                if(tr.fraction != 1.0)
                {
                        if( tr.allsolid )
                                return false;

                        VectorSubtract ( tr.endpos, vStart, tmpVec );
                        flTempLength = sqrt(tmpVec.x * tmpVec.x + tmpVec.y * tmpVec.y+ tmpVec.z * tmpVec.z);

                        if ( flTempLength >= flLength )
                        {
                                if ( iCurrentDamage > 10.f )
                                        return true;
                        }

                        iCurrentDamage *= (powf (flRangeModifier, (tr.fraction * flTempLength) / 500.f));
                        iCurrentDamage *= flDamageModifier;

                        iPenetration--;
                }
                else
                {
                        VectorSubtract ( tr.endpos, vStart, tmpVec );
                        flTempLength = sqrt(tmpVec.x * tmpVec.x + tmpVec.y * tmpVec.y + tmpVec.z * tmpVec.z);

                        if ( flTempLength >= flLength )
                        {
                                if ( iCurrentDamage > 10.f )
                                        return true;
                        }
                }
                vecSrc = vecEnd;
        }
        return true;
}

//bool __fastcall cAimbot::AutoWall( Vector vStart, Vector vEnd, C_BaseEntity *pBaseEntity )
//{
//    trace_t tr,tr2;
//    Vector vecSrc,vecEnd,vecDir,tmpVec;
//    float flRangeModifier,flPenetrationDistance,flCurrentDistance = 0.0f;
//    int iPenetration;
//    int iCurrentDamage = 0;
//    int iPenetrationPower = 0;
//    float flLength = 0.0f;
//    float flTempLength = 0.0f;
//    int iBulletType = 0;
//    float flTravelledDistance = 0.0f;
//
//    C_BaseEntity*pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
//
//    if( !pLocal )
//        return false;
//
//    CBaseCombatWeapon* pWeapon = gNospread.GetBaseCombatActiveWeapon(pLocal);
//    int iWeaponID = gNospread.getWeaponID(g_pModelinfo->GetModelName(pWeapon->GetModel()));
//
//    DWORD dwTemp[5];
//    const DWORD dwTraceFilter = this->dwTraceFilter;
//    const DWORD dwGetBulletTypeParameters = this->dwGetBulletTypeParameters;
//    const DWORD dwGetTextureInformation = this->dwGetTextureInformation;
//
//    VectorCopy(vStart,vecSrc);
//    vecDir = vEnd - vStart;
//    flLength = sqrt ( vecDir.x * vecDir.x + vecDir.y * vecDir.y + vecDir.z * vecDir.z );
//    vecDir /= flLength;
//
//    if(!gNospread.GetWeaponInfo(pWeapon,iWeaponID,iBulletType,iPenetration,iCurrentDamage,flCurrentDistance,flRangeModifier))
//        return false;
//
//    float fPenetrationPower = 0.0f;
//
//    __asm
//    {
//        LEA ECX, flPenetrationDistance
//            PUSH ECX
//            LEA EDX, fPenetrationPower
//            PUSH EDX
//            PUSH iBulletType
//            CALL g_cAimbot.dwGetBulletTypeParameters
//    }
//
//    iPenetrationPower = (int)fPenetrationPower;
//
//    float flDamageModifier = 0.5f;
//
//    while(iPenetration || iCurrentDamage > 0.f)
//    {
//        vecEnd = vecSrc + vecDir * 10.f;
//
//        if(flTravelledDistance > flCurrentDistance)
//            return false;
//
//        _asm
//        {
//            PUSH COLLISION_GROUP_NONE
//                PUSH pLocal
//                PUSH pBaseEntity
//                LEA ECX, dwTemp
//                CALL g_cAimbot.dwTraceFilter
//        }
//
//        pTraceLine( vecSrc, vecEnd, /*0x200400B*/MASK_SHOT, (ITraceFilter*)&dwTemp, &tr);
//
//        if(tr.m_pEnt)
//            pBaseEntity = tr.m_pEnt;
//
//        _asm
//        {
//            PUSH COLLISION_GROUP_NONE
//            PUSH pBaseEntity
//            PUSH pLocal
//            LEA ECX, dwTemp
//            CALL g_cAimbot.dwTraceFilter
//        }
//           
//        pTraceLine( vecSrc, vecEnd, /*0x200400B*/MASK_SHOT, (ITraceFilter*)&dwTemp, &tr);
//
//        surfacedata_t *g_pSurfaceData = g_pPhysicAPI->GetSurfaceData( tr.surface.surfaceProps );
//        int iMaterial = g_pSurfaceData->game.material;
//
//        float flPenetrationPowerModifier = 0.0f;
//        switch ( (char)iMaterial )
//        {
//        case 'D':
//        case 'M':
//            flPenetrationPowerModifier = 0.5;
//            flDamageModifier = 0.3;
//            break;
//        case 'C':
//            flPenetrationPowerModifier = 0.4;
//            flDamageModifier = 0.25;
//            break;
//        case 'G':
//            flPenetrationPowerModifier = 1.0;
//            flDamageModifier = 1.0;
//            break;
//        case 'V':
//            flPenetrationPowerModifier = 0.5;
//            flDamageModifier = 0.45;
//            break;
//        case 'T':
//            flPenetrationPowerModifier = 0.65;
//            flDamageModifier = 0.3;
//            break;
//        case 'P':
//            flPenetrationPowerModifier = 0.4;
//            flDamageModifier = 0.45;
//            break;
//        case 'W':
//            flPenetrationPowerModifier = 1.0;
//            flDamageModifier = 0.6;
//            break;
//        default:
//            flPenetrationPowerModifier = 1.0;
//            flDamageModifier = 0.5;
//            break;
//        }
//
//        iPenetrationPower *= flPenetrationPowerModifier;
//
//        flTravelledDistance += 10.f;
//
//        if(tr.fraction != 1.0)
//        {
//            if( tr.allsolid )
//                return false;
//
//            VectorSubtract ( tr.endpos, vStart, tmpVec );
//            flTempLength = sqrt(tmpVec.x * tmpVec.x + tmpVec.y * tmpVec.y + tmpVec.z * tmpVec.z);
//
//            iCurrentDamage *= (powf (flRangeModifier, (flTempLength * 0.002f)));
//            iCurrentDamage *= flDamageModifier;
//
//            if ( flTempLength > flLength )
//            {
//                if ( iCurrentDamage > 1.f )
//                    return true;
//            }
//
//            iPenetration--;
//        }
//        else
//        {
//            VectorSubtract ( tr.endpos, vStart, tmpVec );
//            flTempLength = sqrt(tmpVec.x * tmpVec.x + tmpVec.y * tmpVec.y + tmpVec.z * tmpVec.z);
//
//            if ( flTempLength > flLength )
//            {
//                if ( iCurrentDamage > 1.f )
//                    return true;
//            }
//        }
//        vecSrc = vecEnd;
//    }
//    return false;
//}

//
bool cAimbot::GetAllPoints( C_BaseEntity *pEnt, int iBone, Vector &vPoints )
{
        matrix3x4_t Matrix[MAXSTUDIOBONES];
        if( pEnt->SetupBones( Matrix, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0))
        {
                studiohdr_t *pStudioHeader = g_pModelinfo->GetStudiomodel( pEnt->GetModel() );
                if( pStudioHeader )
                {
                        if (iBone < 0 || iBone >= pStudioHeader->numbones)
                                return false;

                        QAngle qAngles;
                        MatrixAngles(Matrix[iBone],qAngles,vPoints);
                }
        }
        return true;
}

//bool cAimbot::KnifeBot ( Vector& vecAbsOrigin, Vector& vecEndPos, CBaseEntity *pBaseEntity )
//{
//    float flDist = GetDistance(vecEndPos, vecAbsOrigin);
//    if(flDist < 6.8)
//        return true;
//
//    return false;
//}

//void cAimbot::BypassNameProtection(C_BaseEntity* pEnt)
//{
//    player_info_t pinfo;
//    g_pEngine->GetPlayerInfo(pEnt->index, &pinfo);
//    char* newname;
//    sprintf_s(newname, sizeof(newname), "%s\x20\x1F", pinfo.name);
//    g_pFriends->SetPersonaName(newname);
//}

//C_BaseEntity* __fastcall cAimbot::GetFirstEntity(C_BaseEntity *pMe)
//{
//    IClientEntity* pEnemyClient;
//    C_BaseEntity *pEnemy;
//
//    for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
//    {
//        if(nIndex != g_pEngine->GetLocalPlayer())
//        {
//            pEnemyClient = g_pEntList->GetClientEntity(nIndex);
//            if(pEnemyClient && !pEnemyClient->IsDormant())
//            {
//                pEnemy = pEnemyClient->GetBaseEntity();
//                if(IsAlive(pEnemy))
//                {
//                    if(GetTeamNumber(pEnemy) != GetTeamNumber(pMe))
//                    {
//                        return pEnemy;
//                    }
//                }
//            }
//        }
//    }
//    return NULL;
//}
//
//C_BaseEntity* __fastcall cAimbot::GetNearest(C_BaseEntity *pMe, Vector vMyEyePosition)
//{
//    IClientEntity* pEnemyClient;
//    C_BaseEntity *pEnemy, *pFirstEntity;
//    Vector vEnemyPosition, vTempPosition;
//
//    pFirstEntity = GetFirstEntity(pMe);
//
//    if(pFirstEntity)
//    {
//        vTempPosition = GetPredictedEyePosition(pFirstEntity);
//        for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
//        {
//            if(nIndex != g_pEngine->GetLocalPlayer() && nIndex != pFirstEntity->entindex())
//            {
//                pEnemyClient = g_pEntList->GetClientEntity(nIndex);
//                if(pEnemyClient && !pEnemyClient->IsDormant())
//                {
//                    pEnemy = pEnemyClient->GetBaseEntity();
//                    vEnemyPosition = GetPredictedEyePosition(pEnemy);
//                    if(IsAlive(pEnemy))
//                    {
//                        if(GetTeamNumber(pEnemy) != GetTeamNumber(pMe))
//                        {
//                            if(GetDistance(vMyEyePosition, vEnemyPosition) < GetDistance(vMyEyePosition, vTempPosition))
//                                //if(GetVisible(vMyEyePosition, vEnemyPosition) || (AutoWall(vMyEyePosition, vEnemyPosition,pEnemy)))
//                                return pEnemy;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return pFirstEntity;
//}


void cAimbot::Main(CUserCmd* pUserCmd)
{
        IClientEntity* pEnemyClient;
        C_BaseEntity* pMe, *pEnemy;
        Vector vMyEyePosition, vDelta, vTemp;

        pMe = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
        if(IsAlive(pMe))
        {   
                DropTarget();
                vMyEyePosition = GetPredictedEyePosition(pMe);
       
                for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
                {
                        if(nIndex != g_pEngine->GetLocalPlayer())
                        {
                                pEnemyClient = g_pEntList->GetClientEntity(nIndex);
                                if(pEnemyClient && !pEnemyClient->IsDormant())
                                {
                                        pEnemy = pEnemyClient->GetBaseEntity();
                                        player_info_t pInfo;
                                        g_pEngine->GetPlayerInfo(pEnemyClient->entindex(), &pInfo);

                                        if(IsAlive(pEnemy))
                                        {
                                                color32* Model = (color32*)((DWORD)pEnemy + (DWORD)0x58 );

                                                if(gCvar.esp_ammo)
                                                {
                                                        color32* Model = (color32*)((DWORD)pEnemy + (DWORD)0x58 );
                                                        if (Model && g_cAimbot.GetVisible(vMyEyePosition,pMe,pEnemy));/*this can be found in royalpub1d*/
                                                        {

                                                                if (GetTeamNumber(pEnemy) == 2) // Terrorist
                                                                {
                                                                        Model->r = (byte)255;
                                                                        Model->g = (byte)0;
                                                                        Model->b = (byte)0;
                                                                        Model->a = (byte)255;
                                                                }

                                                                if (GetTeamNumber(pEnemy) == 3) //Ct's
                                                                {

                                                                        Model->r = (byte)0;
                                                                        Model->g = (byte)0;
                                                                        Model->b = (byte)255;
                                                                        Model->a = (byte)255;
                                                                }
                                                                // Now if they aren't visible (behind a wall)
                                                                else if (Model && !g_cAimbot.GetVisible(vMyEyePosition,pMe,pEnemy));
                                                                {

                                                                        if (GetTeamNumber(pEnemy) == 2) // t again
                                                                        {
                                                                                Model->r = (byte)255;
                                                                                Model->g = (byte)240;
                                                                                Model->b = (byte)0;
                                                                                Model->a = (byte)255;
                                                                        }

                                                                        if (GetTeamNumber(pEnemy) == 3) // ct again
                                                                        {
                                                                                Model->r = (byte)0;
                                                                                Model->g = (byte)255;
                                                                                Model->b = (byte)0;
                                                                                Model->a = (byte)255;
                                                                        }
                                                                }
                                                        }

                                                        // Makes the normal
                                                        if(!gCvar.esp_ammo)
                                                        {
                                                                color32* Model = (color32*)((DWORD)pEnemy + (DWORD)0x58 );

                                                                if (GetTeamNumber(pEnemy) == 2) // t again
                                                                {
                                                                        Model->r = (byte)255;
                                                                        Model->g = (byte)255; // Make them normal colour
                                                                        Model->b = (byte)255;
                                                                        Model->a = (byte)255;
                                                                }

                                                                if (GetTeamNumber(pEnemy) == 3) // ct
                                                                {
                                                                        Model->r = (byte)255;
                                                                        Model->g = (byte)255;
                                                                        Model->b = (byte)255; // Make them normal colour
                                                                        Model->a = (byte)255;
                                                                }

                                                        }
                                                }

                                                if(GetTeamNumber(pEnemy) != GetTeamNumber(pMe))
                                                {
                                                        if(GetHitboxPosition(nIndex))
                                                        {
                                                                //PredictTarget(nIndex);
                                                                if(AutoWallz( m_vPosition,vMyEyePosition, pEnemy ) )
                                                                {
                                                                        float dick = GetRadius(m_vPosition, pEnemy);
                                                                        if(m_flBestDist > dick)
                                                                        {
                                                                                m_flBestDist = dick;
                                                                                m_nTarget = nIndex;
                                                                                m_vFinalPosition = m_vPosition;
                                                                        }
                                                                }
                                                                //else
                                                                //{
                                                                //    Vector vBones[50];

                                                                //    QAngle qAsd;
                                                                //    for(size_t lol = 0; lol < 49; lol++)
                                                                //    {
                                                                //            GetBonePosition(lol,vBones[lol],qAsd,pEnemy->index);//LOL NO WONDER IT DIDNT WORK LOL OWNED
                                                                //            //PredictTarget(pEnemy,vBones[lol],pMe);
                                                                //            if(AutoWallz(vBones[lol], m_vPosition))
                                                                //            {
                                                                //                float dick = GetRadius(vMyEyePosition, pEnemy);
                                                                //                if(m_flBestDist > dick)
                                                                //                {
                                                                //                    m_flBestDist = dick;
                                                                //                    m_nTarget = nIndex;
                                                                //                    m_vFinalPosition = vBones[lol];
                                                                //                }
                                                                //            }
                                                                //}       
                                                                //    }
                                                        }
                                                }
                                        }
                                }
                        }


                        if(m_nTarget != -1)
                        {
                                C_BaseCombatWeapon *m_pWeapon = gNospread.GetBaseCombatActiveWeapon(pMe);
                                if(gCvar.misc_knifebot && gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_KNIFE)
                                {
                                        if(KnifeBot(m_vFinalPosition, vMyEyePosition, pEnemy))
                                        {
                                                pUserCmd->buttons |= IN_ATTACK2;
                                                return;
                                        }
                                }

                                if(!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_HE_GRENADE))
                                        if(!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_KNIFE))
                                                if(!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_SMOKE_GRENADE))
                                                        if(!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_FLASHBANG))
                                                                if(!(gNospread.getWeaponID(g_pModelinfo->GetModelName(m_pWeapon->GetModel())) == WEAPON_C4))
                                                                        if(gCvar.aim_autoshoot)
                                                                        {
                                                                                pUserCmd->buttons |= IN_ATTACK;
                                                                        }

                                //m_vLastPosition[m_nTarget]= m_vFinalPosition;

                                if(gCvar.aim_on)
                                        CalcAngle(vMyEyePosition, m_vFinalPosition, pUserCmd->viewangles);

                                //if( gCvar.aim_smooth /*> 1 */)
                                //{

                                //    QAngle qCurrentView;
                                //    g_pEngine->GetViewAngles(qCurrentView);
                                //    QAngle qDelta = pUserCmd->viewangles - qCurrentView;
                                //    if(qDelta[0]>180)  qDelta[0]-=360;
                                //    if(qDelta[1]>180)  qDelta[1]-=360;
                                //    if(qDelta[0]<-180) qDelta[0]+=360;
                                //    if(qDelta[1]<-180) qDelta[1]+=360;
                                //    pUserCmd->viewangles = qCurrentView + qDelta / gCvar.aim_smooth;
                                //    if(pUserCmd->viewangles[0] >  180) pUserCmd->viewangles[0]-=360;
                                //    if(pUserCmd->viewangles[1] >  180) pUserCmd->viewangles[1]-=360;
                                //    if(pUserCmd->viewangles[0] < -180) pUserCmd->viewangles[0]+=360;
                                //    if(pUserCmd->viewangles[1] < -180) pUserCmd->viewangles[1]+=360;
                                //}

                                if(!gCvar.aim_silent)
                                        g_pEngine->SetViewAngles(pUserCmd->viewangles);
                        }
                }
        }
}   
//else
//{
//    int bestPosition = -1;
//    float secondaryLowestHealth = FLT_MAX;
//
//    for ( int cornerIndex = 1; cornerIndex <= 8; ++cornerIndex )
//    {
//        traceInfo = GetVisibility( vMyEyePosition, AimPoints[pEntity->index][cornerIndex], pMe, pEntity, WeaponInfo );GetBoxPoints
//        healthLeft = ( health - traceInfo.damage );
//
//        if ( ( traceInfo.damage != -1 ) && healthLeft <= secondaryLowestHealth )
//        {
//            bestPosition = cornerIndex;
//            secondaryLowestHealth = healthLeft;
//        }
//    }
//
//    if ( ( bestPosition != -1 ) && secondaryLowestHealth <= lowestHealth )
//    {
//        this->m_nTarget = nIndex;
//        this->m_vFinalPosition =  AimPoints[pEntity->index][bestPosition];
//        lowestHealth = secondaryLowestHealth;
//    }
//}
//}
//Vector highPosition = ( ( AimPoints[pEntity->index][4] + AimPoints[pEntity->index][5] ) * .5f );
//
//Vector upDirection = ( highPosition - AimPoints[pEntity->index][CENTER] );
//float maxHeight = upDirection.NormalizeInPlace() * ( 1 + (1/3) );

//Vector vBones[50];

//QAngle qAsd;
//for(size_t lol = 0; lol < 49; lol++)
//{
//    GetAllPoints(pEnemy,lol,vBones[lol]);//LOL NO WONDER IT DIDNT WORK LOL OWNED
//    PredictTarget(pEnemy,vBones[lol],pMe);
//    if(AutoWall(vMyEyePosition,vBones[lol],pEnemy))
//    {
//        float dick = GetRadius(vMyEyePosition, pEnemy);
//        if(m_flBestDist > dick)
//        {
//            math.fastMemCopy(&m_flBestDist, &dick, sizeof(float)); //m_flBestDist = flDistance
//            math.fastMemCopy(&m_nTarget, &nIndex, sizeof(int)); //m_nTarget = pEnemy->entindex()
//            math.fastMemCopy(&m_vFinalPosition, &vBones[lol], sizeof(Vector));// so how

//Vector lol[9];
//GetAimPoints(pEnemy,lol,true);
//{
//    for( int cornerIndex = 1; cornerIndex <= 8; ++cornerIndex )
//    {
//        PredictTarget(nIndex);
//        if(AutoWall(lol[cornerIndex],vMyEyePosition,pEnemy))
//        {
//            float dick = GetRadius(m_vPosition, pEnemy);
//            if(m_flBestDist > dick)
//            {
//                math.fastMemCopy(&m_flBestDist, &dick, sizeof(float)); //m_flBestDist = flDistance
//                math.fastMemCopy(&m_nTarget, &nIndex, sizeof(int)); //m_nTarget = pEnemy->entindex()
//                math.fastMemCopy(&m_vFinalPosition, &lol[cornerIndex], sizeof(Vector));// so how


//void cAimbot::Main(CUserCmd* pUserCmd)
//{
//    IClientEntity* pEnemyClient;
//    C_BaseEntity* pMe, *pEnemy;
//    Vector vMyEyePosition, vDelta, vTemp;
//
//    pMe = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
//    if(IsAlive(pMe))
//    {
//        vMyEyePosition = GetPredictedEyePosition(pMe);
//        DropTarget();
//        for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
//        {
//            if(nIndex != g_pEngine->GetLocalPlayer())
//            {
//                pEnemyClient = g_pEntList->GetClientEntity(nIndex);
//                if(pEnemyClient && !pEnemyClient->IsDormant())
//                {
//                    pEnemy = pEnemyClient->GetBaseEntity();
//                    player_info_t pInfo;
//                    g_pEngine->GetPlayerInfo(pEnemyClient->entindex(), &pInfo);
//                    {
//                        if(IsAlive(pEnemy))
//                        {
//                            //if(gCvar.aim_dm && GetHealth(pEnemy) >= 500)
//                            //{
//                            if(GetTeamNumber(pEnemy) != GetTeamNumber(pMe))
//                            {
//                                Vector lol[9];
//                                GetAimPoints(pEnemy,lol,true);
//                                {
//                                    if(AutoWall(vMyEyePosition,lol[0],pEnemy))
//                                    {
//                                        float dick = GetRadius(m_vPosition, pEnemy);
//                                        if(m_flBestDist > dick)
//                                        {
//                                            m_flBestDist = dick;
//                                            m_nTarget = nIndex;
//                                            m_vFinalPosition = lol[0];
//                                        }
//                                    }
//                                    else
//                                    {
//                                        for( int cornerIndex = 0; cornerIndex <= 8; ++cornerIndex )
//                                        {
//                                            if(AutoWall(vMyEyePosition,lol[cornerIndex],pEnemy))
//                                            {
//                                                float dick = GetRadius(m_vPosition, pEnemy);
//                                                if(m_flBestDist > dick)
//                                                {
//                                                    m_flBestDist = dick;
//                                                    m_nTarget = nIndex;
//                                                    m_vFinalPosition = lol[cornerIndex];
//                                                    break;
//                                                    //memcpy ja dumt XD ja ok
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//

//void cAimbot::Main(CUserCmd* pUserCmd)
//{
//    IClientEntity* pEnemyClient;
//    C_BaseEntity* pMe, *pEnemy;
//    Vector vMyEyePosition, vDelta, vTemp;
//
//    pMe = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer())->GetBaseEntity();
//    if(IsAlive(pMe))
//    {
//        vMyEyePosition = GetPredictedEyePosition(pMe);
//        DropTarget();
//        for(int nIndex = 1; nIndex <= g_pEngine->GetMaxClients(); ++nIndex)
//        {
//            if(nIndex != g_pEngine->GetLocalPlayer())
//            {
//                pEnemyClient = g_pEntList->GetClientEntity(nIndex);
//                if(pEnemyClient && !pEnemyClient->IsDormant())
//                {
//                    pEnemy = pEnemyClient->GetBaseEntity();
//                    player_info_t pInfo;
//                    g_pEngine->GetPlayerInfo(pEnemyClient->entindex(), &pInfo);
//                    {
//                        if(IsAlive(pEnemy))
//                        {
//                            //if(gCvar.aim_dm && GetHealth(pEnemy) >= 500)
//                            //{
//                            if(GetTeamNumber(pEnemy) != GetTeamNumber(pMe))
//                            {
//                                Vector lol[9];
//                                GetAimPoints(pEnemy,lol,true);
//                                {
//                                    if(AutoWall(vMyEyePosition,pEnemy,lol[0]))
//                                    {
//                                        float dick = GetRadius(m_vPosition, pEnemy);
//                                        if(m_flBestDist > dick)
//                                        {
//                                            m_flBestDist = dick;
//                                            m_nTarget = nIndex;
//                                            m_vFinalPosition = lol[0];
//                                        }
//                                    }
//                                    else
//                                    {                               
//                                            for( int cornerIndex = 1; cornerIndex <= 8; ++cornerIndex )
//                                            {
//                                                if(AutoWall(vMyEyePosition,pEnemy,lol[cornerIndex]))
//                                                {
//                                                    float dick = GetRadius(m_vPosition, pEnemy);
//                                                    if(m_flBestDist > dick)
//                                                    {
//                                                        m_flBestDist = dick;
//                                                        m_nTarget = nIndex;
//                                                        m_vFinalPosition = lol[cornerIndex];
//                                                        break;
//                                                        //memcpy ja dumt XD ja ok
//                                                    }
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
