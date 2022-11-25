#include "stdafx.h"
#include "aimbot.h"
#include "sdk.h"
#include "CEntity/CPlayer.h"
#include "SDK/public/collisionutils.h"

cAimbot::cAimbot( void )
{
        flBestDist = 99999.9f;
        m_nTarget = -1;
        bSetViewAngles = false;
}

static inline float flChargeBeginTime( IClientEntity* p )
{
        C_BaseEntity* pEntity = p->GetBaseEntity( );

        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)pEntity;
        GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pMe;
        IClientEntity* pWeaponEnt = (IClientEntity*)HalFLife2.m_pEntList->GetClientEntity(pMe->hActiveWeapon()->GetEntryIndex());
        C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)pWeaponEnt;

        GenDT_WeaponCompoundBow* pBow = (GenDT_WeaponCompoundBow*)pWeapon;
        float flChargeStartTime = *pBow->PipebombLauncherLocalData()->flChargeBeginTime();

        //Trace("%f, %f, %f", (*pMe->localdata()->vecViewOffset0()).x, (*pMe->localdata()->vecViewOffset0()).y, (*pMe->localdata()->vecViewOffset0()).z);

        return flChargeStartTime;
}

static inline float GetCurrentCharge( IClientEntity* p )
{
        if ( flChargeBeginTime( p )>0.0f ) return HalFLife2.m_pGlobals->curtime - flChargeBeginTime( p );
        else return 0.0f;
}

static inline bool IsBeingCharged( IClientEntity* p )
{
        return flChargeBeginTime( p )>0.0f;
}

void cAimbot::DropTarget( void )
{
        flBestDist = 99999.9f;
        m_nTarget = -1;
}

int	cAimbot::iGetTarget( void )
{
        return m_nTarget;
}

void cAimbot::MakeVector( QAngle angle, QAngle& vector )
{
        float pitch;
        float yaw;
        float tmp;

        pitch	= (float)(angle[0] * M_PI/180);
        yaw		= (float)(angle[1] * M_PI/180);
        tmp		= (float) cos(pitch);

        vector[0] = (float) (-tmp * -cos(yaw));
        vector[1] = (float) (sin(yaw)*tmp);
        vector[2] = (float) -sin(pitch);
}

