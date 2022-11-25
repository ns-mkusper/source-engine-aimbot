#ifndef _SDK_H_
#define _SDK_H_
#define CLIENT_DLL

//disable shit error
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4541 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4183 )

extern char DllPath[2048];

#define DO_ONCE( arg )				\
	static bool UnIqUe_ONC3 = false;\
	if( UnIqUe_ONC3 == false )\
{									\
	UnIqUe_ONC3 = true;				\
	arg								\
}

//win32
#include <windows.h>
#include <tlhelp32.h>
#include <winsock.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <vector>
#include <fstream>
#include <istream>
#include <string.h>

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy",on)
#include <Security.h>
#include <shlwapi.h>

//hack files (game sdk)
#include "SDK/public/cdll_int.h"
#include "SDK/game/client/cdll_client_int.h"
#include "SDK/public/tier1/tier1.h"
#include "SDK/public/vgui_controls/Panel.h"
//#include "SDK\game\server\baseentity.h"
#include "SDK/public/mathlib/mathlib.h"
#include "SDK/game/client/cbase.h"
#include "SDK/game/client/iclientmode.h"
#include "SDK/game/client/input.h"
#include "SDK/game/client/c_basecombatcharacter.h"
#include "SDK/public/con_nprint.h"
#include "SDK/public/vgui_controls/controls.h"
#include "SDK/public/vgui/ISurface.h"
#include "SDK/public/ienginevgui.h"
#include "SDK/public/vgui/IPanel.h"
#include "SDK/public/vgui/IClientPanel.h"
#include "SDK/game/client/game_controls/commandmenu.h"
#include "SDK/public/VGuiMatSurface/IMatSystemSurface.h"
#include "SDK/public/ienginevgui.h"
#include "SDK/public/vgui/IClientPanel.h"
#include "SDK/public/vgui/IPanel.h"
#include "SDK/public/vgui/ISurface.h"
#include "SDK/public/vgui_controls/Panel.h"
#include "SDK/game/shared/in_buttons.h"
#include "SDK/game/shared/IEffects.h"
#include "SDK/game/shared/ichoreoeventcallback.h"
#include "SDK/game/shared/igamemovement.h"
#include "SDK/game/shared/igamesystem.h"
#include "SDK/game/shared/imovehelper.h"
#include "SDK/game/shared/interval.h"
#include "SDK/game/shared/in_buttons.h"
#include "SDK/game/shared/iplayeranimstate.h"
#include "SDK/game/shared/ipredictionsystem.h"
#include "SDK/game/shared/iscenetokenprocessor.h"
#include "SDK/game/shared/itempents.h"
#include "SDK/game/shared/IEffects.h"
#include "SDK/game/shared/IVehicle.h"
#include "SDK/game/client/prediction.h"
#include "SDK/common/GameUI/IGameUI.h"
#include "SDK/public/inetchannelinfo.h"
#include "SDK/public/iefx.h"
#include "SDK/game/server/networkstringtable_gamedll.h"
#include "SDK/public/engine/ivdebugoverlay.h"
#include "SDK/public/engine/IEngineSound.h"
#include "SDK/public/IGameUIFuncs.h"
#include "SDK/public/igameevents.h"
#include "SDK/public/inputsystem/iinputsystem.h"
#include "SDK/public/avi/iavi.h"
#include "SDK/public/avi/ibik.h"
#include "SDK/public/scenefilecache/ISceneFileCache.h"
//#include "SDK/public/GameUI/IGameConsole.h"

#include "SDK/public/ienginevgui.h"
#include "SDK/public/vgui/Cursor.h"
#include "SDK/public/vgui/Dar.h"
#include "SDK/public/vgui/IBorder.h"
#include "SDK/public/vgui/IClientPanel.h"
#include "SDK/public/vgui/IPanel.h"
#include "SDK/public/vgui/ISurface.h"
#include "SDK/public/vgui/IInputInternal.h"
#include "SDK/public/vgui_controls/Frame.h"
#include "SDK/public/vgui_controls/CheckButton.h"
#include "SDK/public/vgui_controls/ComboBox.h"
#include "SDK/public/vgui_controls/Button.h"
#include "SDK/public/vgui_controls/Controls.h"
#include "SDK/public/vgui_controls/DialogManager.h"
#include "SDK/public/vgui_controls/RadioButton.h"
#include "SDK/public/vgui_controls/Menu.h"
#include "SDK/public/vgui/ILocalize.h"
#include "SDK/public/collisionutils.h"
#include "SDK\public\icliententitylist.h"
#include "SDK\game\shared\basecombatweapon_shared.h"

#include <tchar.h>

#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr)+(DWORD)(addValue))

//cred to pato for these macros, and the whole color code thing
#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define RGBA(COLORCODE) RED( COLORCODE ), GREEN( COLORCODE ), BLUE( COLORCODE ), ALPHA( COLORCODE )

