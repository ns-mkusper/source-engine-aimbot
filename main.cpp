#include "main.h"
#include "stdafx.h"
//#define _NOT_LOG

DWORD dwClient;

char cdir[256];


typedef bool(__stdcall* QueryPerformanceCounter_t)(LARGE_INTEGER *lpPerformanceCount);
QueryPerformanceCounter_t pQueryPerformanceCounter;
CreateInterfaceFn appSystemFactory;
CreateInterfaceFn clientFactory;

bool bSpeed = false;

void HideModule(HINSTANCE hModule)
{
        DWORD dwPEB_LDR_DATA = 0;
        __asm{
                pushad;
                pushfd;
                mov eax, fs:[30h]
                mov eax, [eax+0Ch]
                mov dwPEB_LDR_DATA, eax

InLoadOrderModuleList:
                mov esi, [eax+0Ch]
                mov edx, [eax+10h]

LoopInLoadOrderModuleList:
                lodsd
                        mov esi, eax
                        mov ecx, [eax+18h]
                cmp ecx, hModule
                        jne SkipA
                        mov ebx, [eax]
                mov ecx, [eax+4]
                mov [ecx], ebx
                        mov [ebx+4], ecx
                        jmp InMemoryOrderModuleList
SkipA:
                cmp edx, esi
                        jne LoopInLoadOrderModuleList

InMemoryOrderModuleList:
                mov eax, dwPEB_LDR_DATA
                        mov esi, [eax+14h]
                mov edx, [eax+18h]

LoopInMemoryOrderModuleList:
                lodsd
                        mov esi, eax
                        mov ecx, [eax+10h]
                cmp ecx, hModule
                        jne SkipB
                        mov ebx, [eax]
                mov ecx, [eax+4]
                mov [ecx], ebx
                        mov [ebx+4], ecx
                        jmp InInitializationOrderModuleList
SkipB:
                cmp edx, esi
                        jne LoopInMemoryOrderModuleList

InInitializationOrderModuleList:
                mov eax, dwPEB_LDR_DATA
                        mov esi, [eax+1Ch]
                mov edx, [eax+20h]

LoopInInitializationOrderModuleList:
                lodsd
                        mov esi, eax
                        mov ecx, [eax+08h]
                cmp ecx, hModule
                        jne SkipC
                        mov ebx, [eax]
                mov ecx, [eax+4]
                mov [ecx], ebx
                        mov [ebx+4], ecx
                        jmp Finished
SkipC:
                cmp edx, esi
                        jne LoopInInitializationOrderModuleList

Finished:
                popfd;
        }
}

void GetCDir( HMODULE hModule )
{

#ifdef CLIENT_LAUNCHING
        HKEY hKey;
        BOOL bRet = TRUE;
        LONG lReturn = RegOpenKeyEx( HKEY_LOCAL_MACHINE,"SOFTWARE\\DarkSourceLoader\\",0L,KEY_ALL_ACCESS,&hKey);
        if( lReturn == ERROR_SUCCESS )
        {
                char dwText [512] = "";
                DWORD lpcbData = sizeof(dwText);
                lReturn = RegQueryValueEx(hKey, "DarkSourceLoaderPath", NULL, REG_NONE, (BYTE*)dwText, &lpcbData);
                if( lReturn == ERROR_SUCCESS )
                {
                        strcpy(cdir,dwText);
                        //strcat(cdir,"files\\css_by_floxy");
                }
        }
        RegCloseKey(hKey);
#else
        GetModuleFileName( hModule, cdir, sizeof( cdir ) );
        for( int i = 0; i < ( int )strlen( cdir ); i++ )
        {
                if( cdir[ strlen( cdir ) - i ] == '\\' )
                {
                        cdir[ ( strlen( cdir ) -  i ) + 1 ] = '\0';
                        return;
                }
        }
#endif

}

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
        for(; *szMask; ++szMask, ++pData, ++bMask)
        {
                if(*szMask == 'x' && *pData != *bMask)
                {
                        return false;
                }
        }
        return (*szMask) == NULL;
}