void cAimbot::CalcAngle( Vector &src, Vector &dst, QAngle &angles )
{
        double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };
        double hyp = FastSqrt(delta[0]*delta[0] + delta[1]*delta[1]);

        angles[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
        angles[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
        angles[2] = 0.0f;

        qAimAngle[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
        qAimAngle[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
        qAimAngle[2] = 0.0f;

        if(delta[0] >= 0.0) { angles[1] += 180.0f; }
}

float cAimbot::CalcAngleDiff( Vector &src, Vector &dst, QAngle &angles )
{
        QAngle NewAngle;

        double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };
        double hyp = FastSqrt(delta[0]*delta[0] + delta[1]*delta[1]);

        NewAngle[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
        NewAngle[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
        NewAngle[2] = 0.0f;

        if(delta[0] >= 0.0) { NewAngle[1] += 180.0f; }

        float angleDiff = angles[1] - NewAngle[1];

        if ( angleDiff < 0.0f )
                angleDiff *= -1.0f;

        if ( angleDiff > 360 )
                angleDiff -= 360;

        //add_log("%f, %f, %f", angleDiff, angles[1], NewAngle[1]);
        //Trace("%f, %f, %f", angleDiff, angles[1], NewAngle[1]);

        return angleDiff;

}

bool IsDisguised(GenDT_TFPlayer *TFME)
{

        return (*TFME->Shared()->nPlayerCond() & PLAYERCOND_DISGUISED) == PLAYERCOND_DISGUISED;

}

bool IsUbered(GenDT_TFPlayer *TFME)
{

        return (*TFME->Shared()->nPlayerCond() & TF_CONDFLAG_UBERCHARGED) == TF_CONDFLAG_UBERCHARGED;

}

bool IsCloaked(GenDT_TFPlayer *TFME)
{
        return (*TFME->Shared()->nPlayerCond() & TF_CONDFLAG_CLOAKED) == TF_CONDFLAG_CLOAKED;

}

bool cAimbot::GetHitboxPosition( int iHitbox, Vector& vecOrigin, CBaseEntity* pEntity )
{
        try
        {
                GenDT_TFPlayer *pTargetPlayer = (GenDT_TFPlayer*)pEntity;

                matrix3x4_t pmatrix[MAXSTUDIOBONES];
                mstudiohitboxset_t* set;
                mstudiobbox_t* box;
                Vector min, max;

                if ( iHitbox < 0 || iHitbox >= 20 )
                        return false;

                const model_t* model = pEntity->GetModel();

                if (!model)
                {
                        //add_log("model");
                        return false;
                }

                if( IsDisguised(pTargetPlayer ) ) model = HalFLife2.m_pModelInfoClient->GetModel( HalFLife2.m_pModelInfoClient->GetModelIndex( "models/player/spy.mdl" ) );

                studiohdr_t *pStudioHdr = HalFLife2.m_pModelInfoClient->GetStudiomodel( model );
                if (!pStudioHdr)
                        return false;

                if ( !pEntity->SetupBones( pmatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f ) )
                        return false;

                set = pStudioHdr->pHitboxSet( 0 );
                box = pStudioHdr->pHitbox( iHitbox, NULL );

                MatrixAngles( pmatrix[ box->bone ], QAngle(), vecOrigin );
                VectorTransform( box->bbmin, pmatrix[ box->bone ], min );
                VectorTransform( box->bbmax, pmatrix[ box->bone ], max );
                vecOrigin = ( min + max ) * 0.5f;

                return true;
        }
        catch(...) //--Bad pointers, etc
        {

                Trace( "GetHitbox() Crashed!?" );
                return false;
        }
}

//===================================================================================
float cAimbot::flGetDistance( Vector vOrigin )
{
        IClientEntity *pLocalEnt = HalFLife2.m_pEntList->GetClientEntity( HalFLife2.m_pEngineClient->GetLocalPlayer( ) );

        if( pLocalEnt == NULL )
                return 1.0f;

        Vector vDistance = vOrigin - HalFLife2.m_pMyPlayer->Ent()->GetAbsOrigin( );

        float flDistance = SQUARE( vDistance.Length( ) );

        if( flDistance < 1.0f )
                return 1.0f;

        return flDistance;
}

float cAimbot::CalcFOVAngle( QAngle qAngle, Vector vSrc, Vector vDst )
{
        float fFOV = 0.0f;
        QAngle qAng,qAim;

        CalcAngle( vSrc, vDst, qAng );
        MakeVector( qAngle, qAim );
        MakeVector( qAng, qAng );

        float mag_s = FastSqrt(SQUARE(qAim[0]) + SQUARE(qAim[1]) + SQUARE(qAim[2]));
        float mag_d = FastSqrt(SQUARE(qAng[0]) + SQUARE(qAng[1]) + SQUARE(qAng[2]));

        float u_dot_v = qAim[0]*qAng[0] + qAim[1]*qAng[1] + qAim[2]*qAng[2];

        fFOV = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI);

        return fFOV;
}

float cAimbot::flGetFOV( QAngle angle, Vector vOrigin, Vector vDest )
{
        float fFOV = 0.0f;
        QAngle qAngle, qAim;

        IClientEntity* pClientEnt = HalFLife2.m_pEntList->GetClientEntity( HalFLife2.m_pEngineClient->GetLocalPlayer( ) );

        if( pClientEnt == NULL )
                return 1.0f;
        C_BaseEntity* pBaseEnt = pClientEnt->GetBaseEntity( );

        if( pBaseEnt == NULL )
                return 1.0f;

        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();
        GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pMe;

        CalcAngle( vOrigin, vDest, qAngle );
        MakeVector( *TFME->tflocaldata()->angEyeAngles0(), qAim );
        MakeVector( qAngle, qAngle );

        float mag_s = SQUARE( qAim.Length( ) );
        float mag_d = SQUARE( qAngle.Length( ) );

        float u_dot_v = qAim[0]*qAngle[0] + qAim[1]*qAngle[1] + qAim[2]*qAngle[2];

        fFOV = acos(u_dot_v / (mag_s*mag_d)) * (180.0f / M_PI);

        return fFOV;
}

float cAimbot::GetFov( QAngle angle, Vector src, Vector dst )
{
        QAngle ang,aim;
        float fov;

        CalcAngle(src, dst, ang);
        MakeVector(angle, aim);
        MakeVector(ang, ang);

        float mag_s = FastSqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2]));
        float mag_d = FastSqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2]));

        float u_dot_v = aim[0]*ang[0] + aim[1]*ang[1] + aim[2]*ang[2];

        fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI);

        return fov;
}

void GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter )
{
        if ( pBaseEnt )
        {
                Vector vMin, vMax;
                pBaseEnt->GetRenderBounds( vMin, vMax );
                vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
                vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;
        }
}

bool cAimbot::GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* pBaseEnt )
{
        player_info_t pinfo;
        trace_t tr;
        Ray_t ray;

        ray.Init( vecAbsStart, vecAbsEnd );
        HalFLife2.m_pEngineTrace->TraceRay( ray, MASK_NPCWORLDSTATIC|CONTENTS_HITBOX|CONTENTS_MONSTER|CONTENTS_MOVEABLE|CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE, NULL, &tr );

        if ( tr.fraction > 0.97f )
                return true;

        //if(tr.fraction <= 0.70f)
        //        return false;

        if ( tr.m_pEnt && pBaseEnt )
        {
                if ( tr.startsolid || tr.allsolid )
                        return false;

                if ( ( HalFLife2.m_pEngineClient->GetPlayerInfo( tr.m_pEnt->index, &pinfo ) || pBaseEnt->index == tr.m_pEnt->index) && tr.fraction > 0.92)
                        return true;
        }
        return false;
}

