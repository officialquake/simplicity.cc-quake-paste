/*      misc.cpp
 *
 *  - autoDefuse
 *
 */

#include "main.h"
#include "misc.h"

C_Misc* misc = new C_Misc();

/*
 *  show_ranks
 *  Shows users ranks in the scoreboard
 */
void C_Misc::show_ranks()
{
    if (!set.misc.show_ranks)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    if (!(Global::cmd->buttons & IN_SCORE))
        return;
    
    float input[3] = { 0.f };
    ServerRankRevealAllFunc(input);
}

/*
 *  fake_lag
 *  Chokes packets to emulate lag
 */
void C_Misc::fake_lag()
{
    /*
    if(!set.misc.fake_lag)
        return;
    
    if(!Global::local)
        return;
    
    if(!Global::local->IsAlive())
        return;
    
    if(Global::local->GetFlags() & FL_ONGROUND && set.misc.fake_lag_factor == 1) // adaptive
        return;
    
    if(Global::cmd->buttons & IN_ATTACK)
    {
        *Global::send_packet = true;
        return;
    }
    
    static int tick;
    if (++tick >= 16)
        tick = 0;

    *Global::send_packet = tick < 16 - set.misc.fake_lag_factor;
    */
}

/*
 *  remove_flash
 *  Removes flash
 */
void C_Misc::remove_flash(ClientFrameStage_t stage)
{
    if(!Global::local)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    *Global::local->GetFlashMaxAlpha() = set.misc.remove_flash ? 255.f - set.misc.flash_alpha : 255.f;
}

/*
 *  remove_smoke
 *  Removes smoke particles
 */
void C_Misc::remove_smoke(ClientFrameStage_t stage)
{
    if(!pEngine->IsInGame())
        return;
    
    static bool done;
    static bool last_setting;
    
    const vector<const char*> smoke_materials =
    {
        "particle/beam_smoke_01",
        "particle/particle_smokegrenade",
        "particle/particle_smokegrenade1",
        "particle/particle_smokegrenade2",
        "particle/particle_smokegrenade3",
        "particle/particle_smokegrenade_sc",
        "particle/smoke1/smoke1",
        "particle/smoke1/smoke1_ash",
        "particle/smoke1/smoke1_nearcull",
        "particle/smoke1/smoke1_nearcull2",
        "particle/smoke1/smoke1_snow",
        "particle/smokesprites_0001",
        "particle/smokestack",
        "particle/vistasmokev1/vistasmokev1",
        "particle/vistasmokev1/vistasmokev1_emods",
        "particle/vistasmokev1/vistasmokev1_emods_impactdust",
        "particle/vistasmokev1/vistasmokev1_fire",
        "particle/vistasmokev1/vistasmokev1_nearcull",
        "particle/vistasmokev1/vistasmokev1_nearcull_fog",
        "particle/vistasmokev1/vistasmokev1_nearcull_nodepth",
        "particle/vistasmokev1/vistasmokev1_smokegrenade",
        "particle/vistasmokev1/vistasmokev4_emods_nocull",
        "particle/vistasmokev1/vistasmokev4_nearcull",
        "particle/vistasmokev1/vistasmokev4_nocull"
    };
    
    if(!done)
    {
        for(auto material : smoke_materials)
        {
            IMaterial* mat = pMatSystem->FindMaterial(material, TEXTURE_GROUP_OTHER);
            mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, set.misc.remove_smoke);
        }
        
        done = true;
    }
    
    if(last_setting != set.misc.remove_smoke)
    {
        last_setting = set.misc.remove_smoke;
        done = false;
    }
}

/*
 *  clan_tag
 *  Clan tag spammer
 */