DWORD g_dwOrgInit;
int	__stdcall new_Init( CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CGlobalVarsBase *pGlobals )
{
        HalFLife2.m_pGlobals = pGlobals;
        Trace("m_pGlobals: [0x%X]", HalFLife2.m_pGlobals );
        _asm
        {
                PUSH pGlobals
                        PUSH physicsFactory
                        PUSH appSystemFactory
                        CALL g_dwOrgInit
        }

        HalFLife2.m_pSurface	= reinterpret_cast< vgui::ISurface* >( appSystemFactory( VGUI_SURFACE_INTERFACE_VERSION, NULL ) );
        HalFLife2.m_pMatSurface = reinterpret_cast< IMatSystemSurface* >( (IMatSystemSurface*)appSystemFactory("MatSystemSurface006", NULL)  );


}

DWORD g_dwOrgFrameStageNotify;
void __stdcall new_FrameStageNotify ( ClientFrameStage_t curStage )
{
        //QAngle *PunchAngle, OldPunch;
        //C_BaseEntity *pMe;
        //if( curStage == FRAME_RENDER_START)
        //{
        //	if(HalFLife2.m_pEngineClient->IsInGame())
        //	{
        //		pMe = HalFLife2.m_pEntList->GetClientEntity(HalFLife2.m_pEngineClient->GetLocalPlayer())->GetBaseEntity();
        //		PunchAngle = (QAngle*)((DWORD)pMe + (DWORD)hl2_offsets::m_vecPunchAngle );
        //		if(pMe)
        //		{
        //			if( PunchAngle->x != 0 || PunchAngle->y != 0 || PunchAngle->z != 0)
        //			{
        //				OldPunch = *PunchAngle;
        //				*PunchAngle = QAngle(0,0,0);
        //			}
        //		}
        //	}
        //}

        _asm
        {
                PUSH curStage
                        CALL g_dwOrgFrameStageNotify
        }

        //if(curStage == FRAME_RENDER_START)
        //{
        //	if(HalFLife2.m_pEngineClient->IsInGame())
        //	{
        //		if( PunchAngle->x == 0 || PunchAngle->y == 0 || PunchAngle->z == 0)
        //		{
        //			*PunchAngle = OldPunch;
        //		}
        //	}
        //}
}