// Get hitbox position, thanks Xeno
bool cAimbot::GetHitbox ( int hitbox, Vector& vecOrigin, CBaseEntity* pEnt )
{
        try
        {
                GenDT_TFPlayer *pTargetPlayer = (GenDT_TFPlayer*)pEnt;

                float i = HalFLife2.m_pGlobals->curtime;

                matrix3x4_t pmatrix[MAXSTUDIOBONES];
                mstudiohitboxset_t* set;
                mstudiobbox_t* box;
                Vector min, max;

                if ( hitbox < 0 || hitbox >= 20 )
                        return false;

                // Uses wrong model when spy is disguised :(
                const model_t* model = pEnt->GetModel();

                if (!model)
                {
                        //add_log("model");
                        return false;
                }

                if( IsDisguised(pTargetPlayer ) ) model = HalFLife2.m_pModelInfoClient->GetModel( HalFLife2.m_pModelInfoClient->GetModelIndex( "models/player/spy.mdl" ) );

                studiohdr_t *pStudioHdr = (studiohdr_t*)(HalFLife2.m_pModelInfoClient->GetStudiomodel( model ));
                if (!pStudioHdr)
                        return false;

                if ( !pEnt->SetupBones( pmatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f ) )
                        return false;

                set = pStudioHdr->pHitboxSet( 0 );
                box = pStudioHdr->pHitbox( hitbox, NULL );

                MatrixAngles( pmatrix[ box->bone ], QAngle(), vecOrigin );

                VectorTransform( box->bbmin, pmatrix[ box->bone ], min );
                VectorTransform( box->bbmax, pmatrix[ box->bone ], max );
                vecOrigin = ( min + max ) * 0.5f;

                return true;
        }
        catch(...) //--Bad pointers, etc
        {

                Trace( "GetHitbox() Crashed!?" );
                return false;
        }
}

std::string cAimbot::sGetClass (int iClass)
{
        std::string sClass;

        switch(iClass)
        {
        case(TF_SCOUT):
                return "SCOUT";
                break;
        case(TF_SOLDIER):
                return "SOLDIER";
                break;
        case(TF_PYRO):
                return "PYRO";
                break;
        case(TF_DEMOMAN):
                return "DEMOMAN";
                break;
        case(TF_HEAVY):
                return "HEAVY";
                break;
        case(TF_ENGINEER):
                return "ENGINEER";
                break;
        case(TF_MEDIC):
                return "MEDIC";
                break;
        case(TF_SNIPER):
                return "SNIPER";
                break;
        case(TF_SPY):
                return "SPY";
                break;
        default:
                return "other";
                break;
        }

}

