/*      visuals.cpp
 *
 *
 *
 */

#include "main.h"
#include "legit.h"
#include "visuals.h"
#include "backtrack.h"

C_Visuals* visuals = new C_Visuals();


/*
 *  draw_esp_box
 *  Draws an esp box
 */
void C_Visuals::draw_esp_box(int x, int y, int w, int h, Color col)
{
    render->draw_box(x - 1, y - 1, w + 2, h + 2, Color::Black());
    render->draw_box(x + 1, y + 1, w - 2, h - 2, Color::Black());
    render->draw_box(x, y, w, h, col);
}

/*
 *  draw_skeletom
 *  Draws the skeleton of the player
 */
void C_Visuals::draw_skeleton(C_BasePlayer* player)
{
    static matrix3x4_t matrix[128];
    studiohdr_t* pStudioModel = pModelInfo->GetStudioModel(player->GetModel());
    
    if (!pStudioModel)
        return;
    
    if (!player->SetupBones(matrix, 128, 256, 0))
        return;
    
    for (int i = 0; i < pStudioModel->numbones; i++)
    {
        mstudiobone_t* pBone = pStudioModel->pBone(i);
        
        if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
            continue;
        
        Vector vBone1 = player->GetBonePosition(i);
        Vector vBoneOut1;
        
        Vector vBone2 = player->GetBonePosition(pBone->parent);
        Vector vBoneOut2;
        
        if(world_to_screen(vBone1, vBoneOut1) && world_to_screen(vBone2, vBoneOut2))
        {
            render->draw_line(vBoneOut1.x, vBoneOut1.y, vBoneOut2.x, vBoneOut2.y, imvec_to_color(set.colors.skeleton));
        }
    }
}

/******************************** Other entity visuals ********************************/

/*
 *  draw_planted_bomb
 *  Draws bomb timer on the bomb
 */
void C_Visuals::draw_planted_bomb(C_BasePlantedC4* bomb)
{
    if(!bomb)
        return;
    
    if(!bomb->IsBombTicking())
        return;
    
    box_t box;
    
    if(!get_box(bomb, box))
        return;
    
    float flBlow    = bomb->GetBombTime();
    float bombTimer = flBlow - (pGlobals->interval_per_tick * Global::local->GetTickBase());
    
    char buffer[128];
    
    if((Global::local->HasDefuser() && flBlow < 5.25f) || (!Global::local->HasDefuser() && flBlow < 10.25f))
        sprintf(buffer, "No time %.f", bombTimer);
    
    if((Global::local->HasDefuser() && flBlow > 5.25f) || (!Global::local->HasDefuser() && flBlow > 10.25f))
        sprintf(buffer, "Bomb %.f", bombTimer);
    
    if (bomb->IsBombDefused() || !bomb->IsBombTicking() || bombTimer <= 0.f)
        sprintf(buffer, "Bomb");
    
    render->draw_string(box.x, box.y, buffer, Fonts::esp, Color::Magenta());
}

/*
 *  draw_dropped_weapons
 *  Draws dropped weapons that are within 15 meters
 */