#define CHEAT_ORANGE COLORCODE( 255, 100, 000, 255 )
#define CHEAT_YELLOW COLORCODE( 255, 255, 0, 255 )
#define CHEAT_PURPLE COLORCODE( 55, 25, 128, 255 )
#define CHEAT_RED COLORCODE( 255, 0, 0, 255 )
#define CHEAT_GREEN COLORCODE( 0, 255, 0, 255 )
#define CHEAT_BLUE COLORCODE( 0, 0, 255, 255 )
#define CHEAT_BLACK COLORCODE( 0, 0, 0, 255 )
#define CHEAT_WHITE COLORCODE( 255, 255, 255, 255 )

enum TFStatType_t
{
	TFSTAT_UNDEFINED = 0,
	TFSTAT_SHOTS_HIT,
	TFSTAT_SHOTS_FIRED,
	TFSTAT_KILLS,
	TFSTAT_DEATHS,
	TFSTAT_DAMAGE,
	TFSTAT_CAPTURES,
	TFSTAT_DEFENSES,
	TFSTAT_DOMINATIONS,
	TFSTAT_REVENGE,
	TFSTAT_POINTSSCORED,
	TFSTAT_BUILDINGSDESTROYED,
	TFSTAT_HEADSHOTS,
	TFSTAT_PLAYTIME,
	TFSTAT_HEALING,
	TFSTAT_INVULNS,
	TFSTAT_KILLASSISTS,
	TFSTAT_BACKSTABS,
	TFSTAT_HEALTHLEACHED,
	TFSTAT_BUILDINGSBUILT,
	TFSTAT_MAXSENTRYKILLS,
	TFSTAT_TELEPORTS,
	TFSTAT_FIREDAMAGE,
	TFSTAT_BONUS_POINTS,
	TFSTAT_BLASTDAMAGE
};

//===================================================================================
//Weapon ID Define List
//Scout
#define WPN_Scattergun 221
#define WPN_Pistol 201
#define WPN_FAN 45
#define WPN_Shortstop 220
#define WPN_ScoutPistol 23
#define WPN_Bonk 46
#define WPN_CritCola 163
#define WPN_Lugermorph 160
#define WPN_Milk 222
#define WPN_Bat 167
#define WPN_Sandman 44
#define WPN_Fish 221
//Soldier
#define WPN_RocketLauncher 18
#define WPN_DirectHit 127
#define WPN_BlackBox 228
#define WPN_RocketJump 237
#define WPN_SoldierShotgun 10
#define WPN_BuffBanner 129
#define WPN_BattalionBackup 226
#define WPN_Shovel 6
#define WPN_Equalizer 128
#define WPN_PainTrain 154
//Pyro
#define WPN_Flamethrower 21
#define WPN_Backburner 40
#define WPN_Degreaser 215
#define WPN_PyroShotgun 12
#define WPN_Flaregun 39
#define WPN_Fireaxe 2
#define WPN_Axtingusher 38
#define WPN_HomeWrecker 153
#define WPN_PowerJack 214
//Demoman
#define WPN_GrenadeLauncher 19
#define WPN_StickyLauncher 20
#define WPN_ScottishResistance 130
#define WPN_StickyJumper 265
#define WPN_Bottle 1
#define WPN_Sword 132
#define WPN_ScottsSkullctter 172
#define WPN_Fryingpan 264
#define WPN_Headless 266
//Heavy
#define WPN_Minigun 15
#define WPN_Natascha 41
#define WPN_HeavyShotgun 11
#define WPN_CandyBar 159
#define WPN_Sandvich 42
#define WPN_Fists 5
#define WPN_KGB 43
#define WPN_GRU 239
//Engineer
#define WPN_EngineerShotgun 9
#define WPN_FrontierJustice 141
#define WPN_EngineerPistol 22
#define WPN_Wrangler 140
#define WPN_Wrench 7
#define WPN_Goldenwrench 169
#define WPN_SouthernHospitality 155
#define WPN_Gunslinger 142
#define WPN_Builder 25
#define WPN_Destructor 26
#define WPN_Toolbox 28
//Medic
#define WPN_SyringeGun 17
#define WPN_Blutsauger 36
#define WPN_Medigun 29
#define WPN_Kritzkrieg 35
#define WPN_Bonesaw 8
#define WPN_Ubersaw 37
#define WPN_Vitasaw 173
//Sniper
#define WPN_SniperRifle 14
#define WPN_Huntsman 175
#define WPN_SydneySleeper 223
#define WPN_SMG 221
#define WPN_Jarate 58
#define WPN_Kukri 3
#define WPN_TribalmansShiv 171
#define WPN_Bushwacka 232
//Spy
#define WPN_Revolver 217	
#define WPN_Ambassador 61
#define WPN_BigKill 161
#define WPN_Letranger 224
#define WPN_Knife 191
#define WPN_EternalReward 225
#define WPN_DisguiseKit 27
//Nonsense
#define WPN_NewBat 190
#define WPN_NewBottle 191
#define WPN_NewAxe 192
#define WPN_NewKukri 193
#define WPN_NewKnife 194
#define WPN_NewFists 195
#define WPN_NewShovel 196
#define WPN_NewWrench 197
#define WPN_NewBonesaw 198
#define WPN_NewShotgun 199
#define WPN_NewScattergun 200
#define WPN_NewSniperRifle 201
#define WPN_NewMinigun 202
#define WPN_NewSMG 203
#define WPN_NewSyringeGun 204
#define WPN_NewRocketLauncher 205
#define WPN_NewPipeLauncher 206
#define WPN_NewStickyLauncher 207
#define WPN_NewFlameThrower 208
#define WPN_NewPistol 209
#define WPN_NewRevolver 210
#define WPN_NewMedigun 211