void cAimbot::AimAtTarget( CUserCmd* c )
{
        float fAngleDistanceToTravel;

        Vector vecSource;
        QAngle flCurrentAngle = c->viewangles;

        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();
        GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pMe;
        IClientEntity* pWeaponEnt = (IClientEntity*)HalFLife2.m_pEntList->GetClientEntity(pMe->hActiveWeapon()->GetEntryIndex());
        C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)pWeaponEnt;

        DropTarget();
        //----------------------------------//
        player_info_t pinfo;
        Vector vecPunchAngle = *pMe->localdata()->Local()->vecPunchAngle();
        QAngle pPunchAngle = QAngle(vecPunchAngle.x, vecPunchAngle.y, vecPunchAngle.z);
        //----------------------------------//

        for( int index = 1; index <= HalFLife2.m_pEntList->NumberOfEntities( false ); ++index )
        {
                if ( index == HalFLife2.m_pEngineClient->GetLocalPlayer() )
                        continue;

                IClientEntity* ClientEntity = HalFLife2.m_pEntList->GetClientEntity( index );

                if (ClientEntity == NULL)
                        continue;

                CBaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();

                GenDT_BasePlayer *pThem = (GenDT_BasePlayer*)pBaseEntity;


                if (pBaseEntity == NULL/* nothing */)
                {
                        //add_log("%i  :: pBaseEntity == NULL/* nothing */", index);
                        continue;
                }

                GenDT_TFPlayer *TFThem = (GenDT_TFPlayer*)pThem;

                //Trace("%i / %i : %i -- %s", index, HalFLife2.m_pEntList->GetMaxEntities(), (*pThem->lifeState() / 256), pBaseEntity->GetClientClass( )->GetName( ));

                if (pBaseEntity->IsDormant()/* not active */)
                {
                        //add_log("%i  :: pBaseEntity->IsDormant()/* not active */", index);
                        continue;
                }


                if (HalFLife2.m_pEngineClient->GetPlayerInfo( index, &pinfo ) == false/* not a player!*/ ||  !strcmp( pBaseEntity->GetClientClass( )->GetName( ), "CObjectSentrygun" ) )
                {
                        //Trace("%i  :: HalFLife2.m_pEngine->GetPlayerInfo( index, &pinfo ) == false/", index);
                        continue;
                }

                if (*pThem->iTeamNum() == *pMe->iTeamNum()/*enemy*/)
                {
                        //add_log("%i  :: *pBasePlayer->iTeamNum() == HalFLife2.m_pMyPlayer->BaseEnt()->GetTeamNumber()/*enemy*/", index);
                        continue;
                }

                if (*pThem->pl()->deadflag() != 0)
                {
                        //add_log("%i  :: *pBasePlayer->pl()->deadflag() != 0", index);
                        continue;
                }

                if ( IsUbered(TFThem) || IsCloaked(TFThem) )
                {
                        continue;
                }

                std::string sTheirClass = sGetClass(*TFThem->PlayerClass()->iClass());

                vecSource = (*pMe->vecOrigin() + *pMe->localdata()->vecViewOffset0());

                hitboxes_t iHitboxIndex;
                switch (*TFME->PlayerClass()->iClass()) {
                case (TF_SCOUT):
                case (TF_HEAVY):
                case (TF_PYRO):
                        iHitboxIndex = HITBOX_UPPERCHEST;
                        break;
                case (TF_SOLDIER):
                        iHitboxIndex = HITBOX_LEFTFOOT;
                        break;
                default:
                        iHitboxIndex = HITBOX_HEAD;
                        break;
                }

                hitbox = iHitboxIndex;
                if (!GetHitbox( iHitboxIndex, vPlayer, pBaseEntity ))
                {
                        //Trace("%i, %s  :: !GetHitbox( 14/*Head*/, vPlayer, ClientEntity )", index, sTheirClass.c_str());
                        continue;
                }

                float angleDiff = CalcAngleDiff( vecSource, vPlayer, c->viewangles );

                // If crosshair is already on position, fire and return.
                if (angleDiff < 0.25f)
                {
                        //Trace("angleDiff < 0.25f :: %f", angleDiff);
                        if ( pWeapon->GetClientClass()->m_ClassID == WPN_Huntsman )
                                c->buttons &= ~IN_ATTACK;
                        else
                                c->buttons |= IN_ATTACK;
                        DropTarget();
                        return;
                }

                if (angleDiff > 100)
                {
                        //Trace("angleDiff > 100 :: %f", angleDiff);
                        continue;
                }

                if (!GetVisible( vecSource, vPlayer, pBaseEntity )/* not visible */)
                {
                        continue;
                }

                if (flBestDist < angleDiff /* GetFov( *TFME->tflocaldata()->angEyeAngles0(), *pMe->localdata()->vecViewOffset0(), vPlayer ) */ /* flGetFOV( *TFME->tflocaldata()->angEyeAngles0(), vecSource, vPlayer ) */ /* flGetDistance( vPlayer ) */ )
                {
                        //add_log("%i, %f, %f :: flBestDist < GetFov( HalFLife2.m_pMyPlayer->BaseEnt()->GetAbsAngles(), HalFLife2.m_pMyPlayer->BaseEnt()->EyePosition(), vPlayer ))", index, /*GetFov( *TFME->tflocaldata()->angEyeAngles0(), *pMe->localdata()->vecViewOffset0(), vPlayer )*/ flGetDistance( vPlayer ), flBestDist );
                        //Trace("%i, %f less than %f", index, flBestDist, angleDiff);
                        continue;
                }
                else
                {
                        if( m_nTarget != -1 )
                        {
                                GenDT_TFPlayer *pTargetPlayer = (GenDT_TFPlayer*) HalFLife2.m_pEntList->GetClientEntity( m_nTarget )->GetBaseEntity();

                                if (*pTargetPlayer->PlayerClass()->iClass() == TF_MEDIC && *TFThem->PlayerClass()->iClass() != TF_MEDIC)
                                {
                                        continue;
                                }
                        }
                }

                //flBestDist = flGetDistance( vPlayer ); // BEST LOCATION DISTANCE
                //flBestDist = GetFov( *TFME->tflocaldata()->angEyeAngles0(), *pMe->localdata()->vecViewOffset0(), vPlayer ); // BEST FOV DISTANCE
                flBestDist = angleDiff; //Choose closest target to crosshair.

                m_nTarget = index;

                // Calculate the delta origin
                Vector vDeltaOrigin = vPlayer - vPlayer;
                // Calculate the Latency
                float fLatency = HalFLife2.m_pEngineClient->GetNetChannelInfo()->GetLatency( FLOW_OUTGOING );
                // Compensate the latency
                vDeltaOrigin[0] *= fLatency;
                vDeltaOrigin[1] *= fLatency;
                vDeltaOrigin[2] *= fLatency;


                //Apply the prediction
                if ( pWeapon->GetClientClass()->m_ClassID == WPN_Huntsman )
                        PredictedTargetPosition = BallisticPrediction(ClientEntity, pWeapon->GetClientClass()->m_ClassID);
                else
                        PredictedTargetPosition = vPlayer +     vDeltaOrigin;

        }
        if( m_nTarget == -1 )
                return;

        QAngle qCurAngles;
        QAngle qAims;

        HalFLife2.m_pEngineClient->GetViewAngles( qCurAngles );

        CalcAngle( vecSource, PredictedTargetPosition, qAims );
        StrafeCorrection( c, c->viewangles, qAims );

        c->viewangles = qAims;

        //if (bSetViewAngles)
        //HalFLife2.m_pEngineClient->SetViewAngles( qAims );//aim

        if ( pWeapon->GetClientClass()->m_ClassID == WPN_Huntsman )
                c->buttons &= ~IN_ATTACK;
        else
                c->buttons |= IN_ATTACK;

        //c->viewangles = qCurAngles;
        //HalFLife2.m_pEngineClient->SetViewAngles( qCurAngles );//aim

        DropTarget();
}

