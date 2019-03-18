/*
 *  hooks.h
 */
#pragma once

typedef void (*oPaintTraverse)          (void*, VPANEL, bool, bool);
typedef bool (*oCreateMove)             (void*, float, CUserCmd*);
typedef void (*oFrameStage)             (void*, ClientFrameStage_t);
typedef int  (*oKeyEvent)               (void*, int, int, const char*);
typedef void (*oOverrideView)           (void*, CViewSetup&);
typedef void (*oDrawModelExecute)       (void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
typedef float(*GetViewModelFOVFn)       (void*);
typedef void (*LockCursorFn)            (void*);
typedef int  (*PumpWindowMessageLoopFn) (void*);
typedef void (*PostScreenSpaceEffectsFn)(void*, CViewSetup*);

typedef void(*oPaintTraverse)   (void*, VPANEL panel, bool forceRepaint, bool allowForce);
typedef bool(*oCreateMove)      (void*, float flSampleInput, CUserCmd* cmd);
typedef int (*oKeyEvent)        (void*, int, int, const char*);
typedef void(*oFrameStage)      (void*, ClientFrameStage_t);
typedef void(*oDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);
typedef void(*oOverrideView)    (void*, CViewSetup& setup);
typedef float(*oGetViewModelFOV)(void*);
typedef void(*oLockCursor)      (void*);


void    hkPaintTraverse(void* thisptr, VPANEL thisPanel, bool forceRepaint, bool allowForce);
bool    hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd);
void    hkFrameStage(void* thisptr, ClientFrameStage_t curStage);
int     hkKeyEvent(void* thisptr, int eventcode, int keycode, const char* currentbinding);
void    hkOverrideView(void* thisptr, CViewSetup& setup);
void    hkDrawModelExecute(void* thisptr, void* context, void* state, ModelRenderInfo_t& model_info, matrix3x4_t* pCustomBoneToWorld);
float   hkGetViewModelFOV(void* thisptr);
void    hkOpenGL();
void    hkLockCursor(void* thisptr);
void    hkPumpWindowMessageLoop(void* thisptr);
