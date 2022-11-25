#pragma once
#include <windows.h>
template<typename T> inline T* MakePointerGEN( PVOID thisptr, int offset ) { return reinterpret_cast<T*>( reinterpret_cast<UINT_PTR>( thisptr ) + offset ); }
struct GenDT_BaseEntity
{
	struct CAnimTimeMustBeFirst
	{
		inline float* flAnimTime() { return MakePointerGEN< float >( this, 0x60 ); }
	};
	struct CCollisionProperty
	{
		inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x8 ); }
		inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x14 ); }
		inline int* nSolidType() { return MakePointerGEN< int >( this, 0x29 ); }
		inline int* usSolidFlags() { return MakePointerGEN< int >( this, 0x24 ); }
		inline int* nSurroundType() { return MakePointerGEN< int >( this, 0x28 ); }
		inline int* triggerBloat() { return MakePointerGEN< int >( this, 0x2a ); }
		inline Vector* vecSpecifiedSurroundingMins() { return MakePointerGEN< Vector >( this, 0x2c ); }
		inline Vector* vecSpecifiedSurroundingMaxs() { return MakePointerGEN< Vector >( this, 0x38 ); }
	};
	struct CPredictableId
	{
		inline int* PredictableID() { return MakePointerGEN< int >( this, 0x9c ); }
		inline bool* bIsPlayerSimulated() { return MakePointerGEN< bool >( this, 0x474 ); }
	};
	inline CAnimTimeMustBeFirst* AnimTimeMustBeFirst() { return MakePointerGEN< CAnimTimeMustBeFirst >( this, 0x0 ); }
	inline float* flSimulationTime() { return MakePointerGEN< float >( this, 0x68 ); }
	inline int* ubInterpolationFrame() { return MakePointerGEN< int >( this, 0x74 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x8c ); }
	inline int* fEffects() { return MakePointerGEN< int >( this, 0x78 ); }
	inline int* nRenderMode() { return MakePointerGEN< int >( this, 0x7c ); }
	inline int* nRenderFX() { return MakePointerGEN< int >( this, 0x54 ); }
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* iTeamNum() { return MakePointerGEN< int >( this, 0x98 ); }
	inline int* CollisionGroup() { return MakePointerGEN< int >( this, 0x300 ); }
	inline float* flElasticity() { return MakePointerGEN< float >( this, 0x1fc ); }
	inline float* flShadowCastDistance() { return MakePointerGEN< float >( this, 0x200 ); }
	inline EHANDLE* hOwnerEntity() { return MakePointerGEN< EHANDLE >( this, 0x484 ); }
	inline EHANDLE* hEffectEntity() { return MakePointerGEN< EHANDLE >( this, 0x488 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x174 ); }
	inline int* iParentAttachment() { return MakePointerGEN< int >( this, 0x15e ); }
	inline int* movetype() { return MakePointerGEN< int >( this, 0x0 ); }
	inline int* movecollide() { return MakePointerGEN< int >( this, 0x0 ); }
	inline CCollisionProperty* Collision() { return MakePointerGEN< CCollisionProperty >( this, 0x180 ); }
	inline int* iTextureFrameIndex() { return MakePointerGEN< int >( this, 0x478 ); }
	inline CPredictableId* predictable_id() { return MakePointerGEN< CPredictableId >( this, 0x0 ); }
	inline bool* bSimulatedEveryTick() { return MakePointerGEN< bool >( this, 0x475 ); }
	inline bool* bAnimatedEveryTick() { return MakePointerGEN< bool >( this, 0x476 ); }
	inline bool* bAlternateSorting() { return MakePointerGEN< bool >( this, 0x477 ); }
};
struct GenDT_BaseAnimating : public GenDT_BaseEntity
{
	struct CServerAnimationData
	{
		inline float* flCycle() { return MakePointerGEN< float >( this, 0x778 ); }
	};
	inline int* nSequence() { return MakePointerGEN< int >( this, 0x770 ); }
	inline int* nForceBone() { return MakePointerGEN< int >( this, 0x518 ); }
	inline Vector* vecForce() { return MakePointerGEN< Vector >( this, 0x50c ); }
	inline int* nSkin() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline int* nBody() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline int* nHitboxSet() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline float* flModelWidthScale() { return MakePointerGEN< float >( this, 0x5d8 ); }
	inline float* flPoseParameter() { return MakePointerGEN< float >( this, 0x5dc ); } // Array size = 24
	inline float* flPlaybackRate() { return MakePointerGEN< float >( this, 0x500 ); }
	inline float* flEncodedController() { return MakePointerGEN< float >( this, 0x6f4 ); } // Array size = 4
	inline bool* bClientSideAnimation() { return MakePointerGEN< bool >( this, 0x740 ); }
	inline bool* bClientSideFrameReset() { return MakePointerGEN< bool >( this, 0x548 ); }
	inline int* nNewSequenceParity() { return MakePointerGEN< int >( this, 0x744 ); }
	inline int* nResetEventsParity() { return MakePointerGEN< int >( this, 0x748 ); }
	inline int* nMuzzleFlashParity() { return MakePointerGEN< int >( this, 0x7f0 ); }
	inline EHANDLE* hLightingOrigin() { return MakePointerGEN< EHANDLE >( this, 0x7e8 ); }
	inline EHANDLE* hLightingOriginRelative() { return MakePointerGEN< EHANDLE >( this, 0x7ec ); }
	inline CServerAnimationData* serveranimdata() { return MakePointerGEN< CServerAnimationData >( this, 0x0 ); }
	inline int* fadeMinDist() { return MakePointerGEN< int >( this, 0x580 ); }
	inline int* fadeMaxDist() { return MakePointerGEN< int >( this, 0x584 ); }
	inline float* flFadeScale() { return MakePointerGEN< float >( this, 0x588 ); }
};
struct GenDT_EconEntity : public GenDT_BaseAnimating
{
	struct CAttributeContainer
	{
		struct CScriptCreatedItem
		{
			struct CAttributeList
			{
			}; // Fail count = 1
			inline int* iItemDefinitionIndex() { return MakePointerGEN< int >( this, 0x10 ); }
			inline int* iEntityLevel() { return MakePointerGEN< int >( this, 0x18 ); }
			inline int* iItemIDHigh() { return MakePointerGEN< int >( this, 0x28 ); }
			inline int* iItemIDLow() { return MakePointerGEN< int >( this, 0x2c ); }
			inline int* iAccountID() { return MakePointerGEN< int >( this, 0x30 ); }
			inline int* iEntityQuality() { return MakePointerGEN< int >( this, 0x14 ); }
			inline bool* bInitialized() { return MakePointerGEN< bool >( this, 0x46 ); }
			inline CAttributeList* AttributeList() { return MakePointerGEN< CAttributeList >( this, 0x50 ); }
		};
		inline EHANDLE* hOuter() { return MakePointerGEN< EHANDLE >( this, 0x1c ); }
		inline int* ProviderType() { return MakePointerGEN< int >( this, 0x24 ); }
		inline int* iReapplyProvisionParity() { return MakePointerGEN< int >( this, 0x18 ); }
		inline CScriptCreatedItem* Item() { return MakePointerGEN< CScriptCreatedItem >( this, 0x40 ); }
	};
	inline CAttributeContainer* AttributeManager() { return MakePointerGEN< CAttributeContainer >( this, 0x820 ); }
};
struct GenDT_WearableItem : public GenDT_EconEntity
{
};
struct GenDT_TFWearable : public GenDT_WearableItem
{
	inline bool* bDisguiseWearable() { return MakePointerGEN< bool >( this, 0x920 ); }
};
struct GenDT_TFWearableDemoShield : public GenDT_TFWearable
{
};
struct GenDT_TFBaseRocket : public GenDT_BaseAnimating
{
	inline Vector* vInitialVelocity() { return MakePointerGEN< Vector >( this, 0x810 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline int* iDeflected() { return MakePointerGEN< int >( this, 0x81c ); }
	inline EHANDLE* hLauncher() { return MakePointerGEN< EHANDLE >( this, 0x828 ); }
};
struct GenDT_BaseCombatWeapon : public GenDT_EconEntity
{
	struct CLocalWeaponData
	{
		inline int* iClip1() { return MakePointerGEN< int >( this, 0x95c ); }
		inline int* iClip2() { return MakePointerGEN< int >( this, 0x960 ); }
		inline int* iPrimaryAmmoType() { return MakePointerGEN< int >( this, 0x954 ); }
		inline int* iSecondaryAmmoType() { return MakePointerGEN< int >( this, 0x958 ); }
		inline int* nViewModelIndex() { return MakePointerGEN< int >( this, 0x914 ); }
		inline bool* bFlipViewModel() { return MakePointerGEN< bool >( this, 0x98c ); }
	};
	struct CLocalActiveWeaponData
	{
		inline float* flNextPrimaryAttack() { return MakePointerGEN< float >( this, 0x918 ); }
		inline float* flNextSecondaryAttack() { return MakePointerGEN< float >( this, 0x91c ); }
		inline int* nNextThinkTick() { return MakePointerGEN< int >( this, 0x84 ); }
		inline float* flTimeWeaponIdle() { return MakePointerGEN< float >( this, 0x920 ); }
	};
	inline CLocalWeaponData* LocalWeaponData() { return MakePointerGEN< CLocalWeaponData >( this, 0x0 ); }
	inline CLocalActiveWeaponData* LocalActiveWeaponData() { return MakePointerGEN< CLocalActiveWeaponData >( this, 0x0 ); }
	inline int* iViewModelIndex() { return MakePointerGEN< int >( this, 0x928 ); }
	inline int* iWorldModelIndex() { return MakePointerGEN< int >( this, 0x92c ); }
	inline int* iState() { return MakePointerGEN< int >( this, 0x94c ); }
	inline EHANDLE* hOwner() { return MakePointerGEN< EHANDLE >( this, 0x910 ); }
};
struct GenDT_TFWeaponBase : public GenDT_BaseCombatWeapon
{
	struct CLocalTFWeaponData
	{
		inline float* flLastCritCheckTime() { return MakePointerGEN< float >( this, 0x9ec ); }
		inline float* flReloadPriorNextFire() { return MakePointerGEN< float >( this, 0x9d0 ); }
		inline float* flLastFireTime() { return MakePointerGEN< float >( this, 0xa90 ); }
		inline float* flEffectBarRegenTime() { return MakePointerGEN< float >( this, 0x9c4 ); }
	};
	struct CTFWeaponDataNonLocal
	{
	};
	inline bool* bLowered() { return MakePointerGEN< bool >( this, 0x9dc ); }
	inline int* iReloadMode() { return MakePointerGEN< int >( this, 0x9cc ); }
	inline bool* bResetParity() { return MakePointerGEN< bool >( this, 0xa7c ); }
	inline bool* bReloadedThroughAnimEvent() { return MakePointerGEN< bool >( this, 0xa85 ); }
	inline bool* bDisguiseWeapon() { return MakePointerGEN< bool >( this, 0xa8c ); }
	inline CLocalTFWeaponData* LocalActiveTFWeaponData() { return MakePointerGEN< CLocalTFWeaponData >( this, 0x0 ); }
	inline CTFWeaponDataNonLocal* NonLocalTFWeaponData() { return MakePointerGEN< CTFWeaponDataNonLocal >( this, 0x0 ); }
	inline float* flEnergy() { return MakePointerGEN< float >( this, 0xa88 ); }
};
struct GenDT_TFWeaponBaseMelee : public GenDT_TFWeaponBase
{
};
struct GenDT_TFWeaponBaseGun : public GenDT_TFWeaponBase
{
};
struct GenDT_BaseGrenade : public GenDT_BaseAnimating
{
	inline float* flDamage() { return MakePointerGEN< float >( this, 0x824 ); }
	inline float* DmgRadius() { return MakePointerGEN< float >( this, 0x814 ); }
	inline bool* bIsLive() { return MakePointerGEN< bool >( this, 0x811 ); }
	inline EHANDLE* hThrower() { return MakePointerGEN< EHANDLE >( this, 0x82c ); }
	inline Vector* vecVelocity() { return MakePointerGEN< Vector >( this, 0x108 ); }
	inline int* fFlags() { return MakePointerGEN< int >( this, 0x2fc ); }
};
struct GenDT_TFWeaponBaseGrenadeProj : public GenDT_BaseGrenade
{
	inline Vector* vInitialVelocity() { return MakePointerGEN< Vector >( this, 0x838 ); }
	inline bool* bCritical() { return MakePointerGEN< bool >( this, 0x854 ); }
	inline int* iDeflected() { return MakePointerGEN< int >( this, 0x848 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline EHANDLE* hDeflectOwner() { return MakePointerGEN< EHANDLE >( this, 0x84c ); }
};
struct GenDT_TFWearableRobotArm : public GenDT_TFWearable
{
};
struct GenDT_TFWeaponWrench : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_TFWeaponRobotArm : public GenDT_TFWeaponWrench
{
	inline EHANDLE* hRobotArm() { return MakePointerGEN< EHANDLE >( this, 0xaa8 ); }
};
struct GenDT_WeaponSyringeGun : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_TFWeaponKatana : public GenDT_TFWeaponBaseMelee
{
	inline bool* bIsBloody() { return MakePointerGEN< bool >( this, 0xab0 ); }
};
struct GenDT_TFWeaponSword : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_SniperDot : public GenDT_BaseEntity
{
	inline float* flChargeStartTime() { return MakePointerGEN< float >( this, 0x4f0 ); }
};
struct GenDT_TFSniperRifle : public GenDT_TFWeaponBaseGun
{
	struct CSniperRifleLocalData
	{
		inline float* flChargedDamage() { return MakePointerGEN< float >( this, 0xa98 ); }
	};
	inline CSniperRifleLocalData* SniperRifleLocalData() { return MakePointerGEN< CSniperRifleLocalData >( this, 0x0 ); }
};
struct GenDT_TFSniperRifleDecap : public GenDT_TFSniperRifle
{
};
struct GenDT_TFSMG : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_TFWeaponShovel : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_TFShotgun : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_TFScatterGun : public GenDT_TFShotgun
{
};
struct GenDT_TFSodaPopper : public GenDT_TFScatterGun
{
};
struct GenDT_TFShotgun_Revenge : public GenDT_TFShotgun
{
};
struct GenDT_TFShotgun_Pyro : public GenDT_TFShotgun
{
};
struct GenDT_TFShotgun_HWG : public GenDT_TFShotgun
{
};
struct GenDT_TFShotgun_Soldier : public GenDT_TFShotgun
{
};
struct GenDT_WeaponRocketLauncher : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_Crossbow : public GenDT_WeaponRocketLauncher
{
};
struct GenDT_WeaponRocketLauncher_DirectHit : public GenDT_WeaponRocketLauncher
{
};
struct GenDT_WeaponRevolver : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_WeaponRaygun : public GenDT_WeaponRocketLauncher
{
};
struct GenDT_WeaponDRGPomson : public GenDT_WeaponRaygun
{
};
struct GenDT_WeaponPistol : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_WeaponPistol_Scout : public GenDT_WeaponPistol
{
};
struct GenDT_WeaponPistol_ScoutSecondary : public GenDT_WeaponPistol_Scout
{
};
struct GenDT_WeaponPistol_ScoutPrimary : public GenDT_WeaponPistol_Scout
{
};
struct GenDT_WeaponPipebombLauncher : public GenDT_TFWeaponBaseGun
{
	struct CPipebombLauncherLocalData
	{
		inline int* iPipebombCount() { return MakePointerGEN< int >( this, 0xa9c ); }
		inline float* flChargeBeginTime() { return MakePointerGEN< float >( this, 0xabc ); }
	};
	inline CPipebombLauncherLocalData* PipebombLauncherLocalData() { return MakePointerGEN< CPipebombLauncherLocalData >( this, 0x0 ); }
};
struct GenDT_TFWeaponPDA : public GenDT_TFWeaponBase
{
};
struct GenDT_TFWeaponPDA_Spy : public GenDT_TFWeaponPDA
{
};
struct GenDT_TFWeaponPDA_Engineer_Destroy : public GenDT_TFWeaponPDA
{
};
struct GenDT_TFWeaponPDA_Engineer_Build : public GenDT_TFWeaponPDA
{
};
struct GenDT_ParticleCannon : public GenDT_WeaponRocketLauncher
{
	inline float* flChargeBeginTime() { return MakePointerGEN< float >( this, 0xaa0 ); }
	inline int* iChargeEffect() { return MakePointerGEN< int >( this, 0xaa4 ); }
};
struct GenDT_WeaponMinigun : public GenDT_TFWeaponBaseGun
{
	inline int* iWeaponState() { return MakePointerGEN< int >( this, 0xa98 ); }
	inline bool* bCritShot() { return MakePointerGEN< bool >( this, 0xa9c ); }
};
struct GenDT_WeaponMedigun : public GenDT_TFWeaponBaseGun
{
	struct CLocalTFWeaponMedigunData
	{
		inline float* flChargeLevel() { return MakePointerGEN< float >( this, 0xab4 ); }
	};
	struct CTFWeaponMedigunDataNonLocal
	{
		inline float* flChargeLevel() { return MakePointerGEN< float >( this, 0xab4 ); }
	};
	inline EHANDLE* hHealingTarget() { return MakePointerGEN< EHANDLE >( this, 0xa98 ); }
	inline bool* bHealing() { return MakePointerGEN< bool >( this, 0xa9d ); }
	inline bool* bAttacking() { return MakePointerGEN< bool >( this, 0xa9e ); }
	inline bool* bChargeRelease() { return MakePointerGEN< bool >( this, 0xab1 ); }
	inline bool* bHolstered() { return MakePointerGEN< bool >( this, 0xab0 ); }
	inline CLocalTFWeaponMedigunData* LocalTFWeaponMedigunData() { return MakePointerGEN< CLocalTFWeaponMedigunData >( this, 0x0 ); }
	inline CTFWeaponMedigunDataNonLocal* NonLocalTFWeaponMedigunData() { return MakePointerGEN< CTFWeaponMedigunDataNonLocal >( this, 0x0 ); }
};
struct GenDT_TFMechanicalArm : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_WeaponLunchBox : public GenDT_TFWeaponBase
{
};
struct GenDT_TFLunchBox_Drink : public GenDT_WeaponLunchBox
{
};
struct GenDT_LaserDot : public GenDT_SniperDot
{
};
struct GenDT_TFLaserPointer : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_TFWeaponKnife : public GenDT_TFWeaponBaseMelee
{
	inline bool* bReadyToBackstab() { return MakePointerGEN< bool >( this, 0x17c8 ); }
	inline bool* bKnifeExists() { return MakePointerGEN< bool >( this, 0xab1 ); }
	inline float* flKnifeRegenerateDuration() { return MakePointerGEN< float >( this, 0xab4 ); }
	inline float* flKnifeMeltTimestamp() { return MakePointerGEN< float >( this, 0xab8 ); }
};
struct GenDT_TFProjectile_Pipebomb : public GenDT_TFWeaponBaseGrenadeProj
{
	inline bool* bTouched() { return MakePointerGEN< bool >( this, 0x858 ); }
	inline int* iType() { return MakePointerGEN< int >( this, 0x85c ); }
	inline EHANDLE* hLauncher() { return MakePointerGEN< EHANDLE >( this, 0x844 ); }
	inline bool* bDefensiveBomb() { return MakePointerGEN< bool >( this, 0x870 ); }
};
struct GenDT_TFProjectile_Jar : public GenDT_TFProjectile_Pipebomb
{
};
struct GenDT_TFProjectile_JarMilk : public GenDT_TFProjectile_Jar
{
};
struct GenDT_TFWeaponJar : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_TFWeaponJarMilk : public GenDT_TFWeaponJar
{
};
struct GenDT_TFWeaponInvis : public GenDT_TFWeaponBase
{
};
struct GenDT_WeaponGrenadeLauncher : public GenDT_TFWeaponBaseGun
{
};
struct GenDT_WeaponFlareGun : public GenDT_TFWeaponBaseGun
{
	inline float* flChargeBeginTime() { return MakePointerGEN< float >( this, 0xa98 ); }
};
struct GenDT_WeaponFlareGun_Revenge : public GenDT_WeaponFlareGun
{
	inline int* fLastExtinguishTime() { return MakePointerGEN< int >( this, 0xaa8 ); }
};
struct GenDT_TFFlameRocket : public GenDT_TFBaseRocket
{
	inline bool* bCritical() { return MakePointerGEN< bool >( this, 0x830 ); }
};
struct GenDT_WeaponFlameThrower : public GenDT_TFWeaponBaseGun
{
	inline int* iWeaponState() { return MakePointerGEN< int >( this, 0xa9c ); }
	inline bool* bCritFire() { return MakePointerGEN< bool >( this, 0xaa0 ); }
	inline bool* bHitTarget() { return MakePointerGEN< bool >( this, 0xaa1 ); }
	inline int* iActiveFlames() { return MakePointerGEN< int >( this, 0xaa4 ); }
	inline int* iDamagingFlames() { return MakePointerGEN< int >( this, 0xaa8 ); }
	inline float* flChargeBeginTime() { return MakePointerGEN< float >( this, 0xaac ); }
};
struct GenDT_TFWeaponFists : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_TFWeaponFireAxe : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_WeaponCompoundBow : public GenDT_WeaponPipebombLauncher
{
	inline bool* bArrowAlight() { return MakePointerGEN< bool >( this, 0xacd ); }
};
struct GenDT_TFWeaponClub : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_TFWeaponBuffItem : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_TFWeaponBottle : public GenDT_TFWeaponBaseMelee
{
	inline bool* bBroken() { return MakePointerGEN< bool >( this, 0xaa8 ); }
};
struct GenDT_TFWeaponStickBomb : public GenDT_TFWeaponBottle
{
	inline int* iDetonated() { return MakePointerGEN< int >( this, 0xab0 ); }
};
struct GenDT_TFWeaponBonesaw : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_TFProjectile_StunBall : public GenDT_TFProjectile_Pipebomb
{
};
struct GenDT_TFProjectileBall_Ornament : public GenDT_TFProjectile_StunBall
{
};
struct GenDT_TFWeaponBat : public GenDT_TFWeaponBaseMelee
{
};
struct GenDT_TFWeaponBat_Wood : public GenDT_TFWeaponBat
{
};
struct GenDT_TFWeaponBat_Giftwrap : public GenDT_TFWeaponBat_Wood
{
};
struct GenDT_TFWeaponBat_Fish : public GenDT_TFWeaponBat
{
};
struct GenDT_TFWeaponBuilder : public GenDT_TFWeaponBase
{
	struct CBuilderLocalData
	{
		inline int* iObjectType() { return MakePointerGEN< int >( this, 0xa9c ); }
		inline EHANDLE* hObjectBeingBuilt() { return MakePointerGEN< EHANDLE >( this, 0xab4 ); }
	};
	inline int* iBuildState() { return MakePointerGEN< int >( this, 0xa98 ); }
	inline CBuilderLocalData* BuilderLocalData() { return MakePointerGEN< CBuilderLocalData >( this, 0x0 ); }
	inline int* iObjectMode() { return MakePointerGEN< int >( this, 0xaa0 ); }
};
struct GenDT_TFProjectile_Rocket : public GenDT_TFBaseRocket
{
	inline bool* bCritical() { return MakePointerGEN< bool >( this, 0x830 ); }
};
struct GenDT_TFProjectile_Flare : public GenDT_TFBaseRocket
{
	inline bool* bCritical() { return MakePointerGEN< bool >( this, 0x830 ); }
};
struct GenDT_TFProjectile_EnergyBall : public GenDT_TFBaseRocket
{
	inline bool* bChargedShot() { return MakePointerGEN< bool >( this, 0x834 ); }
	inline Vector* vColor1() { return MakePointerGEN< Vector >( this, 0x838 ); }
	inline Vector* vColor2() { return MakePointerGEN< Vector >( this, 0x844 ); }
};
struct GenDT_TFProjectile_Arrow : public GenDT_TFBaseRocket
{
	inline bool* bArrowAlight() { return MakePointerGEN< bool >( this, 0x839 ); }
	inline bool* bCritical() { return MakePointerGEN< bool >( this, 0x83a ); }
};
struct GenDT_TFProjectile_HealingBolt : public GenDT_TFProjectile_Arrow
{
};
struct GenDT_TeleportVortex : public GenDT_BaseAnimating
{
	inline int* iState() { return MakePointerGEN< int >( this, 0x818 ); }
};
struct GenDT_BaseAnimatingOverlay : public GenDT_BaseAnimating
{
	struct COverlayVars
	{
	}; // Fail count = 1
	inline COverlayVars* overlay_vars() { return MakePointerGEN< COverlayVars >( this, 0x0 ); }
};
struct GenDT_BaseFlex : public GenDT_BaseAnimatingOverlay
{
	inline float* flexWeight() { return MakePointerGEN< float >( this, 0x8b4 ); } // Array size = 96
	inline bool* blinktoggle() { return MakePointerGEN< bool >( this, 0xa60 ); }
	inline Vector* viewtarget() { return MakePointerGEN< Vector >( this, 0x87c ); }
};
struct GenDT_BaseCombatCharacter : public GenDT_BaseFlex
{
	struct CBCCLocalPlayerExclusive
	{
		inline float* flNextAttack() { return MakePointerGEN< float >( this, 0xbd0 ); }
	};
	inline CBCCLocalPlayerExclusive* bcc_localdata() { return MakePointerGEN< CBCCLocalPlayerExclusive >( this, 0x0 ); }
	inline EHANDLE* hActiveWeapon() { return MakePointerGEN< EHANDLE >( this, 0xd18 ); }
	inline EHANDLE* hMyWeapons() { return MakePointerGEN< EHANDLE >( this, 0xc58 ); } // Array size = 48
	inline bool* bGlowEnabled() { return MakePointerGEN< bool >( this, 0xd1c ); }
};
struct GenDT_NextBot : public GenDT_BaseCombatCharacter
{
};
struct GenDT_HeadlessHatman : public GenDT_NextBot
{
};
struct GenDT_EyeballBoss : public GenDT_NextBot
{
	inline Vector* lookAtSpot() { return MakePointerGEN< Vector >( this, 0xd48 ); }
	inline int* attitude() { return MakePointerGEN< int >( this, 0xd54 ); }
};
struct GenDT_BaseViewModel
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x8c ); }
	inline int* nSkin() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline int* nBody() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline int* nSequence() { return MakePointerGEN< int >( this, 0x770 ); }
	inline int* nViewModelIndex() { return MakePointerGEN< int >( this, 0x820 ); }
	inline float* flPlaybackRate() { return MakePointerGEN< float >( this, 0x500 ); }
	inline int* fEffects() { return MakePointerGEN< int >( this, 0x78 ); }
	inline int* nAnimationParity() { return MakePointerGEN< int >( this, 0x830 ); }
	inline EHANDLE* hWeapon() { return MakePointerGEN< EHANDLE >( this, 0x840 ); }
	inline EHANDLE* hOwner() { return MakePointerGEN< EHANDLE >( this, 0x824 ); }
	inline int* nNewSequenceParity() { return MakePointerGEN< int >( this, 0x744 ); }
	inline int* nResetEventsParity() { return MakePointerGEN< int >( this, 0x748 ); }
	inline int* nMuzzleFlashParity() { return MakePointerGEN< int >( this, 0x7f0 ); }
	inline float* flPoseParameter0() { return MakePointerGEN< float >( this, 0x5dc ); }
	inline float* flPoseParameter() { return MakePointerGEN< float >( this, 0x0 ); } // Array size = 24
};
struct GenDT_TFViewModel : public GenDT_BaseViewModel
{
};
struct GenDT_TFPumpkinBomb : public GenDT_BaseAnimating
{
};
struct GenDT_TFBaseProjectile : public GenDT_BaseAnimating
{
	inline Vector* vInitialVelocity() { return MakePointerGEN< Vector >( this, 0x818 ); }
};
struct GenDT_BaseObject : public GenDT_BaseCombatCharacter
{
	inline int* iHealth() { return MakePointerGEN< int >( this, 0xe8c ); }
	inline int* iMaxHealth() { return MakePointerGEN< int >( this, 0xe90 ); }
	inline bool* bHasSapper() { return MakePointerGEN< bool >( this, 0xe84 ); }
	inline int* iObjectType() { return MakePointerGEN< int >( this, 0xe88 ); }
	inline bool* bBuilding() { return MakePointerGEN< bool >( this, 0xe95 ); }
	inline bool* bPlacing() { return MakePointerGEN< bool >( this, 0xe97 ); }
	inline bool* bCarried() { return MakePointerGEN< bool >( this, 0xe9a ); }
	inline bool* bCarryDeploy() { return MakePointerGEN< bool >( this, 0xe9b ); }
	inline bool* bMiniBuilding() { return MakePointerGEN< bool >( this, 0xe9d ); }
	inline float* flPercentageConstructed() { return MakePointerGEN< float >( this, 0xea0 ); }
	inline int* fObjectFlags() { return MakePointerGEN< int >( this, 0xe68 ); }
	inline EHANDLE* hBuiltOnEntity() { return MakePointerGEN< EHANDLE >( this, 0xea4 ); }
	inline bool* bDisabled() { return MakePointerGEN< bool >( this, 0xe98 ); }
	inline EHANDLE* hBuilder() { return MakePointerGEN< EHANDLE >( this, 0xe78 ); }
	inline Vector* vecBuildMaxs() { return MakePointerGEN< Vector >( this, 0xeac ); }
	inline Vector* vecBuildMins() { return MakePointerGEN< Vector >( this, 0xeb8 ); }
	inline int* iDesiredBuildRotations() { return MakePointerGEN< int >( this, 0xec4 ); }
	inline bool* bServerOverridePlacement() { return MakePointerGEN< bool >( this, 0xed0 ); }
	inline int* iUpgradeLevel() { return MakePointerGEN< int >( this, 0xe54 ); }
	inline int* iUpgradeMetal() { return MakePointerGEN< int >( this, 0xe5c ); }
	inline int* iHighestUpgradeLevel() { return MakePointerGEN< int >( this, 0xe60 ); }
	inline int* iObjectMode() { return MakePointerGEN< int >( this, 0xea8 ); }
	inline bool* bDisposableBuilding() { return MakePointerGEN< bool >( this, 0xe9e ); }
};
struct GenDT_BaseObjectUpgrade : public GenDT_BaseObject
{
};
struct GenDT_BreakableProp : public GenDT_BaseAnimating
{
};
struct GenDT_DynamicProp : public GenDT_BreakableProp
{
	inline bool* bUseHitboxesForRenderBox() { return MakePointerGEN< bool >( this, 0x810 ); }
};
struct GenDT_TFItem : public GenDT_DynamicProp
{
};
struct GenDT_BonusRoundLogic
{
	struct CScriptCreatedItem
	{
		struct CAttributeList
		{
		}; // Fail count = 1
		inline int* iItemDefinitionIndex() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* iEntityLevel() { return MakePointerGEN< int >( this, 0x18 ); }
		inline int* iItemIDHigh() { return MakePointerGEN< int >( this, 0x28 ); }
		inline int* iItemIDLow() { return MakePointerGEN< int >( this, 0x2c ); }
		inline int* iAccountID() { return MakePointerGEN< int >( this, 0x30 ); }
		inline int* iEntityQuality() { return MakePointerGEN< int >( this, 0x14 ); }
		inline bool* bInitialized() { return MakePointerGEN< bool >( this, 0x46 ); }
		inline CAttributeList* AttributeList() { return MakePointerGEN< CAttributeList >( this, 0x50 ); }
	};
	inline EHANDLE* hBonusWinner() { return MakePointerGEN< EHANDLE >( this, 0x500 ); }
	inline CScriptCreatedItem* Item() { return MakePointerGEN< CScriptCreatedItem >( this, 0x510 ); }
}; // Fail count = 1
struct GenDT_GameRulesProxy
{
};
struct GenDT_TeamplayRoundBasedRulesProxy : public GenDT_GameRulesProxy
{
	struct CTeamplayRoundBasedRules
	{
		inline int* iRoundState() { return MakePointerGEN< int >( this, 0x28 ); }
		inline bool* bInWaitingForPlayers() { return MakePointerGEN< bool >( this, 0x38 ); }
		inline int* iWinningTeam() { return MakePointerGEN< int >( this, 0x30 ); }
		inline bool* bInOvertime() { return MakePointerGEN< bool >( this, 0x2c ); }
		inline bool* bInSetup() { return MakePointerGEN< bool >( this, 0x2d ); }
		inline bool* bSwitchedTeamsThisRound() { return MakePointerGEN< bool >( this, 0x2e ); }
		inline bool* bAwaitingReadyRestart() { return MakePointerGEN< bool >( this, 0x39 ); }
		inline float* flRestartRoundTime() { return MakePointerGEN< float >( this, 0x3c ); }
		inline float* flMapResetTime() { return MakePointerGEN< float >( this, 0x40 ); }
		inline float* flNextRespawnWave() { return MakePointerGEN< float >( this, 0x44 ); } // Array size = 32
		inline bool* bTeamReady() { return MakePointerGEN< bool >( this, 0xc4 ); } // Array size = 32
		inline bool* bStopWatch() { return MakePointerGEN< bool >( this, 0xe4 ); }
		inline bool* bMultipleTrains() { return MakePointerGEN< bool >( this, 0xe5 ); }
	}; // Fail count = 1
	inline CTeamplayRoundBasedRules* teamplayroundbased_gamerules_data() { return MakePointerGEN< CTeamplayRoundBasedRules >( this, 0x0 ); }
};
struct GenDT_TFGameRulesProxy : public GenDT_TeamplayRoundBasedRulesProxy
{
	struct CTFGameRules
	{
		inline int* nGameType() { return MakePointerGEN< int >( this, 0x198 ); }
		inline int* nStopWatchState() { return MakePointerGEN< int >( this, 0x19c ); }
		inline char** pszTeamGoalStringRed() { return MakePointerGEN< char* >( this, 0x1a0 ); }
		inline char** pszTeamGoalStringBlue() { return MakePointerGEN< char* >( this, 0x2a0 ); }
		inline float* flCapturePointEnableTime() { return MakePointerGEN< float >( this, 0x3a0 ); }
		inline int* nHudType() { return MakePointerGEN< int >( this, 0x3a4 ); }
		inline bool* bIsInTraining() { return MakePointerGEN< bool >( this, 0x3a8 ); }
		inline bool* bAllowTrainingAchievements() { return MakePointerGEN< bool >( this, 0x3a9 ); }
		inline bool* bIsWaitingForTrainingContinue() { return MakePointerGEN< bool >( this, 0x3aa ); }
		inline bool* bIsTrainingHUDVisible() { return MakePointerGEN< bool >( this, 0x3ab ); }
		inline bool* bIsInItemTestingMode() { return MakePointerGEN< bool >( this, 0x3ac ); }
		inline EHANDLE* hBonusLogic() { return MakePointerGEN< EHANDLE >( this, 0x3bc ); }
		inline bool* bPlayingKoth() { return MakePointerGEN< bool >( this, 0x3c0 ); }
		inline bool* bPlayingMedieval() { return MakePointerGEN< bool >( this, 0x3c1 ); }
		inline bool* bPlayingHybrid_CTF_CP() { return MakePointerGEN< bool >( this, 0x3c2 ); }
		inline EHANDLE* hRedKothTimer() { return MakePointerGEN< EHANDLE >( this, 0x3c4 ); }
		inline EHANDLE* hBlueKothTimer() { return MakePointerGEN< EHANDLE >( this, 0x3c8 ); }
		inline int* nMapHolidayType() { return MakePointerGEN< int >( this, 0x3cc ); }
		inline int* itHandle() { return MakePointerGEN< int >( this, 0x51c ); }
		inline EHANDLE* hBirthdayPlayer() { return MakePointerGEN< EHANDLE >( this, 0x520 ); }
		inline int* nBossHealth() { return MakePointerGEN< int >( this, 0x510 ); }
		inline int* nMaxBossHealth() { return MakePointerGEN< int >( this, 0x514 ); }
		inline int* fBossNormalizedTravelDistance() { return MakePointerGEN< int >( this, 0x518 ); }
	};
	inline CTFGameRules* tf_gamerules_data() { return MakePointerGEN< CTFGameRules >( this, 0x0 ); }
};
struct GenDT_BaseTempEntity
{
};
struct GenDT_TETFParticleEffect : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin0() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecOrigin1() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline Vector* vecOrigin2() { return MakePointerGEN< Vector >( this, 0x18 ); }
	inline Vector* vecStart0() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline Vector* vecStart1() { return MakePointerGEN< Vector >( this, 0x20 ); }
	inline Vector* vecStart2() { return MakePointerGEN< Vector >( this, 0x24 ); }
	inline Vector* vecAngles() { return MakePointerGEN< Vector >( this, 0x28 ); }
	inline int* iParticleSystemIndex() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* entindex() { return MakePointerGEN< int >( this, 0x0 ); }
	inline int* iAttachType() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* iAttachmentPointIndex() { return MakePointerGEN< int >( this, 0x40 ); }
	inline bool* bResetParticles() { return MakePointerGEN< bool >( this, 0x44 ); }
	inline bool* bCustomColors() { return MakePointerGEN< bool >( this, 0x45 ); }
	inline Vector* CustomColors_m_vecColor1() { return MakePointerGEN< Vector >( this, 0x48 ); }
	inline Vector* CustomColors_m_vecColor2() { return MakePointerGEN< Vector >( this, 0x54 ); }
	inline bool* bControlPoint1() { return MakePointerGEN< bool >( this, 0x60 ); }
	inline int* ControlPoint1_m_eParticleAttachment() { return MakePointerGEN< int >( this, 0x64 ); }
	inline float* ControlPoint1_m_vecOffset0() { return MakePointerGEN< float >( this, 0x68 ); }
	inline float* ControlPoint1_m_vecOffset1() { return MakePointerGEN< float >( this, 0x6c ); }
	inline float* ControlPoint1_m_vecOffset2() { return MakePointerGEN< float >( this, 0x70 ); }
};
struct GenDT_TETFExplosion : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin0() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecOrigin1() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline Vector* vecOrigin2() { return MakePointerGEN< Vector >( this, 0x18 ); }
	inline Vector* vecNormal() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* iWeaponID() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* entindex() { return MakePointerGEN< int >( this, 0x0 ); }
	inline int* nDefID() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* nSound() { return MakePointerGEN< int >( this, 0x34 ); }
};
struct GenDT_TETFBlood : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin0() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecOrigin1() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline Vector* vecOrigin2() { return MakePointerGEN< Vector >( this, 0x18 ); }
	inline Vector* vecNormal() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* entindex() { return MakePointerGEN< int >( this, 0x0 ); }
};
struct GenDT_CaptureFlagReturnIcon : public GenDT_BaseEntity
{
};
struct GenDT_CaptureFlag : public GenDT_TFItem
{
	inline bool* bDisabled() { return MakePointerGEN< bool >( this, 0x838 ); }
	inline int* nType() { return MakePointerGEN< int >( this, 0x83c ); }
	inline int* nFlagStatus() { return MakePointerGEN< int >( this, 0x840 ); }
	inline float* flResetTime() { return MakePointerGEN< float >( this, 0x844 ); }
	inline float* flNeutralTime() { return MakePointerGEN< float >( this, 0x84c ); }
	inline float* flMaxResetTime() { return MakePointerGEN< float >( this, 0x848 ); }
	inline EHANDLE* hPrevOwner() { return MakePointerGEN< EHANDLE >( this, 0x850 ); }
	inline int* iszModel() { return MakePointerGEN< int >( this, 0x854 ); }
	inline int* nUseTrailEffect() { return MakePointerGEN< int >( this, 0x858 ); }
};
struct GenDT_Team
{
	inline int* iTeamNum() { return MakePointerGEN< int >( this, 0x518 ); }
	inline int* iScore() { return MakePointerGEN< int >( this, 0x504 ); }
	inline int* iRoundsWon() { return MakePointerGEN< int >( this, 0x508 ); }
	inline char** szTeamname() { return MakePointerGEN< char* >( this, 0x4e4 ); }
}; // Fail count = 2
struct GenDT_TFTeam : public GenDT_Team
{
	inline int* nFlagCaptures() { return MakePointerGEN< int >( this, 0x534 ); }
	inline int* iRole() { return MakePointerGEN< int >( this, 0x538 ); }
	inline EHANDLE* hLeader() { return MakePointerGEN< EHANDLE >( this, 0x53c ); }
}; // Fail count = 2
struct GenDT_PlayerResource
{
	inline int* iPing() { return MakePointerGEN< int >( this, 0x55c ); } // Array size = 34
	inline int* iScore() { return MakePointerGEN< int >( this, 0x5e4 ); } // Array size = 34
	inline int* iDeaths() { return MakePointerGEN< int >( this, 0x66c ); } // Array size = 34
	inline bool* bConnected() { return MakePointerGEN< bool >( this, 0x6f4 ); } // Array size = 34
	inline int* iTeam() { return MakePointerGEN< int >( this, 0x718 ); } // Array size = 34
	inline bool* bAlive() { return MakePointerGEN< bool >( this, 0x7a0 ); } // Array size = 34
	inline int* iHealth() { return MakePointerGEN< int >( this, 0x7c4 ); } // Array size = 34
};
struct GenDT_TFPlayerResource : public GenDT_PlayerResource
{
	inline int* iTotalScore() { return MakePointerGEN< int >( this, 0x8d0 ); } // Array size = 34
	inline int* iMaxHealth() { return MakePointerGEN< int >( this, 0x958 ); } // Array size = 34
	inline int* iMaxBuffedHealth() { return MakePointerGEN< int >( this, 0x9e0 ); } // Array size = 34
	inline int* iPlayerClass() { return MakePointerGEN< int >( this, 0xa68 ); } // Array size = 34
	inline bool* bArenaSpectator() { return MakePointerGEN< bool >( this, 0xaf0 ); } // Array size = 34
	inline int* iActiveDominations() { return MakePointerGEN< int >( this, 0xb14 ); } // Array size = 34
	inline float* flNextRespawnTime() { return MakePointerGEN< float >( this, 0xb9c ); } // Array size = 34
	inline int* iChargeLevel() { return MakePointerGEN< int >( this, 0xc24 ); } // Array size = 34
};
struct GenDT_BasePlayer : public GenDT_BaseCombatCharacter
{
	struct CLocalPlayerExclusive
	{
		struct CLocal
		{
			inline char* chAreaBits() { return MakePointerGEN< char >( this, 0x4 ); } // Array size = 32
			inline char* chAreaPortalBits() { return MakePointerGEN< char >( this, 0x24 ); } // Array size = 24
			inline int* iHideHUD() { return MakePointerGEN< int >( this, 0x3c ); }
			inline float* flFOVRate() { return MakePointerGEN< float >( this, 0x40 ); }
			inline bool* bDucked() { return MakePointerGEN< bool >( this, 0x44 ); }
			inline bool* bDucking() { return MakePointerGEN< bool >( this, 0x45 ); }
			inline bool* bInDuckJump() { return MakePointerGEN< bool >( this, 0x46 ); }
			inline float* flDucktime() { return MakePointerGEN< float >( this, 0x48 ); }
			inline float* flDuckJumpTime() { return MakePointerGEN< float >( this, 0x4c ); }
			inline float* flJumpTime() { return MakePointerGEN< float >( this, 0x50 ); }
			inline float* flFallVelocity() { return MakePointerGEN< float >( this, 0x58 ); }
			inline Vector* vecPunchAngle() { return MakePointerGEN< Vector >( this, 0x6c ); }
			inline Vector* vecPunchAngleVel() { return MakePointerGEN< Vector >( this, 0xa4 ); }
			inline bool* bDrawViewmodel() { return MakePointerGEN< bool >( this, 0xdc ); }
			inline bool* bWearingSuit() { return MakePointerGEN< bool >( this, 0xdd ); }
			inline bool* bPoisoned() { return MakePointerGEN< bool >( this, 0xde ); }
			inline float* flStepSize() { return MakePointerGEN< float >( this, 0xe0 ); }
			inline bool* bAllowAutoMovement() { return MakePointerGEN< bool >( this, 0xe4 ); }
			inline int* skybox3d_scale() { return MakePointerGEN< int >( this, 0xec ); }
			inline Vector* skybox3d_origin() { return MakePointerGEN< Vector >( this, 0xf0 ); }
			inline int* skybox3d_area() { return MakePointerGEN< int >( this, 0xfc ); }
			inline int* skybox3d_fog_enable() { return MakePointerGEN< int >( this, 0x140 ); }
			inline int* skybox3d_fog_blend() { return MakePointerGEN< int >( this, 0x141 ); }
			inline Vector* skybox3d_fog_dirPrimary() { return MakePointerGEN< Vector >( this, 0x104 ); }
			inline int* skybox3d_fog_colorPrimary() { return MakePointerGEN< int >( this, 0x110 ); }
			inline int* skybox3d_fog_colorSecondary() { return MakePointerGEN< int >( this, 0x114 ); }
			inline float* skybox3d_fog_start() { return MakePointerGEN< float >( this, 0x120 ); }
			inline float* skybox3d_fog_end() { return MakePointerGEN< float >( this, 0x124 ); }
			inline float* skybox3d_fog_maxdensity() { return MakePointerGEN< float >( this, 0x12c ); }
			inline int* PlayerFog_m_hCtrl() { return MakePointerGEN< int >( this, 0x148 ); }
			inline Vector* audio_localSound0() { return MakePointerGEN< Vector >( this, 0x16c ); }
			inline Vector* audio_localSound1() { return MakePointerGEN< Vector >( this, 0x178 ); }
			inline Vector* audio_localSound2() { return MakePointerGEN< Vector >( this, 0x184 ); }
			inline Vector* audio_localSound3() { return MakePointerGEN< Vector >( this, 0x190 ); }
			inline Vector* audio_localSound4() { return MakePointerGEN< Vector >( this, 0x19c ); }
			inline Vector* audio_localSound5() { return MakePointerGEN< Vector >( this, 0x1a8 ); }
			inline Vector* audio_localSound6() { return MakePointerGEN< Vector >( this, 0x1b4 ); }
			inline Vector* audio_localSound7() { return MakePointerGEN< Vector >( this, 0x1c0 ); }
			inline int* audio_soundscapeIndex() { return MakePointerGEN< int >( this, 0x1cc ); }
			inline int* audio_localBits() { return MakePointerGEN< int >( this, 0x1d0 ); }
			inline int* audio_ent() { return MakePointerGEN< int >( this, 0x1d4 ); }
		};
		inline CLocal* Local() { return MakePointerGEN< CLocal >( this, 0xd74 ); }
		inline Vector* vecViewOffset0() { return MakePointerGEN< Vector >( this, 0xe4 ); }
		inline Vector* vecViewOffset1() { return MakePointerGEN< Vector >( this, 0xe8 ); }
		inline Vector* vecViewOffset2() { return MakePointerGEN< Vector >( this, 0xec ); }
		inline float* flFriction() { return MakePointerGEN< float >( this, 0x210 ); }
		inline int* iAmmo() { return MakePointerGEN< int >( this, 0xbd8 ); } // Array size = 32
		inline int* fOnTarget() { return MakePointerGEN< int >( this, 0xf94 ); }
		inline int* nTickBase() { return MakePointerGEN< int >( this, 0x1094 ); }
		inline int* nNextThinkTick() { return MakePointerGEN< int >( this, 0x84 ); }
		inline EHANDLE* hLastWeapon() { return MakePointerGEN< EHANDLE >( this, 0x10a8 ); }
		inline EHANDLE* hGroundEntity() { return MakePointerGEN< EHANDLE >( this, 0x208 ); }
		inline Vector* vecVelocity0() { return MakePointerGEN< Vector >( this, 0x108 ); }
		inline Vector* vecVelocity1() { return MakePointerGEN< Vector >( this, 0x10c ); }
		inline Vector* vecVelocity2() { return MakePointerGEN< Vector >( this, 0x110 ); }
		inline Vector* vecBaseVelocity() { return MakePointerGEN< Vector >( this, 0x13c ); }
		inline EHANDLE* hConstraintEntity() { return MakePointerGEN< EHANDLE >( this, 0xfcc ); }
		inline Vector* vecConstraintCenter() { return MakePointerGEN< Vector >( this, 0xfd0 ); }
		inline float* flConstraintRadius() { return MakePointerGEN< float >( this, 0xfdc ); }
		inline float* flConstraintWidth() { return MakePointerGEN< float >( this, 0xfe0 ); }
		inline float* flConstraintSpeedFactor() { return MakePointerGEN< float >( this, 0xfe4 ); }
		inline float* flDeathTime() { return MakePointerGEN< float >( this, 0x100c ); }
		inline int* nWaterLevel() { return MakePointerGEN< int >( this, 0x160 ); }
		inline float* flLaggedMovementValue() { return MakePointerGEN< float >( this, 0x11e4 ); }
	};
	struct CAttributeList
	{
	}; // Fail count = 1
	struct CPlayerState
	{
		inline int* deadflag() { return MakePointerGEN< int >( this, 0x4 ); }
	};
	inline CLocalPlayerExclusive* localdata() { return MakePointerGEN< CLocalPlayerExclusive >( this, 0x0 ); }
	inline CAttributeList* AttributeList() { return MakePointerGEN< CAttributeList >( this, 0xf50 ); }
	inline CPlayerState* pl() { return MakePointerGEN< CPlayerState >( this, 0xf6c ); }
	inline int* iFOV() { return MakePointerGEN< int >( this, 0xf80 ); }
	inline int* iFOVStart() { return MakePointerGEN< int >( this, 0xf84 ); }
	inline float* flFOVTime() { return MakePointerGEN< float >( this, 0xf88 ); }
	inline int* iDefaultFOV() { return MakePointerGEN< int >( this, 0xf8c ); }
	inline EHANDLE* hZoomOwner() { return MakePointerGEN< EHANDLE >( this, 0xf90 ); }
	inline EHANDLE* hVehicle() { return MakePointerGEN< EHANDLE >( this, 0x1018 ); }
	inline EHANDLE* hUseEntity() { return MakePointerGEN< EHANDLE >( this, 0x1020 ); }
	inline int* iHealth() { return MakePointerGEN< int >( this, 0x90 ); }
	inline int* lifeState() { return MakePointerGEN< int >( this, 0x8f ); }
	inline int* iBonusProgress() { return MakePointerGEN< int >( this, 0x1028 ); }
	inline int* iBonusChallenge() { return MakePointerGEN< int >( this, 0x102c ); }
	inline float* flMaxspeed() { return MakePointerGEN< float >( this, 0x1024 ); }
	inline int* fFlags() { return MakePointerGEN< int >( this, 0x2fc ); }
	inline int* iObserverMode() { return MakePointerGEN< int >( this, 0xfe8 ); }
	inline EHANDLE* hObserverTarget() { return MakePointerGEN< EHANDLE >( this, 0xfec ); }
	inline EHANDLE* hViewModel0() { return MakePointerGEN< EHANDLE >( this, 0x10c0 ); }
	inline EHANDLE* hViewModel() { return MakePointerGEN< EHANDLE >( this, 0x0 ); } // Array size = 2
	inline char** szLastPlaceName() { return MakePointerGEN< char* >( this, 0x1204 ); }
	inline EHANDLE* hMyWearables() { return MakePointerGEN< EHANDLE >( this, 0x0 ); } // Array size = 9
};
struct GenDT_TFPlayer : public GenDT_BasePlayer
{
	struct CTFPlayerClassShared
	{
		inline int* iClass() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* iszCustomModel() { return MakePointerGEN< int >( this, 0x8 ); }
		inline Vector* vecCustomModelOffset() { return MakePointerGEN< Vector >( this, 0x10c ); }
		inline QAngle* angCustomModelRotation() { return MakePointerGEN< QAngle >( this, 0x118 ); }
		inline bool* bCustomModelRotates() { return MakePointerGEN< bool >( this, 0x124 ); }
		inline bool* bCustomModelRotationSet() { return MakePointerGEN< bool >( this, 0x125 ); }
		inline bool* bCustomModelVisibleToSelf() { return MakePointerGEN< bool >( this, 0x126 ); }
		inline bool* bUseClassAnimations() { return MakePointerGEN< bool >( this, 0x127 ); }
		inline int* iClassModelParity() { return MakePointerGEN< int >( this, 0x128 ); }
	};
	struct CTFPlayerShared
	{
		struct CTFPlayerSharedLocal
		{
			struct CTFPlayerScoringDataExclusive
			{
				inline int* iCaptures() { return MakePointerGEN< int >( this, 0x4 ); }
				inline int* iDefenses() { return MakePointerGEN< int >( this, 0x8 ); }
				inline int* iKills() { return MakePointerGEN< int >( this, 0xc ); }
				inline int* iDeaths() { return MakePointerGEN< int >( this, 0x10 ); }
				inline int* iSuicides() { return MakePointerGEN< int >( this, 0x14 ); }
				inline int* iDominations() { return MakePointerGEN< int >( this, 0x18 ); }
				inline int* iRevenge() { return MakePointerGEN< int >( this, 0x1c ); }
				inline int* iBuildingsBuilt() { return MakePointerGEN< int >( this, 0x20 ); }
				inline int* iBuildingsDestroyed() { return MakePointerGEN< int >( this, 0x24 ); }
				inline int* iHeadshots() { return MakePointerGEN< int >( this, 0x28 ); }
				inline int* iBackstabs() { return MakePointerGEN< int >( this, 0x2c ); }
				inline int* iHealPoints() { return MakePointerGEN< int >( this, 0x30 ); }
				inline int* iInvulns() { return MakePointerGEN< int >( this, 0x34 ); }
				inline int* iTeleports() { return MakePointerGEN< int >( this, 0x38 ); }
				inline int* iResupplyPoints() { return MakePointerGEN< int >( this, 0x44 ); }
				inline int* iKillAssists() { return MakePointerGEN< int >( this, 0x48 ); }
				inline int* iPoints() { return MakePointerGEN< int >( this, 0x50 ); }
				inline int* iBonusPoints() { return MakePointerGEN< int >( this, 0x4c ); }
				inline int* iDamageDone() { return MakePointerGEN< int >( this, 0x3c ); }
				inline int* iCrits() { return MakePointerGEN< int >( this, 0x40 ); }
			};
			inline int* nDesiredDisguiseTeam() { return MakePointerGEN< int >( this, 0x1ac ); }
			inline int* nDesiredDisguiseClass() { return MakePointerGEN< int >( this, 0x1a8 ); }
			inline float* flStealthNoAttackExpire() { return MakePointerGEN< float >( this, 0x2c4 ); }
			inline float* flStealthNextChangeTime() { return MakePointerGEN< float >( this, 0x2c8 ); }
			inline bool* bLastDisguisedAsOwnTeam() { return MakePointerGEN< bool >( this, 0x211 ); }
			inline float* flRageMeter() { return MakePointerGEN< float >( this, 0x290 ); }
			inline bool* bRageDraining() { return MakePointerGEN< bool >( this, 0x294 ); }
			inline float* flNextRageEarnTime() { return MakePointerGEN< float >( this, 0x298 ); }
			inline bool* bInUpgradeZone() { return MakePointerGEN< bool >( this, 0x280 ); }
			inline bool* bPlayerDominated() { return MakePointerGEN< bool >( this, 0x2d0 ); } // Array size = 34
			inline bool* bPlayerDominatingMe() { return MakePointerGEN< bool >( this, 0x2f2 ); } // Array size = 34
			inline CTFPlayerScoringDataExclusive* ScoreData() { return MakePointerGEN< CTFPlayerScoringDataExclusive >( this, 0x4 ); }
			inline CTFPlayerScoringDataExclusive* RoundScoreData() { return MakePointerGEN< CTFPlayerScoringDataExclusive >( this, 0x58 ); }
		};
		struct CTFPlayerConditionListExclusive
		{
			inline int* _condition_bits() { return MakePointerGEN< int >( this, 0x18 ); }
		};
		inline int* nPlayerCond() { return MakePointerGEN< int >( this, 0xb0 ); }
		inline bool* bJumping() { return MakePointerGEN< bool >( this, 0x2b4 ); }
		inline int* nNumHealers() { return MakePointerGEN< int >( this, 0x208 ); }
		inline int* iCritMult() { return MakePointerGEN< int >( this, 0x2cc ); }
		inline int* iAirDash() { return MakePointerGEN< int >( this, 0x2b8 ); }
		inline int* nAirDucked() { return MakePointerGEN< int >( this, 0x2bc ); }
		inline float* flDuckTimer() { return MakePointerGEN< float >( this, 0x2c0 ); }
		inline int* nPlayerState() { return MakePointerGEN< int >( this, 0xac ); }
		inline int* iDesiredPlayerClass() { return MakePointerGEN< int >( this, 0x274 ); }
		inline float* flMovementStunTime() { return MakePointerGEN< float >( this, 0x314 ); }
		inline int* iMovementStunAmount() { return MakePointerGEN< int >( this, 0x318 ); }
		inline int* iMovementStunParity() { return MakePointerGEN< int >( this, 0x31c ); }
		inline EHANDLE* hStunner() { return MakePointerGEN< EHANDLE >( this, 0x320 ); }
		inline int* iStunFlags() { return MakePointerGEN< int >( this, 0x324 ); }
		inline int* nArenaNumChanges() { return MakePointerGEN< int >( this, 0x334 ); }
		inline bool* bArenaFirstBloodBoost() { return MakePointerGEN< bool >( this, 0x3ab ); }
		inline int* iWeaponKnockbackID() { return MakePointerGEN< int >( this, 0x338 ); }
		inline bool* bLoadoutUnavailable() { return MakePointerGEN< bool >( this, 0x33c ); }
		inline int* iItemFindBonus() { return MakePointerGEN< int >( this, 0x340 ); }
		inline bool* bShieldEquipped() { return MakePointerGEN< bool >( this, 0x344 ); }
		inline int* iNextMeleeCrit() { return MakePointerGEN< int >( this, 0x354 ); }
		inline int* iDecapitations() { return MakePointerGEN< int >( this, 0x348 ); }
		inline int* iRevengeCrits() { return MakePointerGEN< int >( this, 0x350 ); }
		inline int* iDisguiseBody() { return MakePointerGEN< int >( this, 0x360 ); }
		inline EHANDLE* hCarriedObject() { return MakePointerGEN< EHANDLE >( this, 0x328 ); }
		inline bool* bCarryingObject() { return MakePointerGEN< bool >( this, 0x32c ); }
		inline float* flNextNoiseMakerTime() { return MakePointerGEN< float >( this, 0x364 ); }
		inline int* iKillCountSinceLastDeploy() { return MakePointerGEN< int >( this, 0x368 ); }
		inline float* flFirstPrimaryAttack() { return MakePointerGEN< float >( this, 0x36c ); }
		inline float* flEnergyDrinkMeter() { return MakePointerGEN< float >( this, 0x284 ); }
		inline float* flHypeMeter() { return MakePointerGEN< float >( this, 0x288 ); }
		inline float* flChargeMeter() { return MakePointerGEN< float >( this, 0x28c ); }
		inline float* flInvisChangeCompleteTime() { return MakePointerGEN< float >( this, 0x1d0 ); }
		inline int* nDisguiseTeam() { return MakePointerGEN< int >( this, 0x190 ); }
		inline int* nDisguiseClass() { return MakePointerGEN< int >( this, 0x194 ); }
		inline int* nMaskClass() { return MakePointerGEN< int >( this, 0x198 ); }
		inline int* iDisguiseTargetIndex() { return MakePointerGEN< int >( this, 0x1a0 ); }
		inline int* iDisguiseHealth() { return MakePointerGEN< int >( this, 0x1a4 ); }
		inline bool* bFeignDeathReady() { return MakePointerGEN< bool >( this, 0x270 ); }
		inline EHANDLE* hDisguiseWeapon() { return MakePointerGEN< EHANDLE >( this, 0x1b0 ); }
		inline int* nTeamTeleporterUsed() { return MakePointerGEN< int >( this, 0x1b4 ); }
		inline float* flCloakMeter() { return MakePointerGEN< float >( this, 0x27c ); }
		inline CTFPlayerSharedLocal* tfsharedlocaldata() { return MakePointerGEN< CTFPlayerSharedLocal >( this, 0x0 ); }
		inline CTFPlayerConditionListExclusive* ConditionList() { return MakePointerGEN< CTFPlayerConditionListExclusive >( this, 0x170 ); }
		inline int* iTauntIndex() { return MakePointerGEN< int >( this, 0x24c ); }
		inline int* iTauntConcept() { return MakePointerGEN< int >( this, 0x250 ); }
		inline int* nPlayerCondEx() { return MakePointerGEN< int >( this, 0xb4 ); }
	};
	struct CTFLocalPlayerExclusive
	{
		inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
		inline Vector* vecOrigin2() { return MakePointerGEN< Vector >( this, 0x2ec ); }
		inline QAngle* angEyeAngles0() { return MakePointerGEN< QAngle >( this, 0x1984 ); }
		inline bool* bIsCoaching() { return MakePointerGEN< bool >( this, 0x19e4 ); }
		inline EHANDLE* hCoach() { return MakePointerGEN< EHANDLE >( this, 0x19c4 ); }
		inline EHANDLE* hStudent() { return MakePointerGEN< EHANDLE >( this, 0x19c8 ); }
	}; // Fail count = 2
	struct CTFNonLocalPlayerExclusive
	{
		inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
		inline Vector* vecOrigin2() { return MakePointerGEN< Vector >( this, 0x2ec ); }
		inline QAngle* angEyeAngles0() { return MakePointerGEN< QAngle >( this, 0x1984 ); }
		inline QAngle* angEyeAngles1() { return MakePointerGEN< QAngle >( this, 0x1988 ); }
	};
	struct CAttributeManager
	{
		inline EHANDLE* hOuter() { return MakePointerGEN< EHANDLE >( this, 0x1c ); }
		inline int* ProviderType() { return MakePointerGEN< int >( this, 0x24 ); }
		inline int* iReapplyProvisionParity() { return MakePointerGEN< int >( this, 0x18 ); }
	};
	inline bool* bSaveMeParity() { return MakePointerGEN< bool >( this, 0x19e2 ); }
	inline bool* bIsABot() { return MakePointerGEN< bool >( this, 0x19e1 ); }
	inline int* nWaterLevel() { return MakePointerGEN< int >( this, 0x160 ); }
	inline EHANDLE* hRagdoll() { return MakePointerGEN< EHANDLE >( this, 0x13ec ); }
	inline CTFPlayerClassShared* PlayerClass() { return MakePointerGEN< CTFPlayerClassShared >( this, 0x145c ); }
	inline CTFPlayerShared* Shared() { return MakePointerGEN< CTFPlayerShared >( this, 0x15d4 ); }
	inline EHANDLE* hItem() { return MakePointerGEN< EHANDLE >( this, 0x19bc ); }
	inline CTFLocalPlayerExclusive* tflocaldata() { return MakePointerGEN< CTFLocalPlayerExclusive >( this, 0x0 ); }
	inline CTFNonLocalPlayerExclusive* tfnonlocaldata() { return MakePointerGEN< CTFNonLocalPlayerExclusive >( this, 0x0 ); }
	inline bool* bIsReadyToHighFive() { return MakePointerGEN< bool >( this, 0x19e5 ); }
	inline EHANDLE* hHighFivePartner() { return MakePointerGEN< EHANDLE >( this, 0x19e8 ); }
	inline bool* bForceTauntCam() { return MakePointerGEN< bool >( this, 0x19ec ); }
	inline float* flTauntYaw() { return MakePointerGEN< float >( this, 0x19f0 ); }
	inline bool* bInPowerPlay() { return MakePointerGEN< bool >( this, 0x19d9 ); }
	inline int* iSpawnCounter() { return MakePointerGEN< int >( this, 0x19dc ); }
	inline bool* bArenaSpectator() { return MakePointerGEN< bool >( this, 0x19e0 ); }
	inline CAttributeManager* AttributeManager() { return MakePointerGEN< CAttributeManager >( this, 0x13a8 ); }
	inline bool* bGlowEnabled() { return MakePointerGEN< bool >( this, 0xd1c ); }
};
struct GenDT_TFRagdoll
{
	inline Vector* vecRagdollOrigin() { return MakePointerGEN< Vector >( this, 0xbdc ); }
	inline int* iPlayerIndex() { return MakePointerGEN< int >( this, 0xbe8 ); }
	inline Vector* vecForce() { return MakePointerGEN< Vector >( this, 0x50c ); }
	inline Vector* vecRagdollVelocity() { return MakePointerGEN< Vector >( this, 0xbd0 ); }
	inline int* nForceBone() { return MakePointerGEN< int >( this, 0x518 ); }
	inline bool* bGib() { return MakePointerGEN< bool >( this, 0xbf1 ); }
	inline bool* bBurning() { return MakePointerGEN< bool >( this, 0xbf2 ); }
	inline bool* bElectrocuted() { return MakePointerGEN< bool >( this, 0xbf3 ); }
	inline bool* bFeignDeath() { return MakePointerGEN< bool >( this, 0xbf6 ); }
	inline bool* bWasDisguised() { return MakePointerGEN< bool >( this, 0xbf7 ); }
	inline bool* bOnGround() { return MakePointerGEN< bool >( this, 0xc22 ); }
	inline bool* bCloaked() { return MakePointerGEN< bool >( this, 0xbf8 ); }
	inline bool* bBecomeAsh() { return MakePointerGEN< bool >( this, 0xbf9 ); }
	inline int* iDamageCustom() { return MakePointerGEN< int >( this, 0xbfc ); }
	inline int* iTeam() { return MakePointerGEN< int >( this, 0xc14 ); }
	inline int* iClass() { return MakePointerGEN< int >( this, 0xc18 ); }
	inline EHANDLE* hRagWearables() { return MakePointerGEN< EHANDLE >( this, 0x0 ); } // Array size = 9
	inline bool* bGoldRagdoll() { return MakePointerGEN< bool >( this, 0xc00 ); }
	inline bool* bIceRagdoll() { return MakePointerGEN< bool >( this, 0xc01 ); }
};
struct GenDT_TEPlayerAnimEvent
{
	inline int* iPlayerIndex() { return MakePointerGEN< int >( this, 0x10 ); }
	inline int* iEvent() { return MakePointerGEN< int >( this, 0x14 ); }
	inline int* nData() { return MakePointerGEN< int >( this, 0x18 ); }
};
struct GenDT_BaseTeamObjectiveResource
{
	inline int* iTimerToShowInHUD() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* iStopWatchTimer() { return MakePointerGEN< int >( this, 0x4d4 ); }
	inline int* iNumControlPoints() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline bool* bPlayingMiniRounds() { return MakePointerGEN< bool >( this, 0x4e0 ); }
	inline bool* bControlPointsReset() { return MakePointerGEN< bool >( this, 0x4e1 ); }
	inline int* iUpdateCapHudParity() { return MakePointerGEN< int >( this, 0x4e4 ); }
	inline Vector* vCPPositions0() { return MakePointerGEN< Vector >( this, 0x4ec ); }
	inline bool* bCPIsVisible() { return MakePointerGEN< bool >( this, 0x54c ); } // Array size = 8
	inline float* flLazyCapPerc() { return MakePointerGEN< float >( this, 0x554 ); } // Array size = 8
	inline int* iTeamIcons() { return MakePointerGEN< int >( this, 0x594 ); } // Array size = 64
	inline int* iTeamOverlays() { return MakePointerGEN< int >( this, 0x694 ); } // Array size = 64
	inline int* iTeamReqCappers() { return MakePointerGEN< int >( this, 0x794 ); } // Array size = 64
	inline float* flTeamCapTime() { return MakePointerGEN< float >( this, 0x894 ); } // Array size = 64
	inline int* iPreviousPoints() { return MakePointerGEN< int >( this, 0x994 ); } // Array size = 192
	inline bool* bTeamCanCap() { return MakePointerGEN< bool >( this, 0xc94 ); } // Array size = 64
	inline int* iTeamBaseIcons() { return MakePointerGEN< int >( this, 0xcd4 ); } // Array size = 32
	inline int* iBaseControlPoints() { return MakePointerGEN< int >( this, 0xd54 ); } // Array size = 32
	inline bool* bInMiniRound() { return MakePointerGEN< bool >( this, 0xdd4 ); } // Array size = 8
	inline int* iWarnOnCap() { return MakePointerGEN< int >( this, 0xddc ); } // Array size = 8
	inline int* iszWarnSound0() { return MakePointerGEN< int >( this, 0xdfc ); }
	inline int* iszWarnSound() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 8
	inline float* flPathDistance() { return MakePointerGEN< float >( this, 0x15f4 ); } // Array size = 8
	inline int* iCPGroup() { return MakePointerGEN< int >( this, 0x1614 ); } // Array size = 8
	inline bool* bCPLocked() { return MakePointerGEN< bool >( this, 0x1634 ); } // Array size = 8
	inline int* nNumNodeHillData() { return MakePointerGEN< int >( this, 0x18ac ); } // Array size = 4
	inline float* flNodeHillData() { return MakePointerGEN< float >( this, 0x18bc ); } // Array size = 40
	inline bool* bTrackAlarm() { return MakePointerGEN< bool >( this, 0x1970 ); } // Array size = 4
	inline float* flUnlockTimes() { return MakePointerGEN< float >( this, 0x163c ); } // Array size = 8
	inline bool* bHillIsDownhill() { return MakePointerGEN< bool >( this, 0x1974 ); } // Array size = 20
	inline float* flCPTimerTimes() { return MakePointerGEN< float >( this, 0x167c ); } // Array size = 8
	inline int* iNumTeamMembers() { return MakePointerGEN< int >( this, 0x16bc ); } // Array size = 64
	inline int* iCappingTeam() { return MakePointerGEN< int >( this, 0x17bc ); } // Array size = 8
	inline int* iTeamInZone() { return MakePointerGEN< int >( this, 0x17dc ); } // Array size = 8
	inline bool* bBlocked() { return MakePointerGEN< bool >( this, 0x17fc ); } // Array size = 8
	inline int* iOwner() { return MakePointerGEN< int >( this, 0x1804 ); } // Array size = 8
	inline char** pszCapLayoutInHUD() { return MakePointerGEN< char* >( this, 0x188c ); }
}; // Fail count = 1
struct GenDT_TFObjectiveResource : public GenDT_BaseTeamObjectiveResource
{
};
struct GenDT_TEFireBullets
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline Vector* vecAngles0() { return MakePointerGEN< Vector >( this, 0x20 ); }
	inline Vector* vecAngles1() { return MakePointerGEN< Vector >( this, 0x24 ); }
	inline int* iWeaponID() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* iMode() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* iSeed() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* iPlayer() { return MakePointerGEN< int >( this, 0x10 ); }
	inline float* flSpread() { return MakePointerGEN< float >( this, 0x38 ); }
	inline bool* bCritical() { return MakePointerGEN< bool >( this, 0x3c ); }
};
struct GenDT_TFBuffBanner : public GenDT_BaseAnimating
{
};
struct GenDT_AmmoPack : public GenDT_BaseAnimating
{
	inline Vector* vecInitialVelocity() { return MakePointerGEN< Vector >( this, 0x814 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x2f4 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x2f8 ); }
};
struct GenDT_ObjectTeleporter : public GenDT_BaseObject
{
	inline int* iState() { return MakePointerGEN< int >( this, 0xee8 ); }
	inline float* flRechargeTime() { return MakePointerGEN< float >( this, 0xef0 ); }
	inline float* flCurrentRechargeDuration() { return MakePointerGEN< float >( this, 0xef4 ); }
	inline int* iTimesUsed() { return MakePointerGEN< int >( this, 0xef8 ); }
	inline float* flYawToExit() { return MakePointerGEN< float >( this, 0xefc ); }
	inline bool* bMatchBuilding() { return MakePointerGEN< bool >( this, 0xf00 ); }
};
struct GenDT_ObjectSentrygun : public GenDT_BaseObject
{
	struct CSentrygunLocalData
	{
		inline int* iKills() { return MakePointerGEN< int >( this, 0xef8 ); }
		inline int* iAssists() { return MakePointerGEN< int >( this, 0xefc ); }
	};
	inline int* iAmmoShells() { return MakePointerGEN< int >( this, 0xeec ); }
	inline int* iAmmoRockets() { return MakePointerGEN< int >( this, 0xef4 ); }
	inline int* iState() { return MakePointerGEN< int >( this, 0xee8 ); }
	inline bool* bPlayerControlled() { return MakePointerGEN< bool >( this, 0xf0c ); }
	inline bool* bShielded() { return MakePointerGEN< bool >( this, 0xf0e ); }
	inline EHANDLE* hEnemy() { return MakePointerGEN< EHANDLE >( this, 0xf48 ); }
	inline EHANDLE* hAutoAimTarget() { return MakePointerGEN< EHANDLE >( this, 0xf4c ); }
	inline CSentrygunLocalData* SentrygunLocalData() { return MakePointerGEN< CSentrygunLocalData >( this, 0x0 ); }
};
struct GenDT_TFProjectile_SentryRocket : public GenDT_TFProjectile_Rocket
{
};
struct GenDT_ObjectSapper : public GenDT_BaseObjectUpgrade
{
};
struct GenDT_ObjectDispenser : public GenDT_BaseObject
{
	inline int* iAmmoMetal() { return MakePointerGEN< int >( this, 0xf00 ); }
}; // Fail count = 2
struct GenDT_ObjectCartDispenser : public GenDT_ObjectDispenser
{
};
struct GenDT_MonsterResource
{
	inline int* iBossHealthPercentageByte() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* iBossStunPercentageByte() { return MakePointerGEN< int >( this, 0x4d4 ); }
	inline int* iSkillShotCompleteCount() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline int* fSkillShotComboEndTime() { return MakePointerGEN< int >( this, 0x4dc ); }
};
struct GenDT_FuncRespawnRoomVisualizer : public GenDT_BaseEntity
{
};
struct GenDT_FuncRespawnRoom : public GenDT_BaseEntity
{
};
struct GenDT_CaptureZone : public GenDT_BaseEntity
{
	inline bool* bDisabled() { return MakePointerGEN< bool >( this, 0x4d0 ); }
};
struct GenDT_TestTraceline
{
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x2f4 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x2f8 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x174 ); }
};
struct GenDT_TEWorldDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x1c ); }
};
struct GenDT_TESpriteSpray : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* fNoise() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TESprite : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nBrightness() { return MakePointerGEN< int >( this, 0x24 ); }
};
struct GenDT_TEParticleSystem : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin0() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecOrigin1() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline Vector* vecOrigin2() { return MakePointerGEN< Vector >( this, 0x18 ); }
};
struct GenDT_TESparks : public GenDT_TEParticleSystem
{
	inline int* nMagnitude() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* nTrailLength() { return MakePointerGEN< int >( this, 0x20 ); }
	inline Vector* vecDir() { return MakePointerGEN< Vector >( this, 0x24 ); }
};
struct GenDT_TESmoke : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nFrameRate() { return MakePointerGEN< int >( this, 0x24 ); }
};
struct GenDT_TEShowLine : public GenDT_TEParticleSystem
{
	inline Vector* vecEnd() { return MakePointerGEN< Vector >( this, 0x1c ); }
};
struct GenDT_TEProjectedDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x1c ); }
	inline float* flDistance() { return MakePointerGEN< float >( this, 0x28 ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TEPlayerDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nPlayer() { return MakePointerGEN< int >( this, 0x10 ); }
};
struct GenDT_TEPhysicsProp : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x1c ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x20 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x24 ); }
	inline Vector* vecVelocity() { return MakePointerGEN< Vector >( this, 0x28 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* nSkin() { return MakePointerGEN< int >( this, 0x38 ); }
	inline int* nEffects() { return MakePointerGEN< int >( this, 0x40 ); }
};
struct GenDT_TEMuzzleFlash : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecAngles() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline float* flScale() { return MakePointerGEN< float >( this, 0x28 ); }
	inline int* nType() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TELargeFunnel : public GenDT_TEParticleSystem
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* nReversed() { return MakePointerGEN< int >( this, 0x20 ); }
};
struct GenDT_TEKillPlayerAttachments : public GenDT_BaseTempEntity
{
	inline int* nPlayer() { return MakePointerGEN< int >( this, 0x10 ); }
};
struct GenDT_TEImpact : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecNormal() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* iType() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* ucFlags() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TEGlowSprite : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* fLife() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* nBrightness() { return MakePointerGEN< int >( this, 0x28 ); }
};
struct GenDT_TEShatterSurface : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecAngles() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline Vector* vecForce() { return MakePointerGEN< Vector >( this, 0x28 ); }
	inline Vector* vecForcePos() { return MakePointerGEN< Vector >( this, 0x34 ); }
	inline float* flWidth() { return MakePointerGEN< float >( this, 0x40 ); }
	inline float* flHeight() { return MakePointerGEN< float >( this, 0x44 ); }
	inline float* flShardSize() { return MakePointerGEN< float >( this, 0x48 ); }
	inline int* nSurfaceType() { return MakePointerGEN< int >( this, 0x50 ); }
	inline uchar* uchFrontColor0() { return MakePointerGEN< uchar >( this, 0x54 ); }
	inline uchar* uchFrontColor1() { return MakePointerGEN< uchar >( this, 0x55 ); }
	inline uchar* uchFrontColor2() { return MakePointerGEN< uchar >( this, 0x56 ); }
	inline uchar* uchBackColor0() { return MakePointerGEN< uchar >( this, 0x57 ); }
	inline uchar* uchBackColor1() { return MakePointerGEN< uchar >( this, 0x58 ); }
	inline uchar* uchBackColor2() { return MakePointerGEN< uchar >( this, 0x59 ); }
};
struct GenDT_TEFootprintDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x38 ); }
	inline char* chMaterialType() { return MakePointerGEN< char >( this, 0x3c ); }
};
struct GenDT_TEFizz : public GenDT_BaseTempEntity
{
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x14 ); }
	inline int* nDensity() { return MakePointerGEN< int >( this, 0x18 ); }
	inline int* nCurrent() { return MakePointerGEN< int >( this, 0x1c ); }
};
struct GenDT_TEExplosion : public GenDT_TEParticleSystem
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nFrameRate() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x28 ); }
	inline Vector* vecNormal() { return MakePointerGEN< Vector >( this, 0x2c ); }
	inline char* chMaterialType() { return MakePointerGEN< char >( this, 0x38 ); }
	inline int* nRadius() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* nMagnitude() { return MakePointerGEN< int >( this, 0x40 ); }
};
struct GenDT_TEEnergySplash
{
	inline Vector* vecPos() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDir() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline bool* bExplosive() { return MakePointerGEN< bool >( this, 0x28 ); }
};
struct GenDT_TEEffectDispatch : public GenDT_BaseTempEntity
{
	struct CEffectData
	{
		inline float* vOrigin0() { return MakePointerGEN< float >( this, 0x0 ); }
		inline float* vOrigin1() { return MakePointerGEN< float >( this, 0x4 ); }
		inline float* vOrigin2() { return MakePointerGEN< float >( this, 0x8 ); }
		inline float* vStart0() { return MakePointerGEN< float >( this, 0xc ); }
		inline float* vStart1() { return MakePointerGEN< float >( this, 0x10 ); }
		inline float* vStart2() { return MakePointerGEN< float >( this, 0x14 ); }
		inline Vector* vAngles() { return MakePointerGEN< Vector >( this, 0x24 ); }
		inline Vector* vNormal() { return MakePointerGEN< Vector >( this, 0x18 ); }
		inline int* fFlags() { return MakePointerGEN< int >( this, 0x30 ); }
		inline float* flMagnitude() { return MakePointerGEN< float >( this, 0x3c ); }
		inline float* flScale() { return MakePointerGEN< float >( this, 0x38 ); }
		inline int* nAttachmentIndex() { return MakePointerGEN< int >( this, 0x44 ); }
		inline int* nSurfaceProp() { return MakePointerGEN< int >( this, 0x48 ); }
		inline int* iEffectName() { return MakePointerGEN< int >( this, 0x88 ); }
		inline int* nMaterial() { return MakePointerGEN< int >( this, 0x4c ); }
		inline int* nDamageType() { return MakePointerGEN< int >( this, 0x50 ); }
		inline int* nHitBox() { return MakePointerGEN< int >( this, 0x54 ); }
		inline int* entindex() { return MakePointerGEN< int >( this, 0x0 ); }
		inline int* nColor() { return MakePointerGEN< int >( this, 0x58 ); }
		inline float* flRadius() { return MakePointerGEN< float >( this, 0x40 ); }
		inline bool* bCustomColors() { return MakePointerGEN< bool >( this, 0x59 ); }
		inline Vector* CustomColors_m_vecColor1() { return MakePointerGEN< Vector >( this, 0x5c ); }
		inline Vector* CustomColors_m_vecColor2() { return MakePointerGEN< Vector >( this, 0x68 ); }
		inline bool* bControlPoint1() { return MakePointerGEN< bool >( this, 0x74 ); }
		inline int* ControlPoint1_m_eParticleAttachment() { return MakePointerGEN< int >( this, 0x78 ); }
		inline float* ControlPoint1_m_vecOffset0() { return MakePointerGEN< float >( this, 0x7c ); }
		inline float* ControlPoint1_m_vecOffset1() { return MakePointerGEN< float >( this, 0x80 ); }
		inline float* ControlPoint1_m_vecOffset2() { return MakePointerGEN< float >( this, 0x84 ); }
	};
	inline CEffectData* EffectData() { return MakePointerGEN< CEffectData >( this, 0x10 ); }
};
struct GenDT_TEDynamicLight : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* exponent() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* fRadius() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fTime() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* fDecay() { return MakePointerGEN< int >( this, 0x34 ); }
};
struct GenDT_TEDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecStart() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* nHitbox() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x30 ); }
};
struct GenDT_TEClientProjectile : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecVelocity() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* nLifeTime() { return MakePointerGEN< int >( this, 0x2c ); }
	inline EHANDLE* hOwner() { return MakePointerGEN< EHANDLE >( this, 0x30 ); }
};
struct GenDT_TEBubbleTrail : public GenDT_BaseTempEntity
{
	inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x2c ); }
	inline float* flWaterZ() { return MakePointerGEN< float >( this, 0x28 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* fSpeed() { return MakePointerGEN< int >( this, 0x34 ); }
};
struct GenDT_TEBubbles : public GenDT_BaseTempEntity
{
	inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* fHeight() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* fSpeed() { return MakePointerGEN< int >( this, 0x34 ); }
};
struct GenDT_TEBSPDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x20 ); }
};
struct GenDT_TEBreakModel : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x1c ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x20 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x24 ); }
	inline Vector* vecSize() { return MakePointerGEN< Vector >( this, 0x28 ); }
	inline Vector* vecVelocity() { return MakePointerGEN< Vector >( this, 0x34 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x44 ); }
	inline int* nRandomization() { return MakePointerGEN< int >( this, 0x40 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x48 ); }
	inline int* fTime() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBloodStream : public GenDT_TEParticleSystem
{
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* a() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nAmount() { return MakePointerGEN< int >( this, 0x38 ); }
};
struct GenDT_TEBloodSprite
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* a() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nSprayModel() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* nDropModel() { return MakePointerGEN< int >( this, 0x38 ); }
	inline int* nSize() { return MakePointerGEN< int >( this, 0x40 ); }
};
struct GenDT_TEBeamSpline
{
	inline int* nPoints() { return MakePointerGEN< int >( this, 0xd0 ); }
	inline Vector* vecPoints0() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecPoints() { return MakePointerGEN< Vector >( this, 0x0 ); } // Array size = 16
};
struct GenDT_BaseBeam
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x10 ); }
	inline int* nHaloIndex() { return MakePointerGEN< int >( this, 0x14 ); }
	inline int* nStartFrame() { return MakePointerGEN< int >( this, 0x18 ); }
	inline int* nFrameRate() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fLife() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* fWidth() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* fEndWidth() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* nFadeLength() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* fAmplitude() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x44 ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x38 ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* a() { return MakePointerGEN< int >( this, 0x40 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x48 ); }
};
struct GenDT_TEBeamRingPoint : public GenDT_BaseBeam
{
	inline Vector* vecCenter() { return MakePointerGEN< Vector >( this, 0x4c ); }
	inline float* flStartRadius() { return MakePointerGEN< float >( this, 0x58 ); }
	inline float* flEndRadius() { return MakePointerGEN< float >( this, 0x5c ); }
};
struct GenDT_TEBeamRing : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBeamPoints : public GenDT_BaseBeam
{
	inline Vector* vecStartPoint() { return MakePointerGEN< Vector >( this, 0x4c ); }
	inline Vector* vecEndPoint() { return MakePointerGEN< Vector >( this, 0x58 ); }
};
struct GenDT_TEBeamLaser : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBeamFollow : public GenDT_BaseBeam
{
	inline int* iEntIndex() { return MakePointerGEN< int >( this, 0x4c ); }
};
struct GenDT_TEBeamEnts : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBeamEntPoint : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
	inline Vector* vecStartPoint() { return MakePointerGEN< Vector >( this, 0x54 ); }
	inline Vector* vecEndPoint() { return MakePointerGEN< Vector >( this, 0x60 ); }
};
struct GenDT_TEMetalSparks
{
	inline Vector* vecPos() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDir() { return MakePointerGEN< Vector >( this, 0x1c ); }
};
struct GenDT_TEArmorRicochet : public GenDT_TEMetalSparks
{
};
struct GenDT_BaseParticleEntity : public GenDT_BaseEntity
{
};
struct GenDT_SteamJet : public GenDT_BaseParticleEntity
{
	inline float* SpreadSpeed() { return MakePointerGEN< float >( this, 0x5bc ); }
	inline float* Speed() { return MakePointerGEN< float >( this, 0x5c0 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x5c4 ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x5c8 ); }
	inline float* Rate() { return MakePointerGEN< float >( this, 0x5cc ); }
	inline float* JetLength() { return MakePointerGEN< float >( this, 0x5d0 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x5d4 ); }
	inline bool* bFaceLeft() { return MakePointerGEN< bool >( this, 0x5dc ); }
	inline int* nType() { return MakePointerGEN< int >( this, 0x5d8 ); }
	inline int* spawnflags() { return MakePointerGEN< int >( this, 0x5e0 ); }
	inline float* flRollSpeed() { return MakePointerGEN< float >( this, 0x5e4 ); }
};
struct GenDT_SmokeStack : public GenDT_BaseParticleEntity
{
	inline float* SpreadSpeed() { return MakePointerGEN< float >( this, 0x60c ); }
	inline float* Speed() { return MakePointerGEN< float >( this, 0x610 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x614 ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x618 ); }
	inline float* Rate() { return MakePointerGEN< float >( this, 0x61c ); }
	inline float* JetLength() { return MakePointerGEN< float >( this, 0x620 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x624 ); }
	inline float* flBaseSpread() { return MakePointerGEN< float >( this, 0x628 ); }
	inline float* flTwist() { return MakePointerGEN< float >( this, 0x67c ); }
	inline float* flRollSpeed() { return MakePointerGEN< float >( this, 0x6b8 ); }
	inline int* iMaterialModel() { return MakePointerGEN< int >( this, 0x680 ); }
	inline Vector* AmbientLight_m_vPos() { return MakePointerGEN< Vector >( this, 0x62c ); }
	inline Vector* AmbientLight_m_vColor() { return MakePointerGEN< Vector >( this, 0x638 ); }
	inline float* AmbientLight_m_flIntensity() { return MakePointerGEN< float >( this, 0x644 ); }
	inline Vector* DirLight_m_vPos() { return MakePointerGEN< Vector >( this, 0x648 ); }
	inline Vector* DirLight_m_vColor() { return MakePointerGEN< Vector >( this, 0x654 ); }
	inline float* DirLight_m_flIntensity() { return MakePointerGEN< float >( this, 0x660 ); }
	inline Vector* vWind() { return MakePointerGEN< Vector >( this, 0x670 ); }
};
struct GenDT_DustTrail : public GenDT_BaseParticleEntity
{
	inline float* SpawnRate() { return MakePointerGEN< float >( this, 0x5bc ); }
	inline Vector* Color() { return MakePointerGEN< Vector >( this, 0x5c0 ); }
	inline float* ParticleLifetime() { return MakePointerGEN< float >( this, 0x5d0 ); }
	inline float* StopEmitTime() { return MakePointerGEN< float >( this, 0x5d8 ); }
	inline float* MinSpeed() { return MakePointerGEN< float >( this, 0x5dc ); }
	inline float* MaxSpeed() { return MakePointerGEN< float >( this, 0x5e0 ); }
	inline float* MinDirectedSpeed() { return MakePointerGEN< float >( this, 0x5e4 ); }
	inline float* MaxDirectedSpeed() { return MakePointerGEN< float >( this, 0x5e8 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x5ec ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x5f0 ); }
	inline float* SpawnRadius() { return MakePointerGEN< float >( this, 0x5f4 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x604 ); }
	inline float* Opacity() { return MakePointerGEN< float >( this, 0x5cc ); }
};
struct GenDT_FireTrail : public GenDT_BaseParticleEntity
{
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x5bc ); }
	inline float* flLifetime() { return MakePointerGEN< float >( this, 0x5c0 ); }
};
struct GenDT_SporeTrail : public GenDT_BaseParticleEntity
{
	inline float* flSpawnRate() { return MakePointerGEN< float >( this, 0x5c4 ); }
	inline Vector* vecEndColor() { return MakePointerGEN< Vector >( this, 0x5b8 ); }
	inline float* flParticleLifetime() { return MakePointerGEN< float >( this, 0x5c8 ); }
	inline float* flStartSize() { return MakePointerGEN< float >( this, 0x5cc ); }
	inline float* flEndSize() { return MakePointerGEN< float >( this, 0x5d0 ); }
	inline float* flSpawnRadius() { return MakePointerGEN< float >( this, 0x5d4 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x5e4 ); }
};
struct GenDT_SporeExplosion : public GenDT_BaseParticleEntity
{
	inline float* flSpawnRate() { return MakePointerGEN< float >( this, 0x5bc ); }
	inline float* flParticleLifetime() { return MakePointerGEN< float >( this, 0x5c0 ); }
	inline float* flStartSize() { return MakePointerGEN< float >( this, 0x5c4 ); }
	inline float* flEndSize() { return MakePointerGEN< float >( this, 0x5c8 ); }
	inline float* flSpawnRadius() { return MakePointerGEN< float >( this, 0x5cc ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x5d4 ); }
	inline bool* bDontRemove() { return MakePointerGEN< bool >( this, 0x5d5 ); }
};
struct GenDT_RocketTrail : public GenDT_BaseParticleEntity
{
	inline float* SpawnRate() { return MakePointerGEN< float >( this, 0x5bc ); }
	inline Vector* StartColor() { return MakePointerGEN< Vector >( this, 0x5c0 ); }
	inline Vector* EndColor() { return MakePointerGEN< Vector >( this, 0x5cc ); }
	inline float* ParticleLifetime() { return MakePointerGEN< float >( this, 0x5dc ); }
	inline float* StopEmitTime() { return MakePointerGEN< float >( this, 0x5e0 ); }
	inline float* MinSpeed() { return MakePointerGEN< float >( this, 0x5e4 ); }
	inline float* MaxSpeed() { return MakePointerGEN< float >( this, 0x5e8 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x5ec ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x5f0 ); }
	inline float* SpawnRadius() { return MakePointerGEN< float >( this, 0x5f4 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x604 ); }
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x608 ); }
	inline float* Opacity() { return MakePointerGEN< float >( this, 0x5d8 ); }
	inline bool* bDamaged() { return MakePointerGEN< bool >( this, 0x605 ); }
	inline float* flFlareScale() { return MakePointerGEN< float >( this, 0x618 ); }
};
struct GenDT_SmokeTrail : public GenDT_BaseParticleEntity
{
	inline float* SpawnRate() { return MakePointerGEN< float >( this, 0x5bc ); }
	inline Vector* StartColor() { return MakePointerGEN< Vector >( this, 0x5c0 ); }
	inline Vector* EndColor() { return MakePointerGEN< Vector >( this, 0x5cc ); }
	inline float* ParticleLifetime() { return MakePointerGEN< float >( this, 0x5dc ); }
	inline float* StopEmitTime() { return MakePointerGEN< float >( this, 0x5e0 ); }
	inline float* MinSpeed() { return MakePointerGEN< float >( this, 0x5e4 ); }
	inline float* MaxSpeed() { return MakePointerGEN< float >( this, 0x5e8 ); }
	inline float* MinDirectedSpeed() { return MakePointerGEN< float >( this, 0x5ec ); }
	inline float* MaxDirectedSpeed() { return MakePointerGEN< float >( this, 0x5f0 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x5f4 ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x5f8 ); }
	inline float* SpawnRadius() { return MakePointerGEN< float >( this, 0x5fc ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x60c ); }
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x610 ); }
	inline float* Opacity() { return MakePointerGEN< float >( this, 0x5d8 ); }
};
struct GenDT_PropVehicleDriveable : public GenDT_BaseAnimating
{
	inline EHANDLE* hPlayer() { return MakePointerGEN< EHANDLE >( this, 0x814 ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x818 ); }
	inline int* nRPM() { return MakePointerGEN< int >( this, 0x81c ); }
	inline float* flThrottle() { return MakePointerGEN< float >( this, 0x820 ); }
	inline int* nBoostTimeLeft() { return MakePointerGEN< int >( this, 0x824 ); }
	inline int* nHasBoost() { return MakePointerGEN< int >( this, 0x828 ); }
	inline int* nScannerDisabledWeapons() { return MakePointerGEN< int >( this, 0x82c ); }
	inline int* nScannerDisabledVehicle() { return MakePointerGEN< int >( this, 0x830 ); }
	inline bool* bEnterAnimOn() { return MakePointerGEN< bool >( this, 0x850 ); }
	inline bool* bExitAnimOn() { return MakePointerGEN< bool >( this, 0x851 ); }
	inline bool* bUnableToFire() { return MakePointerGEN< bool >( this, 0x89d ); }
	inline Vector* vecEyeExitEndpoint() { return MakePointerGEN< Vector >( this, 0x890 ); }
	inline bool* bHasGun() { return MakePointerGEN< bool >( this, 0x89c ); }
	inline Vector* vecGunCrosshair() { return MakePointerGEN< Vector >( this, 0x858 ); }
};
struct GenDT_ParticleSmokeGrenade : public GenDT_BaseParticleEntity
{
	inline float* flSpawnTime() { return MakePointerGEN< float >( this, 0x5cc ); }
	inline float* FadeStartTime() { return MakePointerGEN< float >( this, 0x5d0 ); }
	inline float* FadeEndTime() { return MakePointerGEN< float >( this, 0x5d4 ); }
	inline int* CurrentStage() { return MakePointerGEN< int >( this, 0x5bc ); }
};
struct GenDT_ParticleFire
{
	inline Vector* vOrigin() { return MakePointerGEN< Vector >( this, 0x5c4 ); }
	inline Vector* vDirection() { return MakePointerGEN< Vector >( this, 0x5d0 ); }
};
struct GenDT_MovieExplosion : public GenDT_BaseParticleEntity
{
};
struct GenDT_TEGaussExplosion : public GenDT_TEParticleSystem
{
	inline int* nType() { return MakePointerGEN< int >( this, 0x1c ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x20 ); }
};
struct GenDT_QuadraticBeam : public GenDT_BaseEntity
{
	inline Vector* targetPosition() { return MakePointerGEN< Vector >( this, 0x4d0 ); }
	inline Vector* controlPosition() { return MakePointerGEN< Vector >( this, 0x4dc ); }
	inline float* scrollRate() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flWidth() { return MakePointerGEN< float >( this, 0x4ec ); }
};
struct GenDT_Embers : public GenDT_BaseEntity
{
	inline int* nDensity() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* nLifetime() { return MakePointerGEN< int >( this, 0x4d4 ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x4dc ); }
};
struct GenDT_EnvWind : public GenDT_BaseEntity
{
	struct CEnvWindShared
	{
		inline int* iMinWind() { return MakePointerGEN< int >( this, 0xc ); }
		inline int* iMaxWind() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* iMinGust() { return MakePointerGEN< int >( this, 0x14 ); }
		inline int* iMaxGust() { return MakePointerGEN< int >( this, 0x18 ); }
		inline float* flMinGustDelay() { return MakePointerGEN< float >( this, 0x1c ); }
		inline float* flMaxGustDelay() { return MakePointerGEN< float >( this, 0x20 ); }
		inline int* iGustDirChange() { return MakePointerGEN< int >( this, 0x28 ); }
		inline int* iWindSeed() { return MakePointerGEN< int >( this, 0x8 ); }
		inline int* iInitialWindDir() { return MakePointerGEN< int >( this, 0x38 ); }
		inline float* flInitialWindSpeed() { return MakePointerGEN< float >( this, 0x3c ); }
		inline float* flStartTime() { return MakePointerGEN< float >( this, 0x4 ); }
		inline float* flGustDuration() { return MakePointerGEN< float >( this, 0x24 ); }
	};
	inline CEnvWindShared* EnvWindShared() { return MakePointerGEN< CEnvWindShared >( this, 0x4d0 ); }
};
struct GenDT_Precipitation : public GenDT_BaseEntity
{
	inline int* nPrecipType() { return MakePointerGEN< int >( this, 0x4f8 ); }
};
struct GenDT_WeaponIFMBase : public GenDT_TFWeaponBase
{
};
struct GenDT_WeaponIFMBaseCamera : public GenDT_WeaponIFMBase
{
	inline float* flRenderAspectRatio() { return MakePointerGEN< float >( this, 0xacc ); }
	inline float* flRenderFOV() { return MakePointerGEN< float >( this, 0xad0 ); }
	inline float* flRenderArmLength() { return MakePointerGEN< float >( this, 0xad4 ); }
	inline Vector* vecRenderPosition() { return MakePointerGEN< Vector >( this, 0xad8 ); }
	inline QAngle* angRenderAngles() { return MakePointerGEN< QAngle >( this, 0xae4 ); }
};
struct GenDT_WeaponIFMSteadyCam : public GenDT_WeaponIFMBaseCamera
{
};
struct GenDT_TFWearableItem : public GenDT_WearableItem
{
};
struct GenDT_BaseAttributableItem : public GenDT_EconEntity
{
	inline CAttributeContainer* AttributeManager() { return MakePointerGEN< CAttributeContainer >( this, 0x820 ); }
};
struct GenDT_HandleTest : public GenDT_BaseEntity
{
	inline int* Handle() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline bool* bSendHandle() { return MakePointerGEN< bool >( this, 0x4d4 ); }
};
struct GenDT_TeamRoundTimer
{
	inline bool* bTimerPaused() { return MakePointerGEN< bool >( this, 0x4d0 ); }
	inline float* flTimeRemaining() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline float* flTimerEndTime() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline int* nTimerMaxLength() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline bool* bIsDisabled() { return MakePointerGEN< bool >( this, 0x4dc ); }
	inline bool* bShowInHUD() { return MakePointerGEN< bool >( this, 0x4dd ); }
	inline int* nTimerLength() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline int* nTimerInitialLength() { return MakePointerGEN< int >( this, 0x4e4 ); }
	inline bool* bAutoCountdown() { return MakePointerGEN< bool >( this, 0x4ec ); }
	inline int* nSetupTimeLength() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* nState() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline bool* bStartPaused() { return MakePointerGEN< bool >( this, 0x4f8 ); }
	inline bool* bShowTimeRemaining() { return MakePointerGEN< bool >( this, 0x4f9 ); }
	inline bool* bInCaptureWatchState() { return MakePointerGEN< bool >( this, 0x4fa ); }
	inline bool* bStopWatchTimer() { return MakePointerGEN< bool >( this, 0x500 ); }
	inline float* flTotalTime() { return MakePointerGEN< float >( this, 0x4fc ); }
};
struct GenDT_Sprite : public GenDT_BaseEntity
{
	inline EHANDLE* hAttachedToEntity() { return MakePointerGEN< EHANDLE >( this, 0x4e0 ); }
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x4e4 ); }
	inline float* flScaleTime() { return MakePointerGEN< float >( this, 0x500 ); }
	inline float* flSpriteScale() { return MakePointerGEN< float >( this, 0x4fc ); }
	inline float* flSpriteFramerate() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flGlowProxySize() { return MakePointerGEN< float >( this, 0x508 ); }
	inline float* flHDRColorScale() { return MakePointerGEN< float >( this, 0x50c ); }
	inline float* flFrame() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline float* flBrightnessTime() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline int* nBrightness() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline bool* bWorldSpaceScale() { return MakePointerGEN< bool >( this, 0x504 ); }
};
struct GenDT_SpriteTrail : public GenDT_Sprite
{
	inline float* flLifeTime() { return MakePointerGEN< float >( this, 0xb64 ); }
	inline float* flStartWidth() { return MakePointerGEN< float >( this, 0xb68 ); }
	inline float* flEndWidth() { return MakePointerGEN< float >( this, 0xb6c ); }
	inline float* flStartWidthVariance() { return MakePointerGEN< float >( this, 0xb70 ); }
	inline float* flTextureRes() { return MakePointerGEN< float >( this, 0xb74 ); }
	inline float* flMinFadeLength() { return MakePointerGEN< float >( this, 0xb78 ); }
	inline Vector* vecSkyboxOrigin() { return MakePointerGEN< Vector >( this, 0xb7c ); }
	inline float* flSkyboxScale() { return MakePointerGEN< float >( this, 0xb88 ); }
};
struct GenDT_SpriteOriented : public GenDT_Sprite
{
};
struct GenDT_Ragdoll : public GenDT_BaseAnimating
{
	inline Vector* ragAngles0() { return MakePointerGEN< Vector >( this, 0x930 ); }
	inline Vector* ragPos0() { return MakePointerGEN< Vector >( this, 0x810 ); }
	inline EHANDLE* hUnragdoll() { return MakePointerGEN< EHANDLE >( this, 0xb0c ); }
	inline float* flBlendWeight() { return MakePointerGEN< float >( this, 0xb10 ); }
	inline int* nOverlaySequence() { return MakePointerGEN< int >( this, 0xb18 ); }
}; // Fail count = 2
struct GenDT_Ragdoll_Attached : public GenDT_Ragdoll
{
	inline bool* boneIndexAttached() { return MakePointerGEN< bool >( this, 0xb48 ); }
	inline int* ragdollAttachedObjectIndex() { return MakePointerGEN< int >( this, 0xb44 ); }
	inline Vector* attachmentPointBoneSpace() { return MakePointerGEN< Vector >( this, 0xb20 ); }
	inline Vector* attachmentPointRagdollSpace() { return MakePointerGEN< Vector >( this, 0xb38 ); }
};
struct GenDT_PoseController : public GenDT_BaseEntity
{
	inline EHANDLE* hProps() { return MakePointerGEN< EHANDLE >( this, 0x4d0 ); } // Array size = 4
	inline char* chPoseIndex() { return MakePointerGEN< char >( this, 0x4e0 ); } // Array size = 4
	inline bool* bPoseValueParity() { return MakePointerGEN< bool >( this, 0x4e4 ); }
	inline int* fPoseValue() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* fInterpolationTime() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline bool* bInterpolationWrap() { return MakePointerGEN< bool >( this, 0x4f0 ); }
	inline int* fCycleFrequency() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* nFModType() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* fFModTimeOffset() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline int* fFModRate() { return MakePointerGEN< int >( this, 0x500 ); }
	inline int* fFModAmplitude() { return MakePointerGEN< int >( this, 0x504 ); }
};
struct GenDT_InfoLadderDismount : public GenDT_BaseEntity
{
};
struct GenDT_FuncLadder : public GenDT_BaseEntity
{
	inline Vector* vecPlayerMountPositionTop() { return MakePointerGEN< Vector >( this, 0x4f0 ); }
	inline Vector* vecPlayerMountPositionBottom() { return MakePointerGEN< Vector >( this, 0x4fc ); }
	inline Vector* vecLadderDir() { return MakePointerGEN< Vector >( this, 0x4d0 ); }
	inline bool* bFakeLadder() { return MakePointerGEN< bool >( this, 0x509 ); }
};
struct GenDT_DetailController
{
	inline float* flFadeStartDist() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* flFadeEndDist() { return MakePointerGEN< float >( this, 0x4d4 ); }
};
struct GenDT_World : public GenDT_BaseEntity
{
	inline float* flWaveHeight() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline Vector* WorldMins() { return MakePointerGEN< Vector >( this, 0x4d4 ); }
	inline Vector* WorldMaxs() { return MakePointerGEN< Vector >( this, 0x4e0 ); }
	inline bool* bStartDark() { return MakePointerGEN< bool >( this, 0x4ec ); }
	inline float* flMaxOccludeeArea() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline float* flMinOccluderArea() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline float* flMaxPropScreenSpaceWidth() { return MakePointerGEN< float >( this, 0x4fc ); }
	inline float* flMinPropScreenSpaceWidth() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline int* iszDetailSpriteMaterial() { return MakePointerGEN< int >( this, 0x501 ); }
	inline bool* bColdWorld() { return MakePointerGEN< bool >( this, 0x500 ); }
};
struct GenDT_WaterLODControl : public GenDT_BaseEntity
{
	inline float* flCheapWaterStartDistance() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* flCheapWaterEndDistance() { return MakePointerGEN< float >( this, 0x4d4 ); }
};
struct GenDT_WaterBullet : public GenDT_BaseAnimating
{
};
struct GenDT_VoteController : public GenDT_BaseEntity
{
	inline int* iActiveIssueIndex() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline int* iOnlyTeamToVote() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline int* nVoteOptionCount() { return MakePointerGEN< int >( this, 0x4e0 ); } // Array size = 5
	inline int* nPotentialVotes() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline bool* bIsYesNoVote() { return MakePointerGEN< bool >( this, 0x4fe ); }
};
struct GenDT_VGuiScreen : public GenDT_BaseEntity
{
	inline float* flWidth() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline float* flHeight() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline int* fScreenFlags() { return MakePointerGEN< int >( this, 0x504 ); }
	inline int* nPanelName() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline int* nAttachmentIndex() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline int* nOverlayMaterial() { return MakePointerGEN< int >( this, 0x500 ); }
	inline EHANDLE* hPlayerOwner() { return MakePointerGEN< EHANDLE >( this, 0x560 ); }
};
struct GenDT_PropJeep : public GenDT_PropVehicleDriveable
{
	inline bool* bHeadlightIsOn() { return MakePointerGEN< bool >( this, 0x95c ); }
};
struct GenDT_PropVehicleChoreoGeneric : public GenDT_DynamicProp
{
	inline EHANDLE* hPlayer() { return MakePointerGEN< EHANDLE >( this, 0x834 ); }
	inline bool* bEnterAnimOn() { return MakePointerGEN< bool >( this, 0x83c ); }
	inline bool* bExitAnimOn() { return MakePointerGEN< bool >( this, 0x83d ); }
	inline Vector* vecEyeExitEndpoint() { return MakePointerGEN< Vector >( this, 0x840 ); }
	inline int* vehicleView_bClampEyeAngles() { return MakePointerGEN< int >( this, 0x8cc ); }
	inline float* vehicleView_flPitchCurveZero() { return MakePointerGEN< float >( this, 0x8d0 ); }
	inline float* vehicleView_flPitchCurveLinear() { return MakePointerGEN< float >( this, 0x8d4 ); }
	inline float* vehicleView_flRollCurveZero() { return MakePointerGEN< float >( this, 0x8d8 ); }
	inline float* vehicleView_flRollCurveLinear() { return MakePointerGEN< float >( this, 0x8dc ); }
	inline float* vehicleView_flFOV() { return MakePointerGEN< float >( this, 0x8e0 ); }
	inline float* vehicleView_flYawMin() { return MakePointerGEN< float >( this, 0x8e4 ); }
	inline float* vehicleView_flYawMax() { return MakePointerGEN< float >( this, 0x8e8 ); }
	inline float* vehicleView_flPitchMin() { return MakePointerGEN< float >( this, 0x8ec ); }
	inline float* vehicleView_flPitchMax() { return MakePointerGEN< float >( this, 0x8f0 ); }
};
struct GenDT_ProxyToggle : public GenDT_BaseEntity
{
	struct CProxyToggle_ProxiedData
	{
		inline int* WithProxy() { return MakePointerGEN< int >( this, 0x4d0 ); }
	};
	inline CProxyToggle_ProxiedData* blah() { return MakePointerGEN< CProxyToggle_ProxiedData >( this, 0x0 ); }
};
struct GenDT_Tesla : public GenDT_BaseEntity
{
	inline int* iszSpriteName() { return MakePointerGEN< int >( this, 0x538 ); }
}; // Fail count = 1
struct GenDT_TeamTrainWatcher : public GenDT_BaseEntity
{
	inline float* flTotalProgress() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline int* iTrainSpeedLevel() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline float* flRecedeTime() { return MakePointerGEN< float >( this, 0x4e0 ); }
	inline int* nNumCappers() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline EHANDLE* hGlowEnt() { return MakePointerGEN< EHANDLE >( this, 0x4f0 ); }
};
struct GenDT_Sun
{
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* clrOverlay() { return MakePointerGEN< int >( this, 0x620 ); }
	inline Vector* vDirection() { return MakePointerGEN< Vector >( this, 0x62c ); }
	inline bool* bOn() { return MakePointerGEN< bool >( this, 0x638 ); }
	inline int* nSize() { return MakePointerGEN< int >( this, 0x624 ); }
	inline int* nOverlaySize() { return MakePointerGEN< int >( this, 0x628 ); }
	inline int* nMaterial() { return MakePointerGEN< int >( this, 0x63c ); }
	inline int* nOverlayMaterial() { return MakePointerGEN< int >( this, 0x640 ); }
	inline float* HDRColorScale() { return MakePointerGEN< float >( this, 0x0 ); }
};
struct GenDT_ParticlePerformanceMonitor : public GenDT_BaseEntity
{
	inline bool* bMeasurePerf() { return MakePointerGEN< bool >( this, 0x4d1 ); }
	inline bool* bDisplayPerf() { return MakePointerGEN< bool >( this, 0x4d0 ); }
};
struct GenDT_SpotlightEnd : public GenDT_BaseEntity
{
	inline float* flLightScale() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* Radius() { return MakePointerGEN< float >( this, 0x4d4 ); }
};
struct GenDT_SlideshowDisplay : public GenDT_BaseEntity
{
	inline bool* bEnabled() { return MakePointerGEN< bool >( this, 0x4d0 ); }
	inline char** szDisplayText() { return MakePointerGEN< char* >( this, 0x4d1 ); }
	inline char** szSlideshowDirectory() { return MakePointerGEN< char* >( this, 0x551 ); }
	inline char* chCurrentSlideLists() { return MakePointerGEN< char >( this, 0x5e8 ); } // Array size = 16
	inline int* fMinSlideTime() { return MakePointerGEN< int >( this, 0x600 ); }
	inline int* fMaxSlideTime() { return MakePointerGEN< int >( this, 0x604 ); }
	inline int* iCycleType() { return MakePointerGEN< int >( this, 0x60c ); }
	inline bool* bNoListRepeats() { return MakePointerGEN< bool >( this, 0x610 ); }
};
struct GenDT_ShadowControl : public GenDT_BaseEntity
{
	inline Vector* shadowDirection() { return MakePointerGEN< Vector >( this, 0x4d0 ); }
	inline int* shadowColor() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline float* flShadowMaxDist() { return MakePointerGEN< float >( this, 0x4e0 ); }
	inline bool* bDisableShadows() { return MakePointerGEN< bool >( this, 0x4e4 ); }
};
struct GenDT_SceneEntity : public GenDT_BaseEntity
{
	inline int* nSceneStringIndex() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline bool* bIsPlayingBack() { return MakePointerGEN< bool >( this, 0x4d4 ); }
	inline bool* bPaused() { return MakePointerGEN< bool >( this, 0x4d5 ); }
	inline bool* bMultiplayer() { return MakePointerGEN< bool >( this, 0x4d6 ); }
	inline float* flForceClientTime() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline EHANDLE* hActorList() { return MakePointerGEN< EHANDLE >( this, 0x0 ); } // Array size = 17
};
struct GenDT_RopeKeyframe
{
	inline int* iRopeMaterialModelIndex() { return MakePointerGEN< int >( this, 0x50c ); }
	inline EHANDLE* hStartPoint() { return MakePointerGEN< EHANDLE >( this, 0x79c ); }
	inline EHANDLE* hEndPoint() { return MakePointerGEN< EHANDLE >( this, 0x7a0 ); }
	inline int* iStartAttachment() { return MakePointerGEN< int >( this, 0x7a4 ); }
	inline int* iEndAttachment() { return MakePointerGEN< int >( this, 0x7a6 ); }
	inline int* fLockedPoints() { return MakePointerGEN< int >( this, 0x7b8 ); }
	inline int* Slack() { return MakePointerGEN< int >( this, 0x7b0 ); }
	inline int* RopeLength() { return MakePointerGEN< int >( this, 0x7ac ); }
	inline int* RopeFlags() { return MakePointerGEN< int >( this, 0x508 ); }
	inline float* TextureScale() { return MakePointerGEN< float >( this, 0x7b4 ); }
	inline int* nSegments() { return MakePointerGEN< int >( this, 0x798 ); }
	inline bool* bConstrainBetweenEndpoints() { return MakePointerGEN< bool >( this, 0x840 ); }
	inline int* Subdiv() { return MakePointerGEN< int >( this, 0x7a8 ); }
	inline float* Width() { return MakePointerGEN< float >( this, 0x7bc ); }
	inline float* flScrollSpeed() { return MakePointerGEN< float >( this, 0x504 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x174 ); }
	inline int* iParentAttachment() { return MakePointerGEN< int >( this, 0x15e ); }
};
struct GenDT_RagdollManager
{
	inline int* iCurrentMaxRagdollCount() { return MakePointerGEN< int >( this, 0x4d0 ); }
};
struct GenDT_PhysicsProp : public GenDT_BreakableProp
{
	inline bool* bAwake() { return MakePointerGEN< bool >( this, 0x810 ); }
};
struct GenDT_PhysicsPropMultiplayer : public GenDT_PhysicsProp
{
	inline int* iPhysicsMode() { return MakePointerGEN< int >( this, 0x81c ); }
	inline int* fMass() { return MakePointerGEN< int >( this, 0x820 ); }
	inline Vector* collisionMins() { return MakePointerGEN< Vector >( this, 0x824 ); }
	inline Vector* collisionMaxs() { return MakePointerGEN< Vector >( this, 0x830 ); }
};
struct GenDT_PhysBox : public GenDT_BaseEntity
{
	inline float* mass() { return MakePointerGEN< float >( this, 0x4d0 ); }
};
struct GenDT_PhysBoxMultiplayer : public GenDT_PhysBox
{
	inline int* iPhysicsMode() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline int* fMass() { return MakePointerGEN< int >( this, 0x4e0 ); }
};
struct GenDT_BasePropDoor : public GenDT_DynamicProp
{
};
struct GenDT_PointCommentaryNode : public GenDT_BaseAnimating
{
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x810 ); }
	inline float* flStartTime() { return MakePointerGEN< float >( this, 0x814 ); }
	inline int* iszCommentaryFile() { return MakePointerGEN< int >( this, 0x818 ); }
	inline int* iszCommentaryFileNoHDR() { return MakePointerGEN< int >( this, 0x91c ); }
	inline int* iszSpeakers() { return MakePointerGEN< int >( this, 0xa20 ); }
	inline int* iNodeNumber() { return MakePointerGEN< int >( this, 0xb20 ); }
	inline int* iNodeNumberMax() { return MakePointerGEN< int >( this, 0xb24 ); }
	inline EHANDLE* hViewPosition() { return MakePointerGEN< EHANDLE >( this, 0xb2c ); }
};
struct GenDT_PointCamera : public GenDT_BaseEntity
{
	inline float* FOV() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* Resolution() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline bool* bFogEnable() { return MakePointerGEN< bool >( this, 0x4d8 ); }
	inline int* FogColor() { return MakePointerGEN< int >( this, 0x4d9 ); }
	inline float* flFogStart() { return MakePointerGEN< float >( this, 0x4e0 ); }
	inline float* flFogEnd() { return MakePointerGEN< float >( this, 0x4e4 ); }
	inline float* flFogMaxDensity() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x4ec ); }
	inline bool* bUseScreenAspectRatio() { return MakePointerGEN< bool >( this, 0x4ed ); }
};
struct GenDT_Plasma : public GenDT_BaseEntity
{
	inline float* flStartScale() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* flScale() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline float* flScaleTime() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline int* nPlasmaModelIndex() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline int* nPlasmaModelIndex2() { return MakePointerGEN< int >( this, 0x4e4 ); }
	inline int* nGlowModelIndex() { return MakePointerGEN< int >( this, 0x4e8 ); }
};
struct GenDT_PhysMagnet : public GenDT_BaseAnimating
{
};
struct GenDT_ParticleSystem
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline EHANDLE* hOwnerEntity() { return MakePointerGEN< EHANDLE >( this, 0x484 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x174 ); }
	inline int* iParentAttachment() { return MakePointerGEN< int >( this, 0x15e ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline int* iEffectIndex() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x4d4 ); }
	inline float* flStartTime() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline EHANDLE* hControlPointEnts() { return MakePointerGEN< EHANDLE >( this, 0x4dc ); } // Array size = 63
	inline int* iControlPointParents() { return MakePointerGEN< int >( this, 0x5d8 ); } // Array size = 63
	inline bool* bWeatherEffect() { return MakePointerGEN< bool >( this, 0x617 ); }
};
struct GenDT_MaterialModifyControl : public GenDT_BaseEntity
{
	inline char** szMaterialName() { return MakePointerGEN< char* >( this, 0x4d0 ); }
	inline char** szMaterialVar() { return MakePointerGEN< char* >( this, 0x5cf ); }
	inline char** szMaterialVarValue() { return MakePointerGEN< char* >( this, 0x6ce ); }
	inline int* iFrameStart() { return MakePointerGEN< int >( this, 0x7d8 ); }
	inline int* iFrameEnd() { return MakePointerGEN< int >( this, 0x7dc ); }
	inline bool* bWrap() { return MakePointerGEN< bool >( this, 0x7e0 ); }
	inline float* flFramerate() { return MakePointerGEN< float >( this, 0x7e4 ); }
	inline bool* bNewAnimCommandsSemaphore() { return MakePointerGEN< bool >( this, 0x7e8 ); }
	inline float* flFloatLerpStartValue() { return MakePointerGEN< float >( this, 0x7ec ); }
	inline float* flFloatLerpEndValue() { return MakePointerGEN< float >( this, 0x7f0 ); }
	inline float* flFloatLerpTransitionTime() { return MakePointerGEN< float >( this, 0x7f4 ); }
	inline bool* bFloatLerpWrap() { return MakePointerGEN< bool >( this, 0x7f8 ); }
	inline int* nModifyMode() { return MakePointerGEN< int >( this, 0x800 ); }
};
struct GenDT_LightGlow
{
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* nHorizontalSize() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* nVerticalSize() { return MakePointerGEN< int >( this, 0x4d4 ); }
	inline int* nMinDist() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline int* nMaxDist() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline int* nOuterMaxDist() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline int* spawnflags() { return MakePointerGEN< int >( this, 0x4e4 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x174 ); }
	inline float* flGlowProxySize() { return MakePointerGEN< float >( this, 0x5b4 ); }
	inline float* HDRColorScale() { return MakePointerGEN< float >( this, 0x0 ); }
};
struct GenDT_InfoOverlayAccessor
{
	inline int* iTextureFrameIndex() { return MakePointerGEN< int >( this, 0x478 ); }
	inline int* iOverlayID() { return MakePointerGEN< int >( this, 0x4d0 ); }
};
struct GenDT_FuncTrackTrain : public GenDT_BaseEntity
{
};
struct GenDT_FuncSmokeVolume : public GenDT_BaseParticleEntity
{
	inline int* Color1() { return MakePointerGEN< int >( this, 0x5bc ); }
	inline int* Color2() { return MakePointerGEN< int >( this, 0x5c0 ); }
	inline float* ParticleDrawWidth() { return MakePointerGEN< float >( this, 0x6c4 ); }
	inline float* ParticleSpacingDistance() { return MakePointerGEN< float >( this, 0x6c8 ); }
	inline float* DensityRampSpeed() { return MakePointerGEN< float >( this, 0x6cc ); }
	inline float* RotationSpeed() { return MakePointerGEN< float >( this, 0x6d0 ); }
	inline float* MovementSpeed() { return MakePointerGEN< float >( this, 0x6d4 ); }
	inline float* Density() { return MakePointerGEN< float >( this, 0x6d8 ); }
	inline int* spawnflags() { return MakePointerGEN< int >( this, 0x6dc ); }
	inline CCollisionProperty* Collision() { return MakePointerGEN< CCollisionProperty >( this, 0x180 ); }
}; // Fail count = 1
struct GenDT_FuncRotating : public GenDT_BaseEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x2f0 ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x2f4 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x2f8 ); }
	inline float* flSimulationTime() { return MakePointerGEN< float >( this, 0x68 ); }
};
struct GenDT_FuncReflectiveGlass : public GenDT_BaseEntity
{
};
struct GenDT_FuncOccluder : public GenDT_BaseEntity
{
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x4d4 ); }
	inline int* nOccluderIndex() { return MakePointerGEN< int >( this, 0x4d0 ); }
};
struct GenDT_FuncMonitor : public GenDT_BaseEntity
{
};
struct GenDT_Func_LOD : public GenDT_BaseEntity
{
	inline int* fDisappearDist() { return MakePointerGEN< int >( this, 0x4d0 ); }
};
struct GenDT_TEDust : public GenDT_TEParticleSystem
{
	inline float* flSize() { return MakePointerGEN< float >( this, 0x1c ); }
	inline float* flSpeed() { return MakePointerGEN< float >( this, 0x20 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x24 ); }
};
struct GenDT_Func_Dust
{
	struct CCollisionProperty
	{
		inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x8 ); }
		inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x14 ); }
		inline int* nSolidType() { return MakePointerGEN< int >( this, 0x29 ); }
		inline int* usSolidFlags() { return MakePointerGEN< int >( this, 0x24 ); }
		inline int* nSurroundType() { return MakePointerGEN< int >( this, 0x28 ); }
		inline int* triggerBloat() { return MakePointerGEN< int >( this, 0x2a ); }
		inline Vector* vecSpecifiedSurroundingMins() { return MakePointerGEN< Vector >( this, 0x2c ); }
		inline Vector* vecSpecifiedSurroundingMaxs() { return MakePointerGEN< Vector >( this, 0x38 ); }
	};
	inline int* Color() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* SpawnRate() { return MakePointerGEN< int >( this, 0x4d4 ); }
	inline float* flSizeMin() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline float* flSizeMax() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline int* LifetimeMin() { return MakePointerGEN< int >( this, 0x4e4 ); }
	inline int* LifetimeMax() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* DustFlags() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* SpeedMax() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline int* DistMax() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x8c ); }
	inline float* FallSpeed() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline CCollisionProperty* Collision() { return MakePointerGEN< CCollisionProperty >( this, 0x180 ); }
};
struct GenDT_FuncConveyor : public GenDT_BaseEntity
{
	inline float* flConveyorSpeed() { return MakePointerGEN< float >( this, 0x4d0 ); }
};
struct GenDT_BreakableSurface : public GenDT_BaseEntity
{
	inline int* nNumWide() { return MakePointerGEN< int >( this, 0x4d4 ); }
	inline int* nNumHigh() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline float* flPanelWidth() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline float* flPanelHeight() { return MakePointerGEN< float >( this, 0x4e0 ); }
	inline Vector* vNormal() { return MakePointerGEN< Vector >( this, 0x4e4 ); }
	inline Vector* vCorner() { return MakePointerGEN< Vector >( this, 0x4f0 ); }
	inline bool* bIsBroken() { return MakePointerGEN< bool >( this, 0x4fc ); }
	inline int* nSurfaceType() { return MakePointerGEN< int >( this, 0x500 ); }
}; // Fail count = 1
struct GenDT_FuncAreaPortalWindow : public GenDT_BaseEntity
{
	inline float* flFadeStartDist() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* flFadeDist() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline float* flTranslucencyLimit() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline int* iBackgroundModelIndex() { return MakePointerGEN< int >( this, 0x4dc ); }
};
struct GenDT_CFish
{
	inline Vector* poolOrigin() { return MakePointerGEN< Vector >( this, 0x86c ); }
	inline float* x() { return MakePointerGEN< float >( this, 0x854 ); }
	inline float* y() { return MakePointerGEN< float >( this, 0x858 ); }
	inline float* z() { return MakePointerGEN< float >( this, 0x85c ); }
	inline QAngle* angle() { return MakePointerGEN< QAngle >( this, 0x864 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x8c ); }
	inline int* lifeState() { return MakePointerGEN< int >( this, 0x8f ); }
	inline float* waterLevel() { return MakePointerGEN< float >( this, 0x878 ); }
};
struct GenDT_EntityFlame : public GenDT_BaseEntity
{
	inline EHANDLE* hEntAttached() { return MakePointerGEN< EHANDLE >( this, 0x4d4 ); }
};
struct GenDT_FireSmoke : public GenDT_BaseEntity
{
	inline float* flStartScale() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* flScale() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline float* flScaleTime() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x4dc ); }
	inline int* nFlameModelIndex() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline int* nFlameFromAboveModelIndex() { return MakePointerGEN< int >( this, 0x4e4 ); }
};
struct GenDT_EnvTonemapController : public GenDT_BaseEntity
{
	inline bool* bUseCustomAutoExposureMin() { return MakePointerGEN< bool >( this, 0x4d0 ); }
	inline bool* bUseCustomAutoExposureMax() { return MakePointerGEN< bool >( this, 0x4d1 ); }
	inline bool* bUseCustomBloomScale() { return MakePointerGEN< bool >( this, 0x4d2 ); }
	inline float* flCustomAutoExposureMin() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline float* flCustomAutoExposureMax() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline float* flCustomBloomScale() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline float* flCustomBloomScaleMinimum() { return MakePointerGEN< float >( this, 0x4e0 ); }
};
struct GenDT_EnvScreenEffect : public GenDT_BaseEntity
{
	inline float* flDuration() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline int* nType() { return MakePointerGEN< int >( this, 0x4d4 ); }
};
struct GenDT_EnvScreenOverlay : public GenDT_BaseEntity
{
	inline int* iszOverlayNames0() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* iszOverlayNames() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 10
	inline float* flOverlayTimes0() { return MakePointerGEN< float >( this, 0xec8 ); }
	inline float* flOverlayTimes() { return MakePointerGEN< float >( this, 0x0 ); } // Array size = 10
	inline float* flStartTime() { return MakePointerGEN< float >( this, 0xef0 ); }
	inline int* iDesiredOverlay() { return MakePointerGEN< int >( this, 0xef4 ); }
	inline bool* bIsActive() { return MakePointerGEN< bool >( this, 0xef8 ); }
};
struct GenDT_EnvProjectedTexture : public GenDT_BaseEntity
{
	inline EHANDLE* hTargetEntity() { return MakePointerGEN< EHANDLE >( this, 0x4d4 ); }
	inline bool* bState() { return MakePointerGEN< bool >( this, 0x4d8 ); }
	inline float* flLightFOV() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline bool* bEnableShadows() { return MakePointerGEN< bool >( this, 0x4e0 ); }
	inline bool* bLightOnlyTarget() { return MakePointerGEN< bool >( this, 0x4e1 ); }
	inline bool* bLightWorld() { return MakePointerGEN< bool >( this, 0x4e2 ); }
	inline bool* bCameraSpace() { return MakePointerGEN< bool >( this, 0x4e3 ); }
	inline Vector* LinearFloatLightColor() { return MakePointerGEN< Vector >( this, 0x4e4 ); }
	inline float* flAmbient() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline int* nSpotlightTextureFrame() { return MakePointerGEN< int >( this, 0x600 ); }
	inline float* flNearZ() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline float* flFarZ() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline int* nShadowQuality() { return MakePointerGEN< int >( this, 0x604 ); }
}; // Fail count = 1
struct GenDT_EnvParticleScript : public GenDT_BaseAnimating
{
	inline float* flSequenceScale() { return MakePointerGEN< float >( this, 0x8f4 ); }
};
struct GenDT_FogController
{
	inline int* fog_enable() { return MakePointerGEN< int >( this, 0x510 ); }
	inline int* fog_blend() { return MakePointerGEN< int >( this, 0x511 ); }
	inline int* fog_dirPrimary() { return MakePointerGEN< int >( this, 0x4d4 ); }
	inline int* fog_colorPrimary() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline int* fog_colorSecondary() { return MakePointerGEN< int >( this, 0x4e4 ); }
	inline int* fog_start() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* fog_end() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* fog_farz() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* fog_maxdensity() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline int* fog_colorPrimaryLerpTo() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* fog_colorSecondaryLerpTo() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* fog_startLerpTo() { return MakePointerGEN< int >( this, 0x500 ); }
	inline int* fog_endLerpTo() { return MakePointerGEN< int >( this, 0x504 ); }
	inline int* fog_lerptime() { return MakePointerGEN< int >( this, 0x508 ); }
	inline int* fog_duration() { return MakePointerGEN< int >( this, 0x50c ); }
};
struct GenDT_EntityParticleTrail : public GenDT_BaseParticleEntity
{
	struct CEntityParticleTrailInfo
	{
		inline float* flLifetime() { return MakePointerGEN< float >( this, 0x8 ); }
		inline float* flStartSize() { return MakePointerGEN< float >( this, 0xc ); }
		inline float* flEndSize() { return MakePointerGEN< float >( this, 0x10 ); }
	};
	inline int* iMaterialName() { return MakePointerGEN< int >( this, 0x5b8 ); }
	inline CEntityParticleTrailInfo* Info() { return MakePointerGEN< CEntityParticleTrailInfo >( this, 0x5bc ); }
	inline EHANDLE* hConstraintEntity() { return MakePointerGEN< EHANDLE >( this, 0x5d0 ); }
};
struct GenDT_EntityDissolve : public GenDT_BaseEntity
{
	inline float* flStartTime() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline float* flFadeOutStart() { return MakePointerGEN< float >( this, 0x4d8 ); }
	inline float* flFadeOutLength() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline float* flFadeOutModelStart() { return MakePointerGEN< float >( this, 0x4e0 ); }
	inline float* flFadeOutModelLength() { return MakePointerGEN< float >( this, 0x4e4 ); }
	inline float* flFadeInStart() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flFadeInLength() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline int* nDissolveType() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline Vector* vDissolverOrigin() { return MakePointerGEN< Vector >( this, 0x504 ); }
	inline int* nMagnitude() { return MakePointerGEN< int >( this, 0x510 ); }
};
struct GenDT_DynamicLight : public GenDT_BaseEntity
{
	inline int* Flags() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* LightStyle() { return MakePointerGEN< int >( this, 0x4d1 ); }
	inline float* Radius() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline int* Exponent() { return MakePointerGEN< int >( this, 0x4d8 ); }
	inline float* InnerAngle() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline float* OuterAngle() { return MakePointerGEN< float >( this, 0x4e0 ); }
	inline float* SpotRadius() { return MakePointerGEN< float >( this, 0x4e4 ); }
};
struct GenDT_ColorCorrectionVolume : public GenDT_BaseEntity
{
	inline float* Weight() { return MakePointerGEN< float >( this, 0x4d0 ); }
}; // Fail count = 1
struct GenDT_ColorCorrection : public GenDT_BaseEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x4d0 ); }
	inline float* minFalloff() { return MakePointerGEN< float >( this, 0x4dc ); }
	inline float* maxFalloff() { return MakePointerGEN< float >( this, 0x4e0 ); }
	inline float* flCurWeight() { return MakePointerGEN< float >( this, 0x4e4 ); }
	inline int* netLookupFilename() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline bool* bEnabled() { return MakePointerGEN< bool >( this, 0x5ec ); }
};
struct GenDT_BaseDoor : public GenDT_BaseEntity
{
	inline float* flWaveHeight() { return MakePointerGEN< float >( this, 0x4d0 ); }
};
struct GenDT_BoneFollower : public GenDT_BaseEntity
{
	inline int* modelIndex() { return MakePointerGEN< int >( this, 0x4d0 ); }
	inline int* solidIndex() { return MakePointerGEN< int >( this, 0x4d4 ); }
};
struct GenDT_InfoLightingRelative : public GenDT_BaseEntity
{
	inline EHANDLE* hLightingLandmark() { return MakePointerGEN< EHANDLE >( this, 0x4d0 ); }
};
struct GenDT_AI_BaseNPC : public GenDT_BaseCombatCharacter
{
	inline int* lifeState() { return MakePointerGEN< int >( this, 0x8f ); }
	inline bool* bPerformAvoidance() { return MakePointerGEN< bool >( this, 0xd3c ); }
	inline bool* bIsMoving() { return MakePointerGEN< bool >( this, 0xd3d ); }
	inline bool* bFadeCorpse() { return MakePointerGEN< bool >( this, 0xd3e ); }
	inline int* iDeathPose() { return MakePointerGEN< int >( this, 0xd2c ); }
	inline int* iDeathFrame() { return MakePointerGEN< int >( this, 0xd30 ); }
	inline int* iSpeedModRadius() { return MakePointerGEN< int >( this, 0xd34 ); }
	inline int* iSpeedModSpeed() { return MakePointerGEN< int >( this, 0xd38 ); }
	inline bool* bSpeedModActive() { return MakePointerGEN< bool >( this, 0xd3f ); }
	inline bool* bImportanRagdoll() { return MakePointerGEN< bool >( this, 0xd40 ); }
	inline float* flTimePingEffect() { return MakePointerGEN< float >( this, 0xd28 ); }
};
struct GenDT_Beam
{
	struct CBeamPredictableId
	{
		inline int* PredictableID() { return MakePointerGEN< int >( this, 0x9c ); }
		inline bool* bIsPlayerSimulated() { return MakePointerGEN< bool >( this, 0x474 ); }
	};
	inline int* nBeamType() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* nBeamFlags() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* nNumBeamEnts() { return MakePointerGEN< int >( this, 0x4e0 ); }
	inline EHANDLE* hAttachEntity() { return MakePointerGEN< EHANDLE >( this, 0x4f4 ); } // Array size = 10
	inline int* nAttachIndex() { return MakePointerGEN< int >( this, 0x51c ); } // Array size = 10
	inline int* nHaloIndex() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* fHaloScale() { return MakePointerGEN< int >( this, 0x550 ); }
	inline int* fWidth() { return MakePointerGEN< int >( this, 0x544 ); }
	inline int* fEndWidth() { return MakePointerGEN< int >( this, 0x548 ); }
	inline int* fFadeLength() { return MakePointerGEN< int >( this, 0x54c ); }
	inline int* fAmplitude() { return MakePointerGEN< int >( this, 0x554 ); }
	inline int* fStartFrame() { return MakePointerGEN< int >( this, 0x558 ); }
	inline int* fSpeed() { return MakePointerGEN< int >( this, 0x55c ); }
	inline float* flFrameRate() { return MakePointerGEN< float >( this, 0x4d0 ); }
	inline float* flHDRColorScale() { return MakePointerGEN< float >( this, 0x4d4 ); }
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* nRenderFX() { return MakePointerGEN< int >( this, 0x54 ); }
	inline int* nRenderMode() { return MakePointerGEN< int >( this, 0x7c ); }
	inline float* flFrame() { return MakePointerGEN< float >( this, 0x564 ); }
	inline Vector* vecEndPos() { return MakePointerGEN< Vector >( this, 0x568 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x8c ); }
	inline int* nMinDXLevel() { return MakePointerGEN< int >( this, 0x560 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2e4 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x174 ); }
	inline CBeamPredictableId* beampredictable_id() { return MakePointerGEN< CBeamPredictableId >( this, 0x0 ); }
};