void cAimbot::TriggerBot(CUserCmd* c)
{
        try
        {
                C_BaseEntity *me = HalFLife2.m_pEntList->GetClientEntity(HalFLife2.m_pEngineClient->GetLocalPlayer())->GetBaseEntity();

                if(!me)
                        return;

                GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)me;
                GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pMe;

                if (*pMe->pl()->deadflag() != 0)
                        return;

                Vector vMe;
                vMe = (*pMe->vecOrigin() + *pMe->localdata()->vecViewOffset0());

                trace_t tr;
                Ray_t ray;
                QAngle fTraceVec;
                Vector Origin;

                fTraceVec = c->viewangles;

                float flOld[3],flNew[3];
                flOld[0] = c->viewangles[0];
                flOld[1] = c->viewangles[1];
                flOld[2] = c->viewangles[2];
                //g_pNoSpread->GetSpreadFix( c->random_seed, flOld, flNew, 1.0 );
                //fTraceVec.x -= flNew[0];
                //fTraceVec.y -= flNew[1];
                //fTraceVec.z -= flNew[2];

                //QAngle *pPunchAngle = ( QAngle* )( (DWORD)HalFLife2.m_pEntList->GetClientEntity(HalFLife2.m_pEngineClient->GetLocalPlayer() )->GetBaseEntity() + (DWORD)hl2_offsets::m_vecPunchAngle );

                //fTraceVec.x -= pPunchAngle->x*2;
                //fTraceVec.y -= pPunchAngle->y*2;
                //fTraceVec.z -= pPunchAngle->z*2;

                AngleVectors(fTraceVec, &Origin);

                Origin = Origin * 8192.0f + vMe;

                ray.Init(vMe, Origin);

                HalFLife2.m_pEngineTrace->TraceRay( ray, 0x4600400B, NULL, &tr );

                QAngle angles;mstudiobbox_t* m_pHitbox = NULL;
                for( int i = 1; i <= HalFLife2.m_pEntList->GetMaxEntities(); i++ )
                {
                        if(i == HalFLife2.m_pEngineClient->GetLocalPlayer())
                                continue;

                        IClientEntity* ClientEntity = HalFLife2.m_pEntList->GetClientEntity( i );

                        if(ClientEntity == NULL || ClientEntity->IsDormant())
                                continue;

                        CBaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();

                        GenDT_BasePlayer *pThem = (GenDT_BasePlayer*)pBaseEntity;
                        GenDT_TFPlayer *TFThem = (GenDT_TFPlayer*)pThem;

                        if(pBaseEntity == NULL || pBaseEntity->IsDormant())
                                continue;

                        if(pBaseEntity->GetTeamNumber() == me->GetTeamNumber())
                                continue;

                        if(!(stricmp( pBaseEntity->GetClientClass()->GetName(), "CTFPlayer" ) == 0))
                                continue;

                        GenDT_BasePlayer *pBasePlayer = (GenDT_BasePlayer*)ClientEntity->GetBaseEntity();

                        if (*pBasePlayer->iTeamNum() == *pMe->iTeamNum()/*enemy*/)
                                continue;

                        if (*pBasePlayer->pl()->deadflag() != 0)
                                continue;

                        //Get Life State
                        if(!((*pBasePlayer->lifeState() / 256)  > LIFE_ALIVE))
                                continue;



                        if (*pBasePlayer->pl()->deadflag() != 0)
                                continue;

                        matrix3x4_t pmatrix[MAXSTUDIOBONES];
                        QAngle angles;

                        const model_t *m_pModel = pBaseEntity->GetModel();


                        if(m_pModel)
                        {

                                studiohdr_t *pStudioHdr = HalFLife2.m_pModelInfoClient->GetStudiomodel(m_pModel);

                                if(pBaseEntity->SetupBones(pmatrix, 128, BONE_USED_BY_HITBOX, GetTickCount()) == false)
                                        continue;

                                mstudiohitboxset_t *set =pStudioHdr->pHitboxSet(0);
                                for(int il = 0; il < pStudioHdr->numhitboxsets;il++)
                                {
                                        for(int r = 0; r < pStudioHdr->iHitboxCount(il); r++)
                                        {
                                                m_pHitbox = pStudioHdr->pHitbox(r, il);

                                                if(!m_pHitbox)
                                                        continue;

                                                MatrixAngles(pmatrix[ m_pHitbox->bone ], angles,vecPosition);
                                                matrix3x4_t matrix = pmatrix[m_pHitbox->bone];
                                                VectorTransform(m_pHitbox->bbmin, pmatrix[ m_pHitbox->bone ], vMin);
                                                VectorTransform(m_pHitbox->bbmax, pmatrix[ m_pHitbox->bone ], vMax);
                                                if(IsRayIntersectingOBB(ray,vecPosition,fTraceVec,m_pHitbox->bbmin,m_pHitbox->bbmax))
                                                {
                                                        if(GetVisible(vMe,(vMin + vMax) * 0.5,pBaseEntity))
                                                        {
                                                                c->buttons |= IN_ATTACK;
                                                        }

                                                }
                                        }
                                }
                        }
                }

                return;
        }
        catch(...)
        {
                return;
        }
}