void C_Misc::clan_tag()
{
    if(!set.misc.clan_tag)
        return;
    
    if(!Global::local->IsAlive())
        SetClanTagFunc("simplicity", "simplicity.cc");
    
    static int ticks = 0; ticks++;
    
    if(ticks > 0 && ticks < 15)
    {
        SetClanTagFunc("             ", "simplicity.cc");
    }
    else if(ticks > 30 && ticks < 45)
    {
        SetClanTagFunc("            s", "simplicity.cc");
    }
    else if(ticks > 60 && ticks < 75)
    {
        SetClanTagFunc("           si", "simplicity.cc");
    }
    else if(ticks > 90 && ticks < 105)
    {
        SetClanTagFunc("          sim", "simplicity.cc");
    }
    else if(ticks > 120 && ticks < 135)
    {
        SetClanTagFunc("        simp", "simplicity.cc");
    }
    else if(ticks > 150 && ticks < 165)
    {
        SetClanTagFunc("        simpl", "simplicity.cc");
    }
    else if(ticks > 180 && ticks < 195)
    {
        SetClanTagFunc("       simpli", "simplicity.cc");
    }
    else if(ticks > 210 && ticks < 225)
    {
        SetClanTagFunc("      simplic", "simplicity.cc");
    }
    else if(ticks > 240 && ticks < 255)
    {
        SetClanTagFunc("     simplici", "simplicity.cc");
    }
    else if(ticks > 270 && ticks < 285)
    {
        SetClanTagFunc("    simplicit", "simplicity.cc");
    }
    else if(ticks > 300 && ticks < 315)
    {
        SetClanTagFunc("   simplicity", "simplicity.cc");
    }
    else if(ticks > 330 && ticks < 345)
    {
        SetClanTagFunc("  simplicity.", "simplicity.cc");
    }
    else if(ticks > 360 && ticks < 375)
    {
        SetClanTagFunc(" simplicity.c", "simplicity.cc");
    }
    else if(ticks > 390 && ticks < 405)
    {
        SetClanTagFunc("simplicity.cc", "simplicity.cc");
    }
    else if(ticks > 420 && ticks < 435)
    {
        SetClanTagFunc("implicity.cc ", "simplicity.cc");
    }
    else if(ticks > 450 && ticks < 465)
    {
        SetClanTagFunc("mplicity.cc  ", "simplicity.cc");
    }
    else if(ticks > 450 && ticks < 495)
    {
        SetClanTagFunc("plicity.cc   ", "simplicity.cc");
    }
    else if(ticks > 480 && ticks < 525)
    {
        SetClanTagFunc("licity.cc    ", "simplicity.cc");
    }
    else if(ticks > 510 && ticks < 555)
    {
        SetClanTagFunc("icity.cc     ", "simplicity.cc");
    }
    else if(ticks > 540 && ticks < 585)
    {
        SetClanTagFunc("city.cc      ", "simplicity.cc");
    }
    else if(ticks > 570 && ticks < 615)
    {
        SetClanTagFunc("ity.cc       ", "simplicity.cc");
    }
    else if(ticks > 600 && ticks < 645)
    {
        SetClanTagFunc("ty.cc        ", "simplicity.cc");
    }
    else if(ticks > 630 && ticks < 675)
    {
        SetClanTagFunc("y.cc         ", "simplicity.cc");
    }
    else if(ticks > 660 && ticks < 705)
    {
        SetClanTagFunc(".cc          ", "simplicity.cc");
    }
    else if(ticks > 690 && ticks < 735)
    {
        SetClanTagFunc("cc           ", "simplicity.cc");
    }
    else if(ticks > 720 && ticks < 765)
    {
        SetClanTagFunc("c            ", "simplicity.cc");
    }    
    
    if (ticks >= 765)
        ticks = 0;
}

/*
 *  change_view_model
 *  Changes the players view model FOv
 */
void C_Misc::change_view_model(float& fov)
{
    if(!set.misc.view_changer)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    C_BasePlayer* local = Global::local;
    
    if(!local)
        return;
    
    if(!local->IsAlive())
    {
        if (*local->GetObserverMode() == OBS_MODE_IN_EYE && local->GetObserverTarget())
            local = (C_BasePlayer*)pEntList->GetClientEntityFromHandle(local->GetObserverTarget());
        
        if(!local)
            return;
    }
    
    if(!local->IsScoped())
        fov = set.misc.view_fov * 2;
}

/*
 *  bhop
 *  Bunny hop
 *  Todo : chance
 */
void C_Misc::bhop()
{
    if(!set.misc.bhop)
        return;
 
    static bool jump[2] = { false, false };
    
    if(jump[0] && !jump[1])
    {
        Global::cmd->buttons |= IN_JUMP;
        jump[0] = false;
    }
    else if(Global::cmd->buttons & IN_JUMP)
    {
        if (Global::local->GetFlags() & FL_ONGROUND)
        {
            jump[0] = false;
            jump[1] = false;
        }
        else
        {
            Global::cmd->buttons &= ~IN_JUMP;
            jump[1] = false;
        }
    }
    else
    {
        jump[1] = false;
        jump[0] = false;
    }
}

/*
 *  auto_strafe
 *  Automatically strafes when jumping
 */
void C_Misc::auto_strafe()
{
    if(!set.misc.auto_strafe)
        return;
    
    if (!(Global::cmd->buttons & IN_JUMP) && Global::local->GetFlags() & FL_ONGROUND)
        return;
    
    if (Global::local->GetVelocity().Length2D() == 0 && (Global::cmd->forwardmove == 0 && Global::cmd->sidemove == 0))
    {
        Global::cmd->forwardmove = 450.f;
    }
    else if (Global::cmd->forwardmove == 0 && Global::cmd->sidemove == 0)
    {
        if (Global::cmd->mousedx > 0 || Global::cmd->mousedx < -0)
        {
            Global::cmd->sidemove = Global::cmd->mousedx < 0.f ? -450.f : 450.f;
        }
        else
        {
            float _temp = 5850.f / Global::local->GetVelocity().Length2D();
            Global::cmd->forwardmove = clamp(_temp, 0, 450);
            float temp = clamp((450 - (_temp - Global::cmd->forwardmove)), 0, 450);
            Global::cmd->sidemove = (Global::cmd->command_number % 2) == 0 ? -temp : temp;
        }
    }
}





