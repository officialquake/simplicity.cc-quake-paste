/*
 *  util.h
 */
#pragma once

#define ARRSIZE(arr)            (sizeof(arr) / sizeof(*arr))
#define IMPL_HOOK(hook)          static bool o; if(!o) { quake(string(hook) + " hooked", Color::Orange()); o = true; }
#define TIME_TO_TICKS(time)     ((int)(0.5f + ((float)time) / pGlobals->interval_per_tick ))

struct box_t
{
    int x, y, w, h;
};

void quake(string message, Color color = Color::Orange(), string prefix = "quake");
void angle_vectors(const Vector& angles, Vector& forward);
void angle_vectors(const Vector& angles, Vector& forward, Vector& right, Vector& up);
void vector_angles(const Vector& forward, QAngle& angles);
void normalize_angles(QAngle& angle);

void clamp_yaw(float& angle);
void clamp_moves(float& flForward, float& flSide, float& flUp);
void fix_movement(Vector& oang, CUserCmd* cmd);
void correct_movement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);

Vector get_hitbox_position(C_BasePlayer* pEntity, int Hitbox);

bool world_to_screen(Vector& vFrom, Vector& vTo);

bool get_box(C_BaseEntity* pEntity, box_t& str);

void timestamp();

Color imvec_to_color(ImVec4 col, bool alpha = false);

string get_weapon_name(C_BaseCombatWeapon* weapon);

C_BaseCombatWeapon* get_active_weapon(C_BasePlayer* player);

float   get_distance(Vector a, Vector b);
QAngle  calculate_angle(Vector src, Vector dst);
float   get_fov(const QAngle& viewAngle, const QAngle& aimAngle);

bool is_point_visible(Vector point);
bool is_player_visible(C_BasePlayer* player);
bool is_hitbox_visible(C_BasePlayer* player, int hitbox);


template<class T, class U>
T clamp(T in, U low, U high)
{
    if (in <= low)
        return low;
    
    if (in >= high)
        return high;
    
    return in;
}