void GetProjFireSet( Vector vecOffset, Vector &vecFinal, QAngle &angFinal, float flMultiplier, bool bRunTrace = false)
{
        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();

        IClientEntity* pWeaponEnt = (IClientEntity*)HalFLife2.m_pEntList->GetClientEntity(pMe->hActiveWeapon()->GetEntryIndex());
        C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)pWeaponEnt;

        float flTemp;
        if( pWeapon->GetClientClass()->m_ClassID == WPN_Huntsman )
                flTemp = vecOffset.y * -1; //Do this for any flipped weapon models, huntsman is one of them

        Vector vecShootPos = *pMe->vecOrigin() + vecOffset,
                vecForward,
                vecRight,
                vecUp,
                vecTemp01,
                vecTemp02,
                vecTemp03,
                vecTemp04;

        QAngle angAim; //this should be the predicted angle (Player angle when firing)

        AngleVectors( angAim, &vecForward, &vecRight, &vecUp );
        vecTemp01 = vecOffset.z * vecUp;

        if( pWeapon->GetClientClass()->m_ClassID == WPN_Huntsman )
                vecTemp02 = flTemp * vecRight;
        else
                vecTemp02 = vecOffset.y * vecRight;

        vecTemp03 = vecOffset.x * vecForward;
        vecFinal = vecTemp01 + vecTemp02 + vecTemp03;

        vecTemp04 = ( vecForward * flMultiplier ) + vecShootPos;
        VectorAngles( vecTemp04, angFinal );
}

void __fastcall DummyEstimateAbsVelocity( IClientEntity* p, int edx, Vector& vel )
{
        vel.Zero();
}
void EstimateAbsVelocity( IClientEntity* p, Vector& vel )
{
        typedef void (__thiscall* EstimateAbsVelocityFn)( IClientEntity* thisptr, Vector& vel );
        static EstimateAbsVelocityFn pfnEstimateAbsVelocity = NULL;
        if ( !pfnEstimateAbsVelocity )
        {
                // Get the C_BaseEntity::EstimateAbsVelocity function
                //
                // "83EC0C 56 8BF1 E8???? 3BF0 752C"
                //
                // "\x83\xEC\x0C\x56\x8B\xF1\xE8\x00\x00\x00\x00\x3B\xF0\x75\x2C\x00"
                // "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00"
                //
                DWORD dwClientDLL_Init = NULL;
                char szClientDLL_InitSig[] = "\x83\xEC\x0C\x56\x8B\xF1\xE8\x00\x00\x00\x00\x3B\xF0\x75\x2C";
                char szClientDLL_InitMsk[] = "xxxxxxx????xxxx";

                pfnEstimateAbsVelocity = (EstimateAbsVelocityFn) gMemoryTools.dwFindPattern(((DWORD)GetModuleHandleA("client.dll") + 0x1000 ), dwClient_Size - 0x1000 ,(PBYTE)szClientDLL_InitSig, szClientDLL_InitMsk);

                if ( pfnEstimateAbsVelocity )
                {
                        Trace( "BaseEntity() pfnEstimateAbsVelocity = 0x%08X", pfnEstimateAbsVelocity );
                }
                else
                {
                        Trace( "BaseEntity() Couldn't find EstimateAbsVelocity!" );
                        pfnEstimateAbsVelocity = (EstimateAbsVelocityFn) &DummyEstimateAbsVelocity;
                }
        }
        pfnEstimateAbsVelocity( p, vel );
}


// Doesn't work for all projectiles such as rocket launcher
float cAimbot::GetProjectileSpeed( C_BaseCombatWeapon *pBaseWeapon )
{
        float flSpeed;
        _asm
        {
                MOV ESI, pBaseWeapon;
                MOV EDX, DWORD PTR DS:[ESI];
                MOV EAX, DWORD PTR DS:[EDX + 0x67C];
                MOV ECX, ESI;
                CALL EAX;
                FSTP flSpeed;
        }
        return flSpeed;
}


float cAimbot::LinearTimeToImpact( Vector vecDest, float flProjectileSpeed, CBaseEntity* pBaseEnt )
{
        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();

        GenDT_BasePlayer *pThem = (GenDT_BasePlayer*)pBaseEnt;
        GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pThem;

        Vector vecDistance = vecDest - *pMe->localdata()->vecViewOffset0();
        float flDistance = vecDistance.Length();
        float flTime = ( flDistance / flProjectileSpeed ) + 0.05;

        INetChannelInfo* pNet = HalFLife2.m_pEngineClient->GetNetChannelInfo();
        flTime += pNet->GetLatency( FLOW_OUTGOING ); // TODO: Proper interpolation instead of latency

        return flTime;
}

