/*      CreateMove.cpp
 *
 *
 *
 */
#include "main.h"
#include "misc.h"
#include "legit.h"
#include "backtrack.h"

bool hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd)
{
    IMPL_HOOK("CreateMove");
    
    createmoveVMT->GetOriginalMethod<oCreateMove>(25)(thisptr, flSampleInput, cmd);
    
    if(!cmd)
        return false;
    
    if(!cmd->command_number)
        return false;
    
    Global::local = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!Global::local)
        return false;
    
    Global::weapon = get_active_weapon(Global::local);
    
    if(!Global::weapon)
        return false;
    
    Global::cmd = cmd;
    
    QAngle original_angles = cmd->viewangles;
    float forward   = cmd->forwardmove;
    float sidemove  = cmd->sidemove;
    float upmove    = cmd->upmove;
    static int choked_ticks = 0;
    
    {
        misc->clan_tag();
        
        misc->show_ranks();
        
        if(Global::local->IsAlive())
        {            
            misc->bhop();
            
            misc->auto_strafe();
            
            legit->aimbot();
            
            legit->recoil_control();
            
            C_BasePlayer* backtrack_target = (set.legit.enabled ? legit->target : nullptr);
            
            backtrack->backtrack_player(backtrack_target);
        }
    }
    
    
    /*
     *  Clamp everything
     */
    fix_movement(original_angles, cmd);
    clamp_moves(forward, sidemove, upmove);
    cmd->viewangles.ClampAngles();
    
    Global::angles.at(*Global::send_packet) = cmd->viewangles;
    
    if(*Global::send_packet)
        choked_ticks = 0;
    else
        choked_ticks++;
    
    if(choked_ticks > 14)
        *Global::send_packet = true;
    
    return false;
}
