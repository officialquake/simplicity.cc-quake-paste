/*      backtrack.cpp
 *
 *
 *
 */

#include "main.h"
#include "backtrack.h"

C_Backtrack* backtrack = new C_Backtrack();

struct backtrack_info_t
{
    int tick_count;
    float lby;
    float sim_time;
    Vector head_pos;
    Vector position;
};

static array<array<backtrack_info_t, 12>, 64> info;

void C_Backtrack::store()
{
    if(!set.legit.backtrack)
        return;
    
    if(!Global::cmd || !Global::local)
        return;
    
    for(int i = 0; i < pGlobals->maxClients; i++)
    {
        C_BasePlayer* player = (C_BasePlayer*)pEntList->GetClientEntity(i);
        
        if(!player)
            continue;
        
        if(player == Global::local || player->GetTeam() == Global::local->GetTeam())
            continue;
        
        if(player->IsDormant() || player->IsImmune())
            continue;
        
        if(!player->IsAlive())
        {
            memset(info.at(i).data(), 0, sizeof(backtrack_info_t) * 12);
            continue;
        }
        
        backtrack_info_t new_record;
        new_record.tick_count   = pGlobals->tickcount;
        new_record.lby          = player->GetLowerBodyYaw();
        new_record.sim_time     = player->GetSimulationTime();
        new_record.head_pos     = get_hitbox_position(player, 1);
        new_record.position     = player->GetVecOrigin();
        
        info.at(i).at(Global::cmd->command_number % 12) = new_record;
    }
}

inline Vector angle_vectors(QAngle ang)
{
    auto sy = sin(ang.y / 180.f * static_cast<float>(M_PI));
    auto cy = cos(ang.y / 180.f * static_cast<float>(M_PI));
    
    auto sp = sin(ang.x / 180.f * static_cast<float>(M_PI));
    auto cp = cos(ang.x / 180.f * static_cast<float>(M_PI));
    
    return Vector(cp * cy, cp * sy, -sp);
}

inline float distance_to_point(Vector point, Vector origin, Vector dir)
{
    Vector pointDir = point - origin;
    
    float tempOffset = pointDir.Dot(dir) / (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (tempOffset < 0.000001f)
        return MAXFLOAT;
    
    Vector perpendicularPoint = origin + (dir * tempOffset);
    
    return (point - perpendicularPoint).Length();
}

static C_BasePlayer* find_target()
{
    C_BasePlayer* target = nullptr;
    
    float best_fov  = MAXFLOAT;
    
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
    
    return target;
}

void C_Backtrack::backtrack_player(C_BasePlayer* player)
{
    if(!set.legit.backtrack)
        return;
    
    if(!player)
        player = find_target();
    
    if(!player)
        return;
    
    if(!player->IsAlive())
        return;
    
    int best_tick       = -1;
    int index           = player->GetIndex();
    int update_tick     = -1;
    float best_dist     = MAXFLOAT;
    Vector view_dir     = angle_vectors(Global::cmd->viewangles + (*Global::local->GetAimPunchAngle() * 2));
    backtrack_info_t best_record;
    
    for(int i = 0; i < 12; i++)
    {
        auto record = info.at(index).at(i);
        float dist  = distance_to_point(record.head_pos, Global::local->GetEyePosition(), view_dir);
     
        if(i > 0 && info.at(index).at(i - 1).lby != record.lby)
            update_tick = i;
        
        if(dist < best_dist)
        {
            best_record = record;
            best_tick   = i;
        }
    }
    
    if(Global::cmd->buttons & IN_ATTACK)
        Global::cmd->tick_count = TIME_TO_TICKS(best_record.sim_time);
}

void C_Backtrack::draw(C_BasePlayer* player)
{
    for(int i = 0; i < 12; i++)
    {
        auto record = info.at(player->GetIndex()).at(i);
        
        Vector screen_pos;
        
        if(!world_to_screen(record.head_pos, screen_pos))
            continue;
        
        render->draw_box_filled(screen_pos.x, screen_pos.y, 2, 2, Color::Blue());
    }
}
