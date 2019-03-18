/*      FrameStage.cpp
 *
 *
 *
 */
#include "main.h"
#include "misc.h"
#include "backtrack.h"

void hkFrameStage(void* thisptr, ClientFrameStage_t stage)
{
    IMPL_HOOK("FrameStageNotify");
    
    QAngle original_punch, orignal_view;
    
    if(stage == FRAME_RENDER_START)
    {
        if(Global::local)
        {
            if(!Global::local->IsAlive())
                *Global::send_packet = true;
            
            if(Global::local->IsAlive())
            {
                if(set.misc.remove_vrecoil)
                {
                    orignal_view   = *Global::local->GetViewPunchAngle();
                    original_punch = *Global::local->GetAimPunchAngle();
                    
                    Global::local->GetAimPunchAngle()->Init();
                    Global::local->GetViewPunchAngle()->Init();
                }
            }
        }
    }
    
    clientVMT->GetOriginalMethod<oFrameStage>(37)(thisptr, stage);
    
    if(stage == FRAME_NET_UPDATE_END)
    {
        
    }
    
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
    {
        misc->remove_flash(stage);
        
        backtrack->store();
    }
    
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_END)
    {
        misc->remove_smoke(stage);
    }
    
    if(set.misc.remove_vrecoil)
    {
        *Global::local->GetAimPunchAngle()   = original_punch;
        *Global::local->GetViewPunchAngle()  = orignal_view;
    }
}