//	Darkcat's magical phallus, part 2: Elecrtic Kangaroo
float cAimbot::BallisticTimeToImpact( Vector vecDest, float flProjectileSpeed, CBaseEntity* pBaseEnt )
{
        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();
        GenDT_BasePlayer *pThem = (GenDT_BasePlayer*)pBaseEnt;
        GenDT_TFPlayer *TFME = (GenDT_TFPlayer*)pThem;
        float flTemp;

        Vector vecOffset = *pMe->localdata()->vecViewOffset0();

        ConVar* cFlipped = HalFLife2.m_pCvar->FindVar( "cl_flipviewmodels" );
        bool bFlipped = cFlipped->GetBool();

        //if (bFlipped)
        //	flTemp = vecOffset.y * -1;

        INetChannelInfo* pNet = HalFLife2.m_pEngineClient->GetNetChannelInfo( );
        Vector vecDistance = vecDest - vecOffset;

        float flGravity = HalFLife2.m_pCvar->FindVar( "sv_gravity" )->GetFloat();

        float flConstA = flGravity * 0.05f * 0.5;
        float flSquaredProjSpeed = SQUARE(flProjectileSpeed);
        float flSquaredConst = SQUARE(flConstA);
        float flMinus1 = flProjectileSpeed - FastSqrt( flSquaredProjSpeed - 4 * flSquaredConst * vecDistance.Length() );
        float flPlus1 = flProjectileSpeed + FastSqrt( flSquaredProjSpeed - 4 * flSquaredConst * vecDistance.Length()  );

        float flResult;

        if ( flMinus1 < 0 )
                flResult = FastSqrt( flPlus1 / ( 2 * flSquaredConst ) );
        else
                flResult = FastSqrt( flMinus1 / ( 2 * flSquaredConst ) );


        flResult += pNet->GetLatency( FLOW_OUTGOING ); // TODO: Proper interpolation instead of latency

        return flResult;
}



void cAimbot::StrafeCorrection( CUserCmd* cmd, QAngle& qaView, QAngle qaAim )
{
        Vector vecMove( cmd->forwardmove, cmd->sidemove, cmd->upmove );

        Vector vecMoveNorm;
        VectorCopy( vecMove, vecMoveNorm );
        vecMoveNorm.NormalizeInPlace();

        QAngle qaMoveNorm;
        VectorAngles( vecMoveNorm, qaMoveNorm );

        QAngle qaAdjusted = qaMoveNorm + ( qaAim - qaView );
        Vector vecForward, vecSide, vecUp;
        AngleVectors( qaAdjusted, &vecForward, &vecSide, &vecUp );

        Vector vecSet = vecForward * vecMove.Length();

        cmd->forwardmove = vecSet.x;
        cmd->sidemove = vecSet.y;
}

Vector cAimbot::GetEyePosition( C_BaseEntity *pBaseEntity )
{
        GenDT_BasePlayer *pThem = (GenDT_BasePlayer*)pBaseEntity;

        return *pThem->localdata()->vecViewOffset0() + pBaseEntity->GetAbsOrigin();
}

float cAimbot::SolveTime(IClientEntity *target,Vector vTargetPosition,float ProjectileSpeed,float ent_gravity,float proj_gravity)
{
        C_BaseEntity* pEntity = target->GetBaseEntity();
        GenDT_BasePlayer *pThem = (GenDT_BasePlayer*)pEntity;
        GenDT_TFPlayer *TFThem = (GenDT_TFPlayer*)pThem;
        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();
        IClientEntity* pWeaponEnt = (IClientEntity*)HalFLife2.m_pEntList->GetClientEntity(pMe->hActiveWeapon()->GetEntryIndex());
        C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)pWeaponEnt;

        IClientEntity *local = HalFLife2.m_pEntList->GetClientEntity( HalFLife2.m_pEngineClient->GetLocalPlayer( ) );

        if(!target || !local)
                return -1.0f;

        float gravity = ConVarRef("sv_gravity").GetFloat();
        float pr_gravity = proj_gravity * 0.5f * gravity;

        QAngle aProjDirection;
        Vector vProjOrigin,vProjDirection,vEntVelocity;
        Vector vEyePosition = HalFLife2.m_pMyPlayer->BaseEnt()->GetAbsOrigin() + *pMe->localdata()->vecViewOffset0();
        EstimateAbsVelocity(target,vEntVelocity);

        float time = 0.5f;
        int iterations = 15; //It needs only ~3 iterations most of the time
        for(int i = 0;i < iterations;i++)
        {
                Vector vPredictedPosition = vTargetPosition + vEntVelocity * time;
                if(!(*pThem->fFlags() & FL_ONGROUND))
                {
                        vPredictedPosition.z -= ent_gravity * 0.5 * gravity * SQUARE(time); //0.5*a*t
                }
                //Aim at vPredictedPosition
                CalcAngle(vEyePosition,vPredictedPosition,aProjDirection);
                AngleVectors(aProjDirection,&vProjDirection);
                //Get new ProjectileSpawn
                //http://www.gamedeception.net/threads/22233-Reversing-projectile-spawn-offset
                //GetProjectileFireSetup(aProjDirection,vProjOrigin);
                GetProjFireSet( *pMe->localdata()->vecViewOffset0(), vProjOrigin, aProjDirection, 2000.0f);

                Vector vProjVelocity = (vProjDirection * ProjectileSpeed);
                float ImpactTime = (vPredictedPosition.x - vProjOrigin.x)  / vProjVelocity.x;
                if(ImpactTime > 0.0f)
                {
                        ImpactTime;			//ghetto ass lag prediction
                        if(abs(ImpactTime-time) < 0.0001)	//Close enough
                                return ImpactTime;
                        time = ImpactTime;
                }
                else //Unsolvable
                        return -1.0f;
        }
        return -1.0f;
}