enum TFCond
{
	TFCond_Slowed = (1 << 0), //Sniper zoom slowdown or minigun spun slowdown.
	TFCond_Zoomed = (1 << 1), //Sniper zoomed.
	TFCond_Disguising = (1 << 2),
	TFCond_Disguised = (1 << 3),
	TFCond_Cloaked = (1 << 4),
	TFCond_Ubercharged = (1 << 5),
	TFCond_TeleportedGlow = (1 << 6), //Will activate when someone leaves a teleporter and has glow beneath their feet.
	TFCond_Taunting = (1 << 7),
	TFCond_UberchargeFading = (1 << 8),
	TFCond_CloakFlicker = (1 << 9), //When a normal cloak spy gets bumped into, or a CloakAndDagger guy with no energy is moving.
	TFCond_Teleporting = (1 << 10), //Only activates for a brief second, not very useful.
	TFCond_Kritzkrieged = (1 << 11),
	//TFCond_Unknown2 = (1 << 12), //Never used. Probably an obsolete condition.
	TFCond_DeadRingered = (1 << 13), //Only toggles after being shot.
	TFCond_Bonked = (1 << 14), //Drank Bonk
	TFCond_Dazed = (1 << 15), //Stunned from a baseball
	TFCond_Buffed = (1 << 16), //Buff Banner
	TFCond_Charging = (1 << 17), //ChargeNTarge
	TFCond_DemoBuff = (1 << 18), //Toggled when the demoknight reaches forced crits from the charge.
	TFCond_CritCola = (1 << 19),
	TFCond_InHealRadius = (1 << 20), //In heal radius of (presumably) a dispenser. I didn't really test this.
	TFCond_Healing = (1 << 21), //Toggled when a medic is healing someone.
	TFCond_OnFire = (1 << 22),
	TFCond_Overhealed = (1 << 23), //Toggled when the player has >100% health.
	TFCond_Jarated = (1 << 24),
	TFCond_Bleeding = (1 << 25), //Toggled from BostonBasher/Tribalman'sShiv/SouthernHospitality damage.
	TFCond_DefenseBuffed = (1 << 26), //Battalion Backup Buff
	TFCond_Milked = (1 << 27), //Player was hit with the mad milk.
	TFCond_MegaHeal = (1 << 28), //Quick-Fix ubercharge.
	TFCond_RegenBuffed = (1 << 29), //Concheror Buf
	TFCond_MarkedForDeath = (1 << 30), //Fan O'War marked
	
	TFCondEx_SpeedBuffAlly = (1 << 0), //Toggled when a player gets hit with the disciplinary action.
	//TFCondEx_HalloweenCritCandy = (1 << 1), //Only for Scream Fortress event maps that drop crit candy.
	TFCondEx_CritHype = (1 << 4), //Soda Popper crits.
	TFCondEx_CritOnFirstBlood = (1 << 5), //Arena first blood crit buff.
	TFCondEx_CritOnWin = (1 << 6), //End of round crits.
	TFCondEx_CritOnFlagCapture = (1 << 7),
	//TFCondEx_CritOnKill = (1 << 8), //Toggled when the player has frontier justice or diamondback kills. (Doesn't work)
	TFCondEx_RestrictToMelee = (1 << 9),

	TFCond_Crits = ( TFCond_Kritzkrieged ),
	TFCond_MiniCrits = ( TFCond_Buffed | TFCond_CritCola ),
	TFCondEx_Crits = ( /*TFCondEx_HalloweenCritCandy |*/ TFCondEx_CritOnFirstBlood | TFCondEx_CritOnWin | TFCondEx_CritOnFlagCapture /*| TFCondEx_CritOnKill*/ ),
	TFCondEx_MiniCrits = ( TFCondEx_CritHype )
};

