/*      config.cpp
 *
 *
 *
 */

#include "main.h"
#include "config.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const string extention = ".txt";

c_config* config = new c_config();

c_config::c_config()
{
    
}

inline bool does_file_exist(const string& path)
{
    fstream f(path);
    return  f.good();
}

void c_config::init()
{
    folder = string(getenv("HOME")) + "/quake/";
    
    if(!does_file_exist(folder))
        mkdir(folder.c_str(), 0755);
    
    for(int i = 0; i < configs.size(); i++)
    {
        string c = configs.at(i);
        if(!does_file_exist(folder + c + extention))
        {
            config_no = i;
            this->save();
        }
    }
    
    
    config_no = 0;
    
    this->load();
    this->save();
}

void set_color_value(json& config, const string& key, ImVec4 color)
{
    config["colors"][key]["r"] = color.x;
    config["colors"][key]["g"] = color.y;
    config["colors"][key]["b"] = color.z;
    config["colors"][key]["a"] = color.w;
}

void c_config::save()
{
    json config;
    string section;

    section = "legit";
    config[section]["enabled"]          = set.legit.enabled;
    config[section]["flash_check"]      = set.legit.flash_check;
    config[section]["fov"]              = set.legit.fov;
    config[section]["smoothing"]        = set.legit.smoothing;
    config[section]["smooth_factor"]    = set.legit.smooth_factor;
    config[section]["recoil_control"]   = set.legit.recoil_control;
    config[section]["rcs_factor"]       = set.legit.rcs_factor;
    config[section]["backtrack"]        = set.legit.backtrack;
    
    section = "visuals";
    config[section]["enabled"]          = set.visuals.enabled;
    config[section]["visible_only"]     = set.visuals.visible_only;
    config[section]["enemy_only"]       = set.visuals.enemy_only;
    config[section]["box"]              = set.visuals.box;
    config[section]["name"]             = set.visuals.name;
    config[section]["health"]           = set.visuals.health;
    config[section]["weapon"]           = set.visuals.weapon;
    config[section]["radar"]            = set.visuals.radar;
    config[section]["skeleton"]         = set.visuals.skeleton;
    config[section]["snap_lines"]       = set.visuals.snap_lines;
    config[section]["backtrack"]        = set.visuals.backtrack;
    config[section]["chams"]            = set.visuals.chams;
    config[section]["chams_type"]       = set.visuals.chams_type;
    config[section]["bomb_timer"]       = set.visuals.bomb_timer;
    config[section]["dropped_weapons"]  = set.visuals.dropped_weapons;
    config[section]["recoil_crosshair"] = set.visuals.recoil_crosshair;
    
    section = "misc";
    config[section]["bhop"]             = set.misc.bhop;
    config[section]["auto_strafe"]      = set.misc.auto_strafe;
    config[section]["fov_changer"]      = set.misc.fov_changer;
    config[section]["fov"]              = set.misc.fov;
    config[section]["view_changer"]     = set.misc.view_changer;
    config[section]["view_fov"]         = set.misc.view_fov;
    config[section]["show_ranks"]       = set.misc.show_ranks;
    config[section]["clan_tag"]         = set.misc.clan_tag;
    config[section]["remove_flash"]     = set.misc.remove_flash;
    config[section]["flash_alpha"]      = set.misc.flash_alpha;
    config[section]["remove_smoke"]     = set.misc.remove_smoke;
    config[section]["remove_vrecoil"]   = set.misc.remove_vrecoil;
    
    section = "colors";
    set_color_value(config, "box_vis", set.colors.box_vis);
    set_color_value(config, "box_ign", set.colors.box_ign);
    set_color_value(config, "chams_vis", set.colors.chams_vis);
    set_color_value(config, "chams_ign", set.colors.chams_ign);
    set_color_value(config, "skeleton", set.colors.skeleton);
    set_color_value(config, "snap_lines", set.colors.snap_lines);
    
    
    current_config = configs.at(config_no);
    
    
    ofstream f;
    f.open(folder + current_config + extention);
    f << config.dump(2, ' ');
    f.close();
}

