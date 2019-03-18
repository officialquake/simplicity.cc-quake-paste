/*      menu.cpp
 *
 *
 *
 */

#include "menu.h"
#include "config.h"
#include "settings.h"

q_menu* menu = new q_menu();


enum MenuItemSide
{
    Left  = 1,
    Right = 2
};

q_menu::~q_menu()
{
    delete draw;
}

void q_menu::init()
{
    draw = new C_ImRenderer();
    
    draw->init_fonts();
    
    config->init();
    
    move_height = 10;
    x = 200;
    y = 200;
    tab = 2;
}

void q_menu::display()
{
    draw->start();
    
    draw->draw_box(x - 7, y - 7, w + 14, h + 14, ImColor(9, 9, 9, 255));
    draw->draw_box(x - 6, y - 6, w + 12, h + 12, ImColor(60, 60, 60, 255));
    draw->draw_box(x - 5, y - 5, w + 10, h + 10, ImColor(40, 40, 40, 255));
    draw->draw_box(x - 4, y - 4, w +  8, h +  8, ImColor(40, 40, 40, 255));
    draw->draw_box(x - 3, y - 3, w +  6, h +  6, ImColor(40, 40, 40, 255));
    draw->draw_box(x - 2, y - 2, w +  4, h +  4, ImColor(60, 60, 60, 255));
    draw->draw_box_outlined(x, y, w, h, 1, ImColor(15, 15, 15, 255), ImColor(15, 15, 15, 255));
    
    draw->draw_box_gradient(x + 2,         y + 2, w / 2,     1, ImColor(37, 178, 214, 255), ImColor(208, 73, 198, 255), 1);
    draw->draw_box_gradient(x + 2 + w / 2, y + 2, w / 2 - 4, 1, ImColor(208, 73, 198, 255), ImColor(203, 226, 90, 255), 1);
    
    render_tabs();
    
    offset.clear();
    offset.resize(2);
    
    if(tab == 0)
        render_legit();
    
    if(tab == 1)
        render_visuals();
    
    if(tab == 2)
        render_misc();
    
    if(tab == 3)
        render_players();
    
    draw->finish();
    
    move();
}

void q_menu::render_tabs()
{
    ImColor active      = ImColor(225, 225, 225, 255);
    ImColor inactive    = ImColor(80, 80, 80, 255);
    
    bool clicked = ImGui::GetIO().MouseClicked[0];
    
    draw->draw_string(x + 15, y + 20, "LEGIT",      Fonts::impact, tab == 0 ? active : inactive);
    draw->draw_string(x + 15, y + 45, "VISUALS",    Fonts::impact, tab == 1 ? active : inactive);
    draw->draw_string(x + 15, y + 70, "MISC",       Fonts::impact, tab == 2 ? active : inactive);
    draw->draw_string(x + 15, y + 95, "COLORS",     Fonts::impact, tab == 3 ? active : inactive);
    
    if(q_in_area(x + 15, y + 23, 85, 20) && clicked)
        tab = 0;
    
    if(q_in_area(x + 15, y + 48, 85, 20) && clicked)
        tab = 1;
    
    if(q_in_area(x + 15, y + 73, 85, 20) && clicked)
        tab = 2;
    
    if(q_in_area(x + 15, y + 98, 85, 20) && clicked)
        tab = 3;
    
    if(q_in_area(x + 15, y + 123, 85, 20) && clicked)
        tab = 4;
}

void q_menu::render_legit()
{
    render_section(x + 100, y + 23, 150, 330, "Aimbot");
    render_section(x + 280, y + 23, 150, 330, "Misc.");
    
    render_checkbox(1, Left, "Enabled", &set.legit.enabled);
    render_slider_i(2, Left, "FOV",     &set.legit.fov, {0, 180});
    render_slider_i(3, Left, "Smoothing", &set.legit.smooth_factor, {0, 100}, false, true, &set.legit.smoothing);
    render_slider_i(4, Left, "Recoil control", &set.legit.rcs_factor, {0, 100}, false, true, &set.legit.recoil_control);
    render_checkbox(5, Left, "Backtracking", &set.legit.backtrack);
}

