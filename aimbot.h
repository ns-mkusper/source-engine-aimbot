#ifndef __CAIMBOT_H__
#define __CAIMBOT_H__

#include "sdk.h"

class cAimbot
{
public:
	cAimbot();
	//----------------------------------------------
	int		iGetTarget( void );
	void	DropTarget( void );
	void	AimAtTarget ( CUserCmd* pCommand );
	bool	GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* pBaseEnt );
	void	MakeVector( QAngle angle, QAngle& vector );
	void	CalcAngle( Vector &src, Vector &dst, QAngle &angles );
	float	GetFov( QAngle angle, Vector src, Vector dst );
	bool	IsPlayerVisible( Vector viewOrg, Vector origin, CBaseEntity* pPlayerEntity, trace_t* out_tr );
	bool	bIsVisible( const Vector& vecAbsStart, const Vector& vecAbsEnd, C_BaseEntity* pBaseEnt );
	float	flGetDistance( Vector vOrigin );
	float	CalcFOVAngle( QAngle qAngle, Vector vSrc, Vector vDst );
	float	flGetFOV( QAngle angle, Vector vOrigin, Vector vDest );
	float	CalcAngleDiff( Vector &src, Vector &dst, QAngle &angles );
	bool	GetHitboxPosition( int iHitbox, Vector& vecOrigin, CBaseEntity* pEntity );
	float	SolveTime(IClientEntity *target,Vector vTargetPosition,float ProjectileSpeed,float ent_gravity,float proj_gravity);
	float	LinearTimeToImpact( Vector vecDest, float flProjectileSpeed, CBaseEntity* pBaseEnt );
	float	BallisticTimeToImpact( Vector vecDest, float flProjectileSpeed, CBaseEntity* pBaseEnt );
	Vector	BallisticPrediction( IClientEntity *target, int iWeaponID );
	void	StrafeCorrection( CUserCmd* cmd, QAngle& qaView, QAngle qaAim );
	bool	IsVisiblehitscan(Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* pEnt/*, float *push_hitbox*/ );
	bool	GetHitbox ( int hitbox, Vector& vecOrigin, CBaseEntity* pEnt );
	Vector	GetEyePosition( C_BaseEntity *pBaseEntity );
	float	GetProjectileSpeed( C_BaseCombatWeapon *pBaseWeapon );


	std::string sGetClass (int iClass);


	void	TriggerBot(CUserCmd* c);
	int		m_nTarget;
	float	flBestDist;
	Vector vMin,vMax,vecPosition,vPlayer;
	Vector	PredictedTargetPosition;			//see my name
	time_t	past_time;
	SYSTEMTIME 	earlierTime;
	float	fAngleDiff;
	QAngle	qAimAngle;
	bool	bSetViewAngles;
	int		aim_point, hitbox;
	float	hitscan;

	enum hitboxes_t
	{
		HITBOX_HEAD,
		HITBOX_PELVIS,
		HITBOX_LOWERCHEST,
		HITBOX_MIDDLECHEST,
		HITBOX_UPPERCHEST,
		HITBOX_UPPERUPPERCHEST,
		HITBOX_UPPERLEFTARM,
		HITBOX_LOWERLEFTARM,
		HITBOX_LEFTARM,
		HITBOX_UPPERRIGHTARM,
		HITBOX_LOWERRIGHTARM,
		HITBOX_RIGHTARM,
		HITBOX_LEFTHIP,
		HITBOX_LEFTKNEE,
		HITBOX_LEFTFOOT,
		HITBOX_RIGHTHIP,
		HITBOX_RIGHTKNEE,
		HITBOX_RIGHTFOOT,
	};
};


#endif
