/*      OtherHooks.cpp
 *
 *
 *
 */

#include "main.h"
#include "misc.h"

/*
 *  hkOverrideView
 */
void hkOverrideView(void* thisptr, CViewSetup& setup)
{
    if(set.misc.fov_changer && set.misc.fov > 0)
    {
        if(Global::local && !Global::local->IsScoped())
        {
            setup.fov += set.misc.fov;
        }
    }
    
    createmoveVMT->GetOriginalMethod<oOverrideView>(19)(thisptr, setup);
}

/*
 *  hkGetViewModelFOV
 */
float hkGetViewModelFOV(void* thisptr)
{
    float fov = createmoveVMT->GetOriginalMethod<oGetViewModelFOV>(36)(thisptr);
    
    misc->change_view_model(fov);
    
    return fov;
}

/*
 *  hkLockCursor
 */
void hkLockCursor(void* thisptr)
{
    if(set.menu)
    {
        pSurface->UnlockCursor();
    }
    else
    {
        surfaceVMT->GetOriginalMethod<oLockCursor>(67)(thisptr);
    }
}
