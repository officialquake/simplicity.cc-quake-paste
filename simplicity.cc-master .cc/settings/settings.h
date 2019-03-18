/*
 *  settings.h
 */
#pragma once

#include "imgui.h" // ImVec4

struct C_Settings
{
    bool menu = false;
    
    struct
    {
        bool enabled        = false;
        
        bool flash_check    = false;
        
        int fov             = 0;
        
        bool backtrack      = false;
        
        bool  smoothing     = false;
        int   smooth_factor = 0.f;
        
        bool  recoil_control= false;
        int   rcs_factor    = 0.f;
        
    }legit;
    
    struct
    {
        bool enabled        = false;
        bool visible_only   = false;
        bool enemy_only     = false;
        
        bool box            = false;
        bool name           = false;
        bool health         = false;
        bool weapon         = false;
        bool radar          = false;
        bool skeleton       = false;
        bool snap_lines     = false;
        bool backtrack      = false;
        bool chams          = false;
        int  chams_type     = 0;
        
        bool bomb_timer     = false;
        bool dropped_weapons= false;
        
        bool recoil_crosshair = false;
        
    }visuals;
    
    struct
    {
        bool bhop           = false;
        bool auto_strafe    = false;
        
        bool fov_changer    = false;
        int  fov            = 0;
        bool view_changer   = false;
        int  view_fov       = 0;
        
        bool show_ranks     = false;
        bool clan_tag       = false;
        
        bool remove_flash   = false;
        int  flash_alpha    = 0;
        
        bool remove_smoke   = false;
        bool remove_vrecoil = false; 
        
    }misc;
    
    struct
    {
        ImVec4 box_vis      = {1, 1, 1, 1};
        ImVec4 box_ign      = {1, 1, 1, 1};
        ImVec4 chams_vis    = {1, 1, 1, 1};
        ImVec4 chams_ign    = {1, 1, 1, 1};
        ImVec4 skeleton     = {1, 1, 1, 1};
        ImVec4 snap_lines   = {1, 1, 1, 1};
    }colors;
    
    struct
    {
        
    }keys;
    
};