void C_Visuals::draw_dropped_weapons(C_BaseCombatWeapon* weapon)
{
    if(!Global::local)
        return;
    
    int owner       = weapon->GetOwner();
    Vector vOrig    = weapon->GetVecOrigin();
    Vector localpos = Global::local->GetEyePosition();
    
    if (owner > -1 || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
        return;
    
    if(get_distance(vOrig, localpos) > 15)
        return;
    
    string model = get_weapon_name(weapon);
    int ammo     = weapon->GetAmmo();
    
    if (ammo > 0)
        model += " | " + to_string(ammo);
    
    box_t box;
    if(!get_box(weapon, box))
        return;
    
    render->draw_string(box.x + box.w / 2, box.y, model.c_str(), Fonts::esp, Color::White(), true);
}

/*
 *  draw_recoil_crosshair
 *  Draws a recoil crosshair
 */
void C_Visuals::draw_recoil_crosshair()
{
    if(!set.visuals.enabled || !set.visuals.recoil_crosshair)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    if(!Global::local)
        return;
    
    if(!Global::local->IsAlive())
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    int x = w / 2;
    int y = h / 2;
    
    QAngle punchAngles = *Global::local->GetAimPunchAngle();
    
    int dx = w / 90;
    int dy = h / 90;
    int X = x - (dx * punchAngles.y);
    int Y = y + (dy * punchAngles.x);
    
    render->draw_line(X - 5, Y, X + 5, Y, Color::White());
    render->draw_line(X, Y - 5, X, Y + 5, Color::White());
}

/*
 *  draw_player_esp
 *  Draws esp and visuals for each player
 */
void C_Visuals::draw_player_esp(C_BasePlayer* player)
{
    if(!player->IsAlive())
        return;
    
    if(player->IsDormant())
        return;
    
    int  team = player->GetTeam();
    bool visible = is_player_visible(player);
    
    if(set.visuals.visible_only && !visible)
        return;
    
    if(set.visuals.enemy_only && team == Global::local->GetTeam())
        return;
        
    ImColor imbox_col = visible ? set.colors.box_vis : set.colors.box_ign;
    Color white     = Color(255, 255, 255, 255);
    
    imbox_col.Value.w = 1.f;
    
    Color box_col = imvec_to_color(imbox_col);
    
    box_t box;
    
    if(!get_box(player, box))
        return;
    
    if(set.visuals.box)
        this->draw_esp_box(box.x, box.y, box.w, box.h, box_col);
    
    if(set.visuals.skeleton)
        this->draw_skeleton(player);
    
    string to_draw;
    
    if(set.visuals.name)
        to_draw = player->GetName();
    
    if(set.visuals.health)
    {
        if(set.visuals.name)
            to_draw += " / ";
        
        to_draw += to_string(player->GetHealth());
    }
    
    if(!to_draw.empty())
        render->draw_string(box.x + box.w / 2, box.y + box.h + 5, to_draw.c_str(), Fonts::esp, white, true);
    
    C_BasePlayer* target = (set.legit.enabled ? legit->target : nullptr);
    
    if(player == target)
        render->draw_string(box.x + box.w + 1, box.y, "T", Fonts::esp, white);
    
    if(set.visuals.weapon)
    {
        C_BaseCombatWeapon* weapon = get_active_weapon(player);
        
        Vector2D text_size = {0 , 0};
        
        if(!to_draw.empty())
            text_size = render->get_text_size(to_draw.c_str(), Fonts::esp);
        
        if(weapon)
            render->draw_string(box.x + (box.w / 2), box.y + box.h + text_size.y + 2, get_weapon_name(weapon).c_str(), Fonts::esp, white, true);
    }
    
    if(set.visuals.radar)
        *player->GetSpotted() = true;
    
    if(set.visuals.snap_lines)
    {
        int w, h;
        pEngine->GetScreenSize(w, h);
        render->draw_line(w / 2, h, box.x + (box.w / 2), box.y + box.h, imvec_to_color(set.colors.snap_lines));
    }
    
    if(set.visuals.backtrack)
        backtrack->draw(player);
}

/*
 *  draw_other_esp
 *  Draws esp for non player entities
 */
void C_Visuals::draw_other_esp(C_BaseEntity* entity)
{
    int class_id = entity->GetClientClass()->m_ClassID;
    
    if(set.visuals.bomb_timer && class_id == CPlantedC4)
        draw_planted_bomb((C_BasePlantedC4*)entity);
    
    if(set.visuals.dropped_weapons && class_id != CBaseWeaponWorldModel)
    {
        if (strstr(entity->GetClientClass()->m_pNetworkName, "Weapon") || class_id == CDEagle || class_id == CAK47)
            draw_dropped_weapons((C_BaseCombatWeapon*)entity);
    }
}

/*
 *  draw_esp
 *  Draws all esp, main loop
 */
void C_Visuals::draw_esp()
{
    if(!set.visuals.enabled)
        return;
    
    if(!Global::local)
        return;
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        C_BaseEntity* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity->IsPlayer())
            this->draw_player_esp((C_BasePlayer*)entity);
        else
            this->draw_other_esp(entity);
    }
}
