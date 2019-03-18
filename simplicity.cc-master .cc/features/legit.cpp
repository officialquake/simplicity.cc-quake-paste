/*      aim.cpp
 *
 *
 *
 */

#include "main.h"
#include "legit.h"

C_Legit* legit = new C_Legit();

/*
 *  distance_between
 *  Returns the distance between two vectors
 */
static inline float distance_between(Vector a, Vector b)
{
    return sqrt( pow( a.x - b.x, 2 ) + pow( a.y - b.y, 2 ) + pow( a.z - b.z, 2 ) );
}

/*
 *  find_target
 *  Looks for an aimbot target
 */
void C_Legit::find_target()
{
    float best_fov = MAXFLOAT;
    
    for(int i = 0; i < pGlobals->maxClients; i++)
    {
        C_BasePlayer* player = (C_BasePlayer*)pEntList->GetClientEntity(i);
        
        if(!player)
            continue;
        
        if(player == Global::local)
            continue;
        
        if(player->GetTeam() == Global::local->GetTeam())
            continue;
        
        if(!player->IsAlive() || !player->IsPlayer() || player->IsDormant() || player->IsImmune())
            continue;
        
        Vector hitbox_pos   = get_hitbox_position(player, 1) + (player->GetVelocity() * pGlobals->interval_per_tick);
        QAngle aim_ang      = calculate_angle(Global::local->GetEyePosition(), hitbox_pos);
        float fov           = get_fov(Global::cmd->viewangles, aim_ang);
        
        if(fov < best_fov)
        {
            target   = player;
            best_fov = fov;
        }
    }
}

/*
 *  get_best_hitbox
 *  Returns the closest hitbox to the crosshair
 */
int C_Legit::get_best_hitbox()
{
    int best_hitbox = -1;
    float best_fov = MAXFLOAT;
    
    for(int i = 0; i < HITBOX_TOTAL; i++)
    {
        Vector hitbox_pos   = get_hitbox_position(target, i);
        QAngle aim_ang      = calculate_angle(Global::local->GetEyePosition(), hitbox_pos);
        float fov           = get_fov(Global::cmd->viewangles, aim_ang);
        
        if(!is_hitbox_visible(target, i))
            continue;
        
        if(fov < best_fov)
        {
            best_fov = fov;
            best_hitbox = i;
        }
    }
    
    return best_hitbox;
}

/*
 *  aimbot
 *  Runs the legit aimbot
 */
void C_Legit::aimbot()
{
    if(!set.legit.enabled)
        return;
    
    if(!Global::local->IsAlive())
        return;
    
    if(!Global::weapon->CanShoot())
        return;
    
    if(Global::weapon->IsBomb() || Global::weapon->IsKnife() || Global::weapon->IsGrenade())
        return;

    this->find_target();
    
    if(!this->target)
        return;
    
    int hitbox = get_best_hitbox();
    
    if(hitbox == -1)
        return;
    
    Vector hitbox_pos   = get_hitbox_position(target, hitbox) + (target->GetVelocity() * pGlobals->interval_per_tick);
    QAngle aim_ang      = calculate_angle(Global::local->GetEyePosition(), hitbox_pos);
    
    if(get_fov(Global::cmd->viewangles, aim_ang) > set.legit.fov)
        return;
    
    if(set.legit.smoothing)
        smooth_angle(aim_ang);
    
    if(Global::cmd->buttons & IN_ATTACK)
    {
        Global::cmd->viewangles = aim_ang;
        pEngine->SetViewAngles(Global::cmd->viewangles);
    }
}








