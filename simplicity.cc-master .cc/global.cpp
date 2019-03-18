/*      global.cpp
 *
 *
 *
 */
#include "main.h"

namespace Global
{
    bool*               send_packet;
    array<QAngle, 2>    angles;
    CUserCmd*           cmd;
    C_BasePlayer*       local;
    C_BaseCombatWeapon* weapon;
}

C_Settings  set;
C_Renderer* render = new C_Renderer();

/*
 *  Interfaces
 */
ICvar*              pCvar;
IPanel*             pPanel;
ISurface*           pSurface;
IBaseClientDLL*     pClient;
IClientEntityList*  pEntList;
IVDebugOverlay*     pOverlay;
IEngineClient*      pEngine;
IVModelInfo*        pModelInfo;
IEngineTrace*       pEngineTrace;
IClientMode*        pClientMode;
CGlobalVarsBase*    pGlobals;
IInputSystem*       pInputSystem;
CInput*             pInput;
IMaterialSystem*    pMatSystem;
IVModelRender*      pModelRender;
IPrediction*        pPrediction;
IGameMovement*      pGameMovement;
IMoveHelper*        pMoveHelper;
IPhysicsSurfaceProps*pPhysics;
CMoveData*          pMoveData;

/*
 *  Game Functions
 */
SendClanTagFn         SetClanTagFunc;
ServerRankRevealAllFn ServerRankRevealAllFunc;
RandomIntFn           RandomInt;
RandomSeedFn          RandomSeed;
RandomFloatFn         RandomFloat;

/*
 *  VMT
 */
VMT* paintVMT;
VMT* createmoveVMT;
VMT* clientVMT;
VMT* modelVMT;
VMT* materialVMT;
VMT* predictionVMT;
VMT* surfaceVMT;
VMT* sdlVMT;
