#ifndef __HALFLIFE2_H__
#define __HALFLIFE2_H__

#include "sdk.h"
//=====================================
class LocalPlayer;
class CDrawLayer;
class Needed;
class CConsole;
class Esp;
class cNoSpread;
class cAimbot;
//=====================================
class BaseHook
{
public:
	BaseHook::BaseHook();
	//Hooked class
	CGlobalVarsBase                 *m_pGlobals;                    
	CInput				*m_pInput;                      
	IAvi				*m_pAvi;                        
	IBaseClientDLL			*m_pClient;                     
	IBik				*m_pBik;                        
	IClientEntityList		*m_pEntList;                    
	ICvar				*m_pCvar;                       
	IDataCache			*m_pDataCache;                  
	IEngineSound			*m_pEngineSound;                
	IEngineTrace			*m_pEngineTrace;                
	IEngineVGui			*m_pEngineVGui;                 
	IFileSystem			*m_pFileSystem;                 
	IGameEventManager2		*m_pGameEventManager2;          
	IGameUIFuncs			*m_pGameUIFuncs;                
	IInputSystem			*m_pInputSystem;                
	IMatSystemSurface		*m_pMatSurface;                 
	IMaterialSystem			*m_pMaterialSystem;             
	INetworkStringTableContainer	*m_pNetworkStringTableContainer;
	IPhysicsSurfaceProps		*m_pPhysicAPI;                  
	IPrediction			*m_pPrediction;                 
	ISceneFileCache			*m_pSceneFileCache;             
	IShadowMgr			*m_pShadowMgr;                  
	ISoundEmitterSystemBase		*m_pSoundEmitterSystemBase;     
	ISpatialPartition		*m_pSpatialPartition;           
	IStaticPropMgrClient		*m_pStaticPropMgrClient;        
	IStudioRender			*m_pStudioRender;               
	IUniformRandomStream		*m_pUniformRandomStream;        
	IVDebugOverlay			*m_pDebugOverlay;               
	IVEfx				*m_pEfx;                        
	IVEngineClient			*m_pEngineClient;               
	IVModelInfoClient		*m_pModelInfoClient;            
	IVModelRender			*m_pModelRender;                
	IVRenderView			*m_pRenderView;                 
	vgui::IPanel			*m_pPanel;                      
	vgui::ISurface			*m_pSurface;
	IVEngineServer			*m_pEngineServer;

public://cheat class
	LocalPlayer*			m_pMyPlayer;		//My Entity class
	CDrawLayer*				m_pDrawzLayer;		//Panel Shit
//	CUtils*					m_pCUtils;
	Needed*					m_pNeeded;			//Drawing Shit
	CConsole*				m_pHl2GameConsole;	//Game Console
	Esp*					m_pEsp;				//cheat ESP
	cNoSpread*				m_pNoSpread;		//cheat NoSpread
	cAimbot*				m_pAimbot;			//cheat Aimbot
}; 

extern BaseHook HalFLife2;

class LocalPlayer
{
public:
	//=====================================
	inline IClientEntity *Ent( void ) const
	{
		return HalFLife2.m_pEntList->GetClientEntity( HalFLife2.m_pEngineClient->GetLocalPlayer() );
	}
	inline C_BaseEntity *BaseEnt( void ) const
	{
		return Ent()->GetBaseEntity();
	}
	inline IClientRenderable *RenderPlayer( void ) const
	{
		return Ent()->GetClientRenderable();
	}

	//=====================================
};

class hl2_offsets
{
public:
	static void*m_iTeamNum;
	static void*m_vecOrigin;
	static void*m_angRotation;
	static void*m_clrRender;
	static void*m_nHitboxSet;
	static void*m_iFlags;
	static void*m_lifeState;
	static void*m_iHealth;
	static void*m_hActiveWeapon;
	static void*m_bInBombZone;
	static void*m_bIsDefusing;
	static void*m_bInBuyZone;
	static void*m_iArmor;
	static void*m_iEyeAnglesX;
	static void*m_iEyeAnglesY;
	static void*m_vecVelocityX;
	static void*m_vecVelocityY;
	static void*m_vecVelocityZ;
	static void*m_iFov;
	static void*m_vecViewOffsetX;
	static void*m_vecViewOffsetY;
	static void*m_vecViewOffsetZ;
	static void*m_bHasHelmet;
	static void*m_flFlashDuration;
	static void*m_flFlashMaxAlpha;
	static void*m_iPrimaryAddon;
	static void*m_iSecondaryAddon;
	static void*m_iAddonBits;
	static void*m_iObserverMode;
	static void*m_hObserverTarget;
	static void*m_vecPunchAngle;
	static void*m_bSilencerOn_USP;
	static void*m_bSilencerOn_M4A1;
	static void*m_bBurstMode_Glock;
	static void*m_bBurstMode_Famas;
	static void*m_iState;
	static void*m_iClip1;
	static void*m_iClip2;
};

typedef void* (*eCreateInterface)(const char*,int);


#endif