template<class T>
void get_value(json config, string section, string key, T* value)
{
    try
    {
        *value = config[section][key];
    }
    catch(exception& e)
    {

    }
}

void get_color_value(json config, string key, ImVec4* value)
{
    try
    {
        value->x = config["colors"][key]["r"];
        value->y = config["colors"][key]["g"];
        value->z = config["colors"][key]["b"];
        value->w = config["colors"][key]["a"];
    }
    catch(exception& e)
    {
        
    }
}

void c_config::load()
{
    current_config = string(configs.at(config_no));
    
    string buffer, line;
    
    if(!does_file_exist(folder + current_config + extention))
    {
        quake("Cant find config");
        return;
    }
    
    ifstream f(folder + current_config + extention);
    
    while(getline(f, line))
        buffer += line;
    
    f.close();
    
    json config = json::parse(buffer);
    
    string section;
    
    section = "legit";
    get_value(config, section, "enabled", &set.legit.enabled);
    get_value(config, section, "flash_check", &set.legit.flash_check);
    get_value(config, section, "fov", &set.legit.fov);
    get_value(config, section, "backtrack", &set.legit.backtrack);
    get_value(config, section, "smoothing", &set.legit.smoothing);
    get_value(config, section, "smooth_factor", &set.legit.smooth_factor);
    get_value(config, section, "recoil_control", &set.legit.recoil_control);
    get_value(config, section, "rcs_factor", &set.legit.rcs_factor);
    
    section = "visuals";
    get_value(config, section, "enabled", &set.visuals.enabled);
    get_value(config, section, "visible_only", &set.visuals.visible_only);
    get_value(config, section, "enemy_only", &set.visuals.enemy_only);
    get_value(config, section, "box", &set.visuals.box);
    get_value(config, section, "name", &set.visuals.name);
    get_value(config, section, "health", &set.visuals.health);
    get_value(config, section, "weapon", &set.visuals.weapon);
    get_value(config, section, "radar", &set.visuals.radar);
    get_value(config, section, "skeleton", &set.visuals.skeleton);
    get_value(config, section, "snap_lines", &set.visuals.snap_lines);
    get_value(config, section, "backtrack", &set.visuals.backtrack);
    get_value(config, section, "chams", &set.visuals.chams);
    get_value(config, section, "chams_type", &set.visuals.chams_type);
    get_value(config, section, "bomb_timer", &set.visuals.bomb_timer);
    get_value(config, section, "dropped_weapons", &set.visuals.dropped_weapons);
    get_value(config, section, "recoil_crosshair", &set.visuals.recoil_crosshair);
    
    section = "misc";
    get_value(config, section, "bhop", &set.misc.bhop);
    get_value(config, section, "auto_strafe", &set.misc.auto_strafe);
    get_value(config, section, "fov_changer", &set.misc.fov_changer);
    get_value(config, section, "fov", &set.misc.fov);
    get_value(config, section, "view_changer", &set.misc.view_changer);
    get_value(config, section, "view_fov", &set.misc.view_fov);
    get_value(config, section, "show_ranks", &set.misc.show_ranks);
    get_value(config, section, "clan_tag", &set.misc.clan_tag);
    get_value(config, section, "remove_flash", &set.misc.remove_flash);
    get_value(config, section, "flash_alpha", &set.misc.flash_alpha);
    get_value(config, section, "remove_smoke", &set.misc.remove_smoke);
    get_value(config, section, "remove_vrecoil", &set.misc.remove_vrecoil);
    
    section = "colors";
    get_color_value(config, "box_vis", &set.colors.box_vis);
    get_color_value(config, "box_ign", &set.colors.box_ign);
    get_color_value(config, "chams_vis", &set.colors.chams_vis);
    get_color_value(config, "chams_ign", &set.colors.chams_ign);
    get_color_value(config, "skeleton", &set.colors.skeleton);
    get_color_value(config, "snap_lines", &set.colors.snap_lines);
}