void q_menu::render_visuals()
{
    render_section(x + 100, y + 23, 150, 330, "Players");
    render_section(x + 280, y + 23, 150, 330, "Other");
    
    render_checkbox(1, Left, "Enabled", &set.visuals.enabled);
    render_checkbox(2, Left, "Visual only", &set.visuals.visible_only);
    render_checkbox(3, Left, "Enemy only", &set.visuals.enemy_only);
    render_checkbox(4, Left, "Box", &set.visuals.box);
    render_checkbox(5, Left, "Name", &set.visuals.name);
    render_checkbox(6, Left, "Health", &set.visuals.health);
    render_checkbox(7, Left, "Acitve weapon", &set.visuals.weapon);
    render_checkbox(8, Left, "Skeleton", &set.visuals.skeleton);
    render_checkbox(9, Left, "Snap lines", &set.visuals.snap_lines);
    render_checkbox(10, Left, "Backtrack",  &set.visuals.backtrack);
    impl_combo(Left, true);
    render_combo(11, Left, "Chams", {"Textured", "Flat", "No players"}, &set.visuals.chams_type, &opened.chams, false, true, &set.visuals.chams);
    
    
    render_checkbox(1, Right, "Radar", &set.visuals.radar);
    render_checkbox(2, Right, "Bomb timer", &set.visuals.bomb_timer);
    render_checkbox(3, Right, "Dropped weapons", &set.visuals.dropped_weapons);
    render_checkbox(4, Right, "Recoil crosshair", &set.visuals.recoil_crosshair);
}

void q_menu::render_misc()
{
    render_section(x + 100, y + 23, 150, 330, "General");
    render_section(x + 280, y + 23, 150, 330, "Misc.");
    
    render_slider_i(1, Left, "Override FOV", &set.misc.fov, {0, 70}, false, true, &set.misc.fov_changer);
    render_slider_i(2, Left, "Override view model", &set.misc.view_fov, {0, 100}, false, true, &set.misc.view_changer);
    render_checkbox(3, Left, "Bhop", &set.misc.bhop);
    render_checkbox(4, Left, "Auto-strafe", &set.misc.auto_strafe);
    render_checkbox(5, Left, "Show ranks", &set.misc.show_ranks);
    render_checkbox(6, Left, "Clan-tag", &set.misc.clan_tag);
    render_slider_i(7, Left, "Remove flash", &set.misc.flash_alpha, {0, 255}, false, true, &set.misc.remove_flash);
    render_checkbox(8, Left, "Remove smoke", &set.misc.remove_smoke);
    render_checkbox(9, Left, "Remove visual recoil", &set.misc.remove_vrecoil);

    if(render_button_2(3, Right, "Load", opened.config))
        config->load();
    
    if(render_button_2(4, Right, "Save", opened.config))
        config->save();
    
    if(render_button_2(5, Right, "Unload"))
        unload_cheat();
    
    impl_combo(Right, true);
    
    offset[Right - 1] -= 24;
    
    static const vector<const char*> configs = config->get_configs();
    
    render_combo(1, Right, "Configs", configs, &config->config_no, &opened.config);
}

void q_menu::render_players()
{
    render_section(x + 100, y + 23, 150, 330, "Colors");
    render_section(x + 280, y + 23, 150, 330, "Colors cont.");
    
    render_color_picker(1, Left, "Box", &set.colors.box_vis);
    render_color_picker(2, Left, "Box behind walls", &set.colors.box_ign);
    render_color_picker(3, Left, "Player chams", &set.colors.chams_vis);
    render_color_picker(4, Left, "Chams behind walls", &set.colors.chams_ign);
        
    render_color_picker(1, Right, "Skeleton", &set.colors.skeleton);
    render_color_picker(2, Right, "Snap lines", &set.colors.snap_lines);
}