// Classes returned by iClass
#define TF_SCOUT 1
#define TF_SOLDIER 3
#define TF_PYRO 7
#define TF_DEMOMAN 4
#define TF_HEAVY 6
#define TF_ENGINEER 9
#define TF_MEDIC 5
#define TF_SNIPER 2
#define TF_SPY 8 

//cred to pato for these macros, and the whole color code thing
#define COLORCODE(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define RED(COLORCODE)	((int) ( COLORCODE >> 24) )
#define BLUE(COLORCODE)	((int) ( COLORCODE >> 8 ) & 0xFF )
#define GREEN(COLORCODE)	((int) ( COLORCODE >> 16 ) & 0xFF )
#define ALPHA(COLORCODE)	((int) COLORCODE & 0xFF )
#define RGBA(COLORCODE) RED( COLORCODE ), GREEN( COLORCODE ), BLUE( COLORCODE ), ALPHA( COLORCODE )

#define CHEAT_ORANGE COLORCODE( 255, 100, 000, 255 )
#define CHEAT_YELLOW COLORCODE( 255, 255, 0, 255 )
#define CHEAT_PURPLE COLORCODE( 55, 25, 128, 255 )
#define CHEAT_RED COLORCODE( 255, 0, 0, 255 )
#define CHEAT_GREEN COLORCODE( 0, 255, 0, 255 )
#define CHEAT_BLUE COLORCODE( 0, 0, 255, 255 )
#define CHEAT_BLACK COLORCODE( 0, 0, 0, 255 )
#define CHEAT_WHITE COLORCODE( 255, 255, 255, 255 )

/* Updated from SourceMod's -- tf2.inc */
#define TF_CONDFLAG_NONE                   0
#define TF_CONDFLAG_SLOWED          (1 <<  0)
#define TF_CONDFLAG_ZOOMED          (1 <<  1)
#define TF_CONDFLAG_DISGUISING      (1 <<  2)
#define TF_CONDFLAG_DISGUISED       (1 <<  3)
#define TF_CONDFLAG_CLOAKED         (1 <<  4)
#define TF_CONDFLAG_UBERCHARGED     (1 <<  5)
#define TF_CONDFLAG_TELEPORTGLOW    (1 <<  6)
#define TF_CONDFLAG_TAUNTING        (1 <<  7)
#define TF_CONDFLAG_UBERCHARGEFADE  (1 <<  8)
#define TF_CONDFLAG_TELEPORTING     (1 << 10)
#define TF_CONDFLAG_KRITZKRIEGED    (1 << 11)
#define TF_CONDFLAG_DEADRINGERED    (1 << 13)
#define TF_CONDFLAG_BONKED          (1 << 14)
#define TF_CONDFLAG_DAZED           (1 << 15)
#define TF_CONDFLAG_BUFFED          (1 << 16)
#define TF_CONDFLAG_CHARGING        (1 << 17)
#define TF_CONDFLAG_DEMOBUFF        (1 << 18)
#define TF_CONDFLAG_CRITCOLA        (1 << 19)
#define TF_CONDFLAG_HEALING         (1 << 20)
#define TF_CONDFLAG_ONFIRE          (1 << 22)
#define TF_COND_ONFIRE                    22
#define TF_CONDFLAG_OVERHEALED      (1 << 23)
#define TF_CONDFLAG_JARATED         (1 << 24)
#define TF_CONDFLAG_BLEEDING        (1 << 25)
#define TF_CONDFLAG_DEFENSEBUFFED   (1 << 26)
#define TF_CONDFLAG_MILKED          (1 << 27) 

//like dll main
void add_log(const char * fmt, ...);

//Hook
void LaunchHookThread( void );

extern CreateInterfaceFn g_AppSysFactory;

#define WIN32_LEAN_AND_MEAN

#define M_RADPI 57.295779513082f
#define SQUARE( a ) a*a

//Cheat Header
#include "HalFLife2.h"
#include "client.h"
//#include "panels.h"
#include "Needed.h"
#include "netvars.h"
//#include "esp.h"
#include "inlines.h"
#include "aimbot.h"
//#include "crithack.h"
//#include "playermanager.h"
//#include "cNoSpread.h"

#pragma comment( lib, "SDK/lib/public/tier0.lib" )
#pragma comment( lib, "SDK/lib/public/tier1.lib" )
#pragma comment( lib, "SDK/lib/public/tier2.lib" )
#pragma comment( lib, "SDK/lib/public/tier3.lib" )
#pragma comment( lib, "SDK/lib/public/vgui_controls.lib" )
#pragma comment( lib, "SDK/lib/public/mathlib.lib" )
#pragma comment( lib, "SDK/lib/public/vstdlib.lib" )
#endif // sdk_h__