Vector cAimbot::BallisticPrediction( IClientEntity *target, int iWeaponID )
{
        C_BaseEntity* pEntity = target->GetBaseEntity();
        GenDT_BasePlayer *pThem = (GenDT_BasePlayer*)pEntity;
        GenDT_TFPlayer *TFThem = (GenDT_TFPlayer*)pThem;

        GenDT_BasePlayer *pMe = (GenDT_BasePlayer*)HalFLife2.m_pMyPlayer->BaseEnt();
        IClientEntity* pWeaponEnt = (IClientEntity*)HalFLife2.m_pEntList->GetClientEntity(pMe->hActiveWeapon()->GetEntryIndex());
        C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)pWeaponEnt;

        Vector vecPos;
        QAngle qaAngsUseless;

        if ( iWeaponID == WPN_Huntsman )
                GetHitbox( HITBOX_HEAD, vecPos, pEntity );
        else
                GetWorldSpaceCenter( pEntity,  vecPos );

        //GetWorldSpaceCenter( pEntity,  vecPos );

        float flGravity = HalFLife2.m_pCvar->FindVar( "sv_gravity" )->GetFloat();
        float flEntGravity;

        if ( pEntity->GetGravity() > 0.01f )
                flEntGravity = pEntity->GetGravity();
        else
                flEntGravity = 1.0f;


        float flProjectileSpeed = GetProjectileSpeed( pWeapon );
        float flImpactTime;

        //Trace("%f", flProjectileSpeed);

        Vector vecVelocity; //g_Players.GetVelocity( pEntity ); // *MakePointer<Vector>( pEntity, 0xF0 )
        EstimateAbsVelocity(target,vecVelocity);

        std::string sTheirClass = sGetClass(*TFThem->PlayerClass()->iClass());
        //Trace( "%s: %f, %f, %f", sTheirClass.c_str(), vecVelocity.x, vecVelocity.y, vecVelocity.z);

        //	float time = 0.5f;
        //int iterations = 15; //It needs only ~3 iterations most of the time
        //for(int i = 0;i < iterations;i++)
        //{

        flImpactTime = SolveTime(target,vecPos,flProjectileSpeed,flEntGravity,flGravity);

        //	if ( iWeaponID == WPN_Huntsman )
        //	flImpactTime = BallisticTimeToImpact( vecPos, flProjectileSpeed, pEntity );
        //else
        //	flImpactTime = LinearTimeToImpact( vecPos, flProjectileSpeed, pEntity );

        Vector vecDistance = vecPos - GetEyePosition( HalFLife2.m_pMyPlayer->BaseEnt() );
        vecVelocity *= flImpactTime;

        flImpactTime *= 0.5f;

        float vecTempZ = 0.0f;
        if ( !( *pThem->fFlags() & FL_ONGROUND ) )
                vecTempZ = flEntGravity * flGravity * SQUARE(flImpactTime) + 0.05f;
        //vecTempZ = flEntGravity * flGravity * SQUARE(flImpactTime) + 0.05f;

        Vector vecTempFinal = vecPos + vecVelocity;
        vecTempFinal[2] -= vecTempZ;

        if ( iWeaponID == WPN_Huntsman)
        {
                float flHuntsmanDropOffset = SQUARE(vecDistance.Length()) *  0.0000055363f; // TY C0BRA
                vecTempFinal[2] += flHuntsmanDropOffset; // Note to self: I'm a dumbass
        }

        if ( !vecTempFinal.IsValid() || vecTempFinal.IsZero() )
                return vecPos;

        return vecTempFinal;
}

//===================================================================================
bool CGameTrace::DidHitWorld() const
{
        return m_pEnt == HalFLife2.m_pEntList->GetClientEntity( 0 );
}
//===================================================================================
bool CGameTrace::DidHitNonWorldEntity() const
{
        return m_pEnt != HalFLife2.m_pEntList->GetClientEntity( 0 );
}
//===================================================================================
void C_BaseAnimating::GetBoneTransform( int iBone, matrix3x4_t &pBoneToWorld )
{
        studiohdr_t *pStudioHdr = HalFLife2.m_pModelInfoClient->GetStudiomodel( GetModel( ) );

        if (!pStudioHdr)
                return;
        if (iBone < 0 || iBone >= pStudioHdr->numbones)
                return;

        MatrixCopy(m_BoneAccessor.GetBone(iBone), pBoneToWorld);
}
//===================================================================================
void C_BaseAnimating::GetBonePosition ( int iBone, Vector &origin, QAngle &angles )
{
        studiohdr_t *pStudioHdr = HalFLife2.m_pModelInfoClient->GetStudiomodel( GetModel( ) );

        if (!pStudioHdr)
        {
                return;
        }

        if (iBone < 0 || iBone >= pStudioHdr->numbones)
        {
                return;
        }

        matrix3x4_t bonetoworld;
        GetBoneTransform( iBone, bonetoworld );

        MatrixAngles( bonetoworld, angles, origin );
}
//===================================================================================
