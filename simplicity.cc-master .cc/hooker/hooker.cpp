/*      hooker
 *
 *
 *
 */
#include "main.h"
#include "config.h"
#include "hooker.h"

void init_interfaces()
{
    pSurface        = GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    pPanel          = GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    pCvar           = GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    pClient         = GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client_panorama.dylib", "VClient");
    pEngine         = GetInterface<IEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    pEntList        = GetInterface<IClientEntityList>("./csgo/bin/osx64/client_panorama.dylib", "VClientEntityList");
    pOverlay        = GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay");
    pEngineTrace    = GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient");
    pModelInfo      = GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
    pInputSystem    = GetInterface<IInputSystem>("./bin/osx64/inputsystem.dylib", "InputSystemVersion");
    pModelRender    = GetInterface<IVModelRender>("./bin/osx64/engine.dylib", "VEngineModel");
    pMatSystem      = GetInterface<IMaterialSystem>("./bin/osx64/materialsystem.dylib", "VMaterialSystem");
    pPrediction     = GetInterface<IPrediction>("./csgo/bin/osx64/client_panorama.dylib", "VClientPrediction");
    pGameMovement   = GetInterface<IGameMovement>("./csgo/bin/osx64/client_panorama.dylib", "GameMovement");
    pPhysics        = GetInterface<IPhysicsSurfaceProps>("./bin/osx64/vphysics.dylib", "VPhysicsSurfaceProps");
}

/*
 *
 *
 */
void protect_addr(void* addr, int prot)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    void* address = (void*)((long)(uintptr_t)addr & ~(pagesize - 1));
    mprotect(address, sizeof(address), prot);
}

void init_hooks()
{
    C_PatternScanner* scan      = C_PatternScanner::get();
    uintptr_t client_mode_ptr   = scan->get_pointer("client_panorama.dylib",    CLIENTMODE_SIG,   CLIENTMODE_MASK,      0xA)    + 0x4;
    uintptr_t global_vars_ptr   = scan->get_pointer("client_panorama.dylib",    GLOBALS_SIG,      GLOBALS_MASK,         0x3)    + 0x4;
    uintptr_t rank_reveal_ptr   = scan->get_pointer("client_panorama.dylib",    RANKREVEAL_SIG,   RANKREVEAL_MASK,      0x15)   + 0x4;
    uintptr_t clan_tag_ptr      = scan->get_pointer("engine.dylib",             CLANTAG_SIG,      CLANTAG_MASK,         0xB)    + 0x4;
    uintptr_t send_packet_ptr   = scan->get_procedure("engine.dylib",           SENDPACKET_SIG,   SENDPACKET_MASK,      0x1)    + 0x2;
    
    Global::send_packet = reinterpret_cast<bool*>(send_packet_ptr);
    protect_addr(Global::send_packet, PROT_READ | PROT_WRITE | PROT_EXEC);
    
    
    void* handle        = dlopen("./csgo/bin/osx64/client_panorama.dylib", RTLD_NOLOAD | RTLD_NOW);
    RandomInt           = reinterpret_cast<RandomIntFn>          (dlsym(handle, "RandomInt"));
    RandomSeed          = reinterpret_cast<RandomSeedFn>         (dlsym(handle, "RandomSeed"));
    RandomFloat         = reinterpret_cast<RandomFloatFn>        (dlsym(handle, "RandomFloat"));
    dlclose(handle);
    
    
    pGlobals                = *reinterpret_cast<CGlobalVarsBase**>(global_vars_ptr);
    pClientMode             = reinterpret_cast<IClientMode*>(client_mode_ptr);
    
    
    SetClanTagFunc          = reinterpret_cast<SendClanTagFn>(clan_tag_ptr);
    ServerRankRevealAllFunc = reinterpret_cast<ServerRankRevealAllFn>(rank_reveal_ptr);
    
    
    paintVMT        = new VMT(pPanel);
    createmoveVMT   = new VMT(pClientMode);
    clientVMT       = new VMT(pClient);
    surfaceVMT      = new VMT(pSurface);
    modelVMT        = new VMT(pModelRender);
    predictionVMT   = new VMT(pPrediction);
    materialVMT     = new VMT(pMatSystem);
}

void hook_functions()
{
    paintVMT->HookVM((void*)hkPaintTraverse, INDEX_PAINTTRAVERSE);
    paintVMT->ApplyVMT();
    
    createmoveVMT->HookVM((void*)hkCreateMove, INDEX_CREATEMOVE);
    createmoveVMT->HookVM((void*)hkOverrideView, INDEX_OVERRIDEVIEW);
    createmoveVMT->HookVM((void*)hkGetViewModelFOV, INDEX_GETVIEWMODELFOV);
    createmoveVMT->ApplyVMT();
    
    clientVMT->HookVM((void*)hkKeyEvent, INDEX_INKEYEVENT);
    clientVMT->HookVM((void*)hkFrameStage, INDEX_FRAMESTAGENOTIFY);
    clientVMT->ApplyVMT();
    
    modelVMT->HookVM((void*)hkDrawModelExecute, INDEX_DRAWMODELEXECUTE);
    modelVMT->ApplyVMT();
    
    surfaceVMT->HookVM((void*)hkLockCursor, INDEX_LOCKCURSOR);
    surfaceVMT->ApplyVMT();
    
    hkOpenGL();
}

void init_settings()
{
    
}

void unload_cheat()
{
    set.menu = false;
    
    paintVMT        ->ReleaseVMT();
    createmoveVMT   ->ReleaseVMT();
    clientVMT       ->ReleaseVMT();
    modelVMT        ->ReleaseVMT();
    predictionVMT   ->ReleaseVMT();
    sdlVMT          ->ReleaseVMT();
    
    delete(paintVMT);
    delete(createmoveVMT);
    delete(clientVMT);
    delete(modelVMT);
    delete(predictionVMT);
    delete(sdlVMT);
}
