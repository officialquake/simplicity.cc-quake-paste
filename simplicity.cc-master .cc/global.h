/*
 *  global.h
 */
#pragma once

namespace Global
{
    extern bool*                send_packet;
    extern array<QAngle, 2>     angles;
    extern CUserCmd*            cmd;
    extern C_BasePlayer*        local;
    extern C_BaseCombatWeapon*  weapon;
}

extern C_Settings  set;
extern C_Renderer* render;


extern ICvar*               pCvar;
extern IPanel*              pPanel;
extern ISurface*            pSurface;
extern IBaseClientDLL*      pClient;
extern IClientEntityList*   pEntList;
extern IVDebugOverlay*      pOverlay;
extern IEngineClient*       pEngine;
extern IVModelInfo*         pModelInfo;
extern IEngineTrace*        pEngineTrace;
extern IClientMode*         pClientMode;
extern CGlobalVarsBase*     pGlobals;
extern IInputSystem*        pInputSystem;
extern CInput*              pInput;
extern IMaterialSystem*     pMatSystem;
extern IVModelRender*       pModelRender;
extern IPrediction*         pPrediction;
extern IGameMovement*       pGameMovement;
extern IMoveHelper*         pMoveHelper;
extern IPhysicsSurfaceProps*pPhysics;
extern CMoveData*           pMoveData;


extern SendClanTagFn         SetClanTagFunc;
extern ServerRankRevealAllFn ServerRankRevealAllFunc;


extern RandomIntFn           RandomInt;
extern RandomSeedFn          RandomSeed;
extern RandomFloatFn         RandomFloat;


extern VMT* paintVMT;
extern VMT* createmoveVMT;
extern VMT* clientVMT;
extern VMT* modelVMT;
extern VMT* materialVMT;
extern VMT* predictionVMT;
extern VMT* surfaceVMT;
extern VMT* sdlVMT;


extern void unload_cheat();




#define INDEX_PAINTTRAVERSE             42
#define INDEX_FRAMESTAGENOTIFY          37
#define INDEX_INKEYEVENT                21
#define INDEX_HUDUPDATE                 11
#define INDEX_DRAWMODELEXECUTE          21
#define INDEX_OVERRIDEVIEW              19
#define INDEX_GETVIEWMODELFOV           36
#define INDEX_CREATEMOVE                25
#define INDEX_FIREEVENT                 9
#define INDEX_ONSCREENSIZECHANGED       116
#define INDEX_OVERRIDECONFIG            21
#define INDEX_SHOWPIXELS                14
#define INDEX_PUMPWINDOWSMESSAGELOOP    19
#define INDEX_GETEVENTS                 12
#define INDEX_SETKEYCODESTATE           92
#define INDEX_SETMOUSECODESTATE         93
#define INDEX_EMITSOUND                 6
#define INDEX_DOPOSTSCREENSPACEEFFECTS  45
#define INDEX_READPACKET                18
#define INDEX_SCENEEND                  9
#define INDEX_LOCKCURSOR                67
#define INDEX_HUDPROCESSINPUT           10
#define INDEX_IN_ACTIVATEMOUSE          16
#define INDEX_GETLOCALPLAYER            12
#define INDEX_BEGINFRAME                42