void *DetourFunc(BYTE *src, const BYTE *dst, const int len)
{
        BYTE *jmp = (BYTE*)malloc(len+5);
        DWORD dwback;

        VirtualProtect(src, len, PAGE_READWRITE, &dwback);

        memcpy(jmp, src, len);	jmp += len;

        jmp[0] = 0xE9;
        *(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;

        src[0] = 0xE9;
        *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

        VirtualProtect(src, len, dwback, &dwback);

        return (jmp-len);
}

bool __stdcall hkQueryPerformanceCounter (LARGE_INTEGER *lpPerformanceCount)
{
        static LONGLONG oldfakevalue = 0;
        static LONGLONG oldrealvalue = 0;

        LONGLONG newvalue;
        BOOL ret;

        if( oldfakevalue == 0 || oldrealvalue == 0 )
        {
                oldfakevalue = lpPerformanceCount->QuadPart;
                oldrealvalue = lpPerformanceCount->QuadPart;
        }

        ret = (pQueryPerformanceCounter)(lpPerformanceCount);

        newvalue  = lpPerformanceCount->QuadPart;

        float factor = 1.0f;

        //    if(bSpeed) factor = gSettings.speed;

        newvalue = oldfakevalue + (LONGLONG)((newvalue - oldrealvalue) * factor);

        oldrealvalue = lpPerformanceCount->QuadPart;
        oldfakevalue = newvalue;

        lpPerformanceCount->QuadPart = newvalue;

        return ret;
}

// Typical "trace" type function
void Trace(LPCSTR format, ...)
{
        if(format)
        {
                va_list vl;
                char	str[4096];

                va_start(vl, format);
                _vsnprintf(str, (sizeof(str) - 1), format, vl);
                str[(sizeof(str) - 1)] = 0;
                va_end(vl);

                // Output to debugger channel
                OutputDebugString(str);
        }
}

bool HookAllInterfaces ()
{
        if ( (HalFLife2.m_pEngineClient = (IVEngineClient *)appSystemFactory( VENGINE_CLIENT_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("EngineClient: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("EngineClient: [0x%X]", HalFLife2.m_pEngineClient );
        }
        if ( (HalFLife2.m_pEntList = (IClientEntityList*)clientFactory(VCLIENTENTITYLIST_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("m_pEntList: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("m_pEntList: [0x%X]", HalFLife2.m_pEntList );
        }
        if ( (HalFLife2.m_pModelRender = (IVModelRender *)appSystemFactory( VENGINE_HUDMODEL_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("ModelRender: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("ModelRender: [0x%X]", HalFLife2.m_pModelRender );
        }
        if ( (HalFLife2.m_pEfx = (IVEfx *)appSystemFactory( VENGINE_EFFECTS_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("Efx: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("Efx: [0x%X]", HalFLife2.m_pEfx );
        }
        if ( (HalFLife2.m_pEngineServer = (IVEngineServer *)appSystemFactory( INTERFACEVERSION_VENGINESERVER, NULL )) == NULL )
        {
                Trace("EngineServer: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("EngineServer: [0x%X]", HalFLife2.m_pEngineServer );
        }
        if ( (HalFLife2.m_pEngineTrace = (IEngineTrace *)appSystemFactory( INTERFACEVERSION_ENGINETRACE_CLIENT, NULL )) == NULL )
        {
                Trace("EngineTrace: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("EngineTrace: [0x%X]", HalFLife2.m_pEngineTrace );
        }
        if ( (HalFLife2.m_pRenderView = (IVRenderView *)appSystemFactory( VENGINE_RENDERVIEW_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("RenderView: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("RenderView: [0x%X]", HalFLife2.m_pRenderView );
        }
        if ( (HalFLife2.m_pDebugOverlay = (IVDebugOverlay *)appSystemFactory( VDEBUG_OVERLAY_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("DebugOverlay: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("DebugOverlay: [0x%X]", HalFLife2.m_pDebugOverlay );
        }
        if ( (HalFLife2.m_pDataCache = (IDataCache*)appSystemFactory(DATACACHE_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("DataCache: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("DataCache: [0x%X]", HalFLife2.m_pDataCache );
        }
        if ( (HalFLife2.m_pModelInfoClient = (IVModelInfoClient *)appSystemFactory(VMODELINFO_CLIENT_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("ModelInfoClient: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("ModelInfoClient: [0x%X]", HalFLife2.m_pModelInfoClient );
        }
        if ( (HalFLife2.m_pEngineVGui = (IEngineVGui *)appSystemFactory(VENGINE_VGUI_VERSION, NULL )) == NULL )
        {
                Trace("EngineVGui: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("EngineVGui: [0x%X]", HalFLife2.m_pEngineVGui );
        }
        if ( (HalFLife2.m_pNetworkStringTableContainer= (INetworkStringTableContainer *)appSystemFactory(INTERFACENAME_NETWORKSTRINGTABLECLIENT,NULL)) == NULL )
        {
                Trace("NetworkStringTableContainer: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("NetworkStringTableContainer: [0x%X]", HalFLife2.m_pNetworkStringTableContainer );
        }
        if ( (HalFLife2.m_pSpatialPartition = (ISpatialPartition *)appSystemFactory(INTERFACEVERSION_SPATIALPARTITION, NULL)) == NULL )
        {
                Trace("SpatialPartition: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("SpatialPartition: [0x%X]", HalFLife2.m_pSpatialPartition );
        }
        if ( (HalFLife2.m_pShadowMgr = (IShadowMgr *)appSystemFactory(ENGINE_SHADOWMGR_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("ShadowMgr: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("ShadowMgr: [0x%X]", HalFLife2.m_pShadowMgr );
        }
        if ( (HalFLife2.m_pStaticPropMgrClient = (IStaticPropMgrClient *)appSystemFactory(INTERFACEVERSION_STATICPROPMGR_CLIENT, NULL)) == NULL )
        {
                Trace("StaticPropMgrClient: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("StaticPropMgrClient: [0x%X]", HalFLife2.m_pStaticPropMgrClient );
        }
        if ( (HalFLife2.m_pEngineSound = (IEngineSound *)appSystemFactory(IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("EngineSound: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("EngineSound: [0x%X]", HalFLife2.m_pEngineSound );
        }
        if ( (HalFLife2.m_pFileSystem = (IFileSystem *)appSystemFactory(FILESYSTEM_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("FileSystem: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("FileSystem: [0x%X]", HalFLife2.m_pFileSystem );
        }
        if ( (HalFLife2.m_pUniformRandomStream = (IUniformRandomStream *)appSystemFactory(VENGINE_CLIENT_RANDOM_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("UniformRandomStream: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("UniformRandomStream: [0x%X]", HalFLife2.m_pUniformRandomStream );
        }
        if ( (HalFLife2.m_pGameUIFuncs = (IGameUIFuncs * )appSystemFactory( VENGINE_GAMEUIFUNCS_VERSION, NULL )) == NULL )
        {
                Trace("GameUifuncs: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("GameUifuncs: [0x%X]", HalFLife2.m_pGameUIFuncs );
        }
        if ( (HalFLife2.m_pGameEventManager2 = (IGameEventManager2 *)appSystemFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2,NULL)) == NULL )
        {
                Trace("GameEventManager: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("GameEventManager: [0x%X]", HalFLife2.m_pGameEventManager2 );
        }
        if ( (HalFLife2.m_pSoundEmitterSystemBase = (ISoundEmitterSystemBase *)appSystemFactory(SOUNDEMITTERSYSTEM_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("SoundEmitterSystemBase: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("SoundEmitterSystemBase: [0x%X]", HalFLife2.m_pSoundEmitterSystemBase );
        }
        if ( (HalFLife2.m_pInputSystem = (IInputSystem *)appSystemFactory(INPUTSYSTEM_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("InputSystem: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("InputSystem: [0x%X]", HalFLife2.m_pInputSystem );
        }
        if ( (HalFLife2.m_pPanel = (vgui::IPanel*)appSystemFactory(VGUI_PANEL_INTERFACE_VERSION, NULL)) == NULL )
        {
                Trace("m_pPanel: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("m_pPanel: [0x%X]", HalFLife2.m_pPanel );
        }
        if ( (HalFLife2.m_pSurface     = (vgui::ISurface*)appSystemFactory("VGUI_Surface030", NULL)) == NULL )
        {
                Trace("m_pSurface: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("m_pSurface: [0x%X]", HalFLife2.m_pSurface );
        }
        if ( (HalFLife2.m_pPhysicAPI = (IPhysicsSurfaceProps*)appSystemFactory(VPHYSICS_SURFACEPROPS_INTERFACE_VERSION,NULL)) == NULL )
        {
                Trace("m_pPhysicAPI: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("m_pPhysicAPI: [0x%X]", HalFLife2.m_pPhysicAPI );
        }

        if ( (HalFLife2.m_pSceneFileCache = (ISceneFileCache *)appSystemFactory( SCENE_FILE_CACHE_INTERFACE_VERSION, NULL )) == NULL )
        {
                Trace("SceneFileCache: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("SceneFileCache: [0x%X]", HalFLife2.m_pSceneFileCache );
        }

        if ( (HalFLife2.m_pMatSurface = (IMatSystemSurface*)appSystemFactory("MatSystemSurface006", NULL)) == NULL )
        {
                Trace("m_pMatSurface: NULL NULL NULL");
                //return false;
        }
        else
        {
                Trace("m_pMatSurface: [0x%X]", HalFLife2.m_pMatSurface );
        }
        return true;
}

CreateInterfaceFn CaptureFactory( char *pszFactoryModule )
{
        CreateInterfaceFn fn = NULL;

        while( fn == NULL )
        {
                HMODULE hFactoryModule = GetModuleHandleA( pszFactoryModule );

                if( hFactoryModule )
                {
                        fn = reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hFactoryModule, "CreateInterface" ) );
                }

                Sleep( 10 );
        }

        return fn;
}

void *CaptureInterface( CreateInterfaceFn fn, char *pszInterfaceName )
{
        unsigned long *ptr = NULL;

        while( ptr == NULL )
        {
                ptr = reinterpret_cast< unsigned long* >( fn( pszInterfaceName, NULL ) );

                Sleep( 10 );
        }

        return ptr;
}

DWORD WINAPI dwInitThread(LPVOID lpArgs)
{
        //pQueryPerformanceCounter = (QueryPerformanceCounter_t) DetourFunc ( (PBYTE)(DWORD)GetProcAddress(LoadLibrary("kernel32.dll"), "QueryPerformanceCounter"), (PBYTE)hkQueryPerformanceCounter, 5 );

        while( GetModuleHandleA( "engine.dll" ) == NULL || GetModuleHandleA( "client.dll" ) == NULL )
                Sleep( 100 );

        while(true)
        {
                if(HalFLife2.m_pClient == NULL && GetModuleHandleA("client.dll"))
                {
                        DWORD dwClientDLL_Init = NULL;
                        char szClientDLL_InitSig[] = "\xA1\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\x11\x83\xC4\x04\x68\x00\x00\x00\x00\x50\x50\x8B\x02";
                        char szClientDLL_InitMsk[] = "x????xx????xxxxxx????xxxx";

                        dwClientDLL_Init = gMemoryTools.dwFindPattern( (DWORD)GetModuleHandleA("engine.dll"), dwEngine_Size, (PBYTE)szClientDLL_InitSig, szClientDLL_InitMsk);
                        if(dwClientDLL_Init)
                        {
                                dwClient = (DWORD)GetModuleHandle("client.dll");

                                appSystemFactory = (CreateInterfaceFn)*(DWORD*)*(DWORD*)(dwClientDLL_Init + 0x1);
                                Trace("appSystemFactory: [0x%X]",appSystemFactory);
                                DWORD ppClient = *(DWORD*)(dwClientDLL_Init + 0x7);
                                clientFactory = (CreateInterfaceFn)*(DWORD*)(ppClient - 0x8);

                                //CreateInterfaceFn fnClient		= CaptureFactory( "client.dll" );
                                //CreateInterfaceFn fnEngine		= CaptureFactory( "engine.dll" );
                                CreateInterfaceFn fnVStd		= CaptureFactory( "vstdlib.dll" );

                                HalFLife2.m_pClient = (IBaseClientDLL*)*(DWORD*)ppClient;
                                Trace("Client: [0x%X]",dwClientDLL_Init);

                                DWORD* pdwClientVMT = (PDWORD)*(PDWORD)HalFLife2.m_pClient;
                                HalFLife2.m_pInput = (CInput*)*(DWORD*)*(DWORD*)(pdwClientVMT[21] + 0x28);
                                Trace("Input: [0x%x]",HalFLife2.m_pInput);

                                char szGlobals_Sig[] = "\xFF\xD6\xA1\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\x11\x83\xC4\x04\x68\x00\x00\x00\x00";
                                DWORD dwGlobals, dwGlobals_Mov = gMemoryTools.dwFindPattern( (DWORD)GetModuleHandleA("engine.dll"), dwEngine_Size, ( PBYTE )szGlobals_Sig, "xxx????xx????xxxxxx????" ) + 0x12;
                                PBYTE pbMov_Address = ( PBYTE )dwGlobals_Mov;
                                pbMov_Address = &pbMov_Address[1];
                                memcpy( (void*)&dwGlobals, pbMov_Address, 4 );
                                HalFLife2.m_pGlobals = ( CGlobalVarsBase* )dwGlobals;

                                HalFLife2.m_pCvar          = reinterpret_cast< ICvar* >( CaptureInterface( fnVStd, CVAR_INTERFACE_VERSION ) );


                                MathLib_Init();

                                ConnectTier1Libraries( &appSystemFactory, 1 );
                                ConnectTier2Libraries( &appSystemFactory, 1 );
                                ConnectTier3Libraries( &appSystemFactory, 1 );

                                if ( vgui::VGui_InitInterfacesList( "nego.dll", &appSystemFactory, 1 ) )
                                        Trace("VGUI Interfaces have Initialized correctly.");

                                if (HookAllInterfaces())
                                {
                                        Trace("HookAllInterfaces");
                                        DWORD dwOldProtect;
                                        DWORD* pdwPanelVMT = (PDWORD)*(PDWORD)HalFLife2.m_pPanel;
                                        DWORD* pdwRenderVMT = (PDWORD)*(PDWORD)HalFLife2.m_pRenderView;

                                        /*				if(VirtualProtect((LPVOID)((DWORD)pdwRenderVMT+(0x4*38)), 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
                                        {
                                        g_dwOrgPush3DView = pdwRenderVMT[38];
                                        pdwRenderVMT[38] = (DWORD)&new_Push3DView;
                                        VirtualProtect((LPVOID)((DWORD)pdwRenderVMT+(0x4*38) ), 4, dwOldProtect, &dwOldProtect);
                                        }*/

                                        if(VirtualProtect((LPVOID)((DWORD)pdwClientVMT), 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
                                        {
                                                g_dwOrgInit = pdwClientVMT[0];
                                                pdwClientVMT[0] = (DWORD)&new_Init;
                                                VirtualProtect((LPVOID)((DWORD)pdwClientVMT ), 4, dwOldProtect, &dwOldProtect);
                                        }

                                        if(VirtualProtect((LPVOID)((DWORD)pdwPanelVMT + (40*0x4)), 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
                                        {
                                                g_dwOrgPaintTraverse = pdwPanelVMT[40];
                                                pdwPanelVMT[40] = (DWORD)&new_PaintTraverse;
                                                VirtualProtect((LPVOID)((DWORD)pdwPanelVMT + (40*0x4)), 4, dwOldProtect, &dwOldProtect);
                                        }

                                        if(VirtualProtect((LPVOID)((DWORD)pdwClientVMT + (21*0x4)), 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
                                        {
                                                g_dwOrgCreateMove = pdwClientVMT[21];
                                                pdwClientVMT[21] = (DWORD)&new_CreateMove;
                                                VirtualProtect((LPVOID)((DWORD)pdwClientVMT + (21*0x4)), 4, dwOldProtect, &dwOldProtect);
                                        }

                                        if(VirtualProtect((LPVOID)((DWORD)pdwClientVMT + (35*0x4)), 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
                                        {
                                                g_dwOrgFrameStageNotify = pdwClientVMT[35];
                                                pdwClientVMT[35] = (DWORD)&new_FrameStageNotify;
                                                VirtualProtect((LPVOID)((DWORD)pdwClientVMT + (35*0x4)), 4, dwOldProtect, &dwOldProtect);
                                        }

                                        if(VirtualProtect((LPVOID)((DWORD)pdwClientVMT + (11*0x4)), 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))
                                        {
                                                g_dwOrgHudUpdate = pdwClientVMT[11];
                                                pdwClientVMT[11] = (DWORD)&new_HudUpdate;
                                                VirtualProtect((LPVOID)((DWORD)pdwClientVMT + (11*0x4)), 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
                                        }

                                }

                                HalFLife2.m_pAimbot = new cAimbot();
                                Trace("*****************************");

                        }
                }
                Sleep(250);
        }
        return TRUE;
}

long long
        timeval_diff(struct timeval *difference,
struct timeval *end_time,
struct timeval *start_time
        )
{
        struct timeval temp_diff;

        if(difference==NULL)
        {
                difference=&temp_diff;
        }

        difference->tv_sec =end_time->tv_sec -start_time->tv_sec ;
        difference->tv_usec=end_time->tv_usec-start_time->tv_usec;

        /* Using while instead of if below makes the code slightly more robust. */

        while(difference->tv_usec<0)
        {
                difference->tv_usec+=1000000;
                difference->tv_sec -=1;
        }

        return 1000000LL*difference->tv_sec+
                difference->tv_usec;

} /* timeval_diff() */

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
        Sleep(500);
        if(dwReason == DLL_PROCESS_ATTACH)
        {
                HideModule(hModule);
                //GetCDir(hModule);
                CreateThread(NULL, NULL, dwInitThread, NULL, NULL, NULL);
                return TRUE;
        }
        return FALSE;

}
