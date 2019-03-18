/*      util.cpp
 *
 *
 *
 */
#include "main.h"

/***************** Util *****************/

void quake(string str, Color col, string prefix)
{
    if(!pCvar)
        return;
    
    prefix = "[" + prefix + "] ";
    pCvar->ConsoleColorPrintf(col, prefix.c_str());
    pCvar->ConsoleDPrintf("%s\n", str.c_str());
}

bool world_to_screen(Vector& in, Vector& out)
{
    return !pOverlay->ScreenPosition(in, out);
}

bool is_point_visible(Vector point)
{
    if(!Global::local)
        return false;
    
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::local;
    
    ray.Init(Global::local->GetEyePosition(), point);
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.fraction > 0.97f);
}

bool is_player_visible(C_BasePlayer* entity)
{
    if(!Global::local || !entity)
        return false;
    
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::local;
    
    ray.Init(Global::local->GetEyePosition(), entity->GetEyePosition());
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.m_pEnt == entity || trace.fraction > 0.99f);
}

bool is_hitbox_visible(C_BasePlayer* player, int hitbox)
{
    if(!Global::local || !player)
        return false;
    
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = Global::local;
    
    ray.Init(Global::local->GetEyePosition(), get_hitbox_position(player, hitbox));
    pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);
    return (trace.m_pEnt == player || trace.fraction > 0.99f);
}

C_BaseCombatWeapon* get_active_weapon(C_BasePlayer* player)
{
    auto weapon = player->GetActiveWeapon();
    
    if (!weapon)
        return nullptr;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(weapon);
}

void timestamp()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

Color imvec_to_color(ImVec4 col, bool alpha)
{
    return Color(col.x * 255, col.y * 255, col.z * 255, alpha ? col.w * 255 : 255);
}

string get_weapon_name(C_BaseCombatWeapon* weapon)
{
    if(!weapon)
        return "Unknown";
    
    int id = *weapon->GetItemDefinitionIndex();
    
    if(!id)
        return "Unknown";
    
    switch (id)
    {
            /* pistols */
        case 4:
            return "Glock";
        case 2:
            return "Dualies";
        case 36:
            return "P250";
        case 30:
            return "Tec 9";
        case 1:
            return "Deagle";
        case 32:
            return "P2000";
        case 3:
            return "Five Seven";
        case 64:
            return "Revolver";
        case 63:
            return "CZ75";
        case 61:
            return "USP";
            
            /*heavy*/
        case 35:
            return "Nova";
        case 25:
            return "XM1014";
        case 29:
            return "Sawed Off";
        case 14:
            return "M249";
        case 28:
            return "Negev";
        case 27:
            return "Mag 7";
            
            /*smgs*/
        case 17:
            return "Mac 10";
        case 33:
            return "MP7";
        case 23:
            return "MP5";
        case 24:
            return "UMP45";
        case 19:
            return "P90";
        case 26:
            return "Bizon";
        case 34:
            return "MP9";
            
            /*rifles*/
        case 10:
            return "Famas";
        case 16:
            return "M4A1";
        case 40:
            return "Scout";
        case 8:
            return "AUG";
        case 9:
            return "AWP";
        case 38:
            return "Scar 20";
        case 13:
            return "Galil";
        case 7:
            return "AK47";
        case 39:
            return "SG553";
        case 11:
            return "G3SG1";
        case 60:
            return "M4A1-S";
            
            /*grenades*/
        case 46:
        case 48:
            return "Molotov";
        case 44:
            return "Grenade";
        case 43:
            return "Flash";
        case 45:
            return "Smoke";
        case 47:
            return "Decoy";
            
            /*other*/
        case 31:
            return "Zeus";
        case 49:
            return "Bomb";
        default:
            return "Knife";
    }
}

/***************** Math *****************/

float get_distance(Vector a, Vector b)
{
    return sqrt( pow( a.x - b.x, 2 ) + pow( a.y - b.y, 2 ) + pow( a.z - b.z, 2 ) ) * 0.0254f;
}

Vector extrapolate_tick( Vector p0, Vector v0 )
{
    return p0 + ( v0 * pGlobals->interval_per_tick );
}

void clamp_moves(float& flForward, float& flSide, float& flUp)
{
    if(flForward > 450)
        flForward = 450;
    
    if(flSide > 450)
        flSide = 450;
    
    if(flUp > 450)
        flUp = 450;
    
    if(flForward < -450)
        flForward = -450;
    
    if(flSide < -450)
        flSide = -450;
    
    if(flUp < -450)
        flUp = -450;
}

void clamp_yaw(float& angle)
{
    while(angle > 180)
        angle -= 360;
    
    while(angle < -180)
        angle += 360;
}

void fix_movement(Vector& oang, CUserCmd* pCmd)
{
    Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
    float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
    Vector vMove2;
    vector_angles(vMove, vMove2);
    
    flYaw = DEG2RAD(pCmd->viewangles.y - oang.y + vMove2.y);
    pCmd->forwardmove = cos(flYaw) * flSpeed;
    pCmd->sidemove = sin(flYaw) * flSpeed;
    
    if (pCmd->viewangles.x < -90.f || pCmd->viewangles.x > 90.f)
        pCmd->forwardmove = -pCmd->forwardmove;
}

void angle_vectors(const Vector & angles, Vector& forward)
{
    Assert(s_bMathlibInitialized);
    Assert(forward);
    
    float sp, sy, cp, cy;
    
    sy = sin(DEG2RAD(angles[1]));
    cy = cos(DEG2RAD(angles[1]));
    sp = sin(DEG2RAD(angles[0]));
    cp = cos(DEG2RAD(angles[0]));
    
    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

void angle_vectors(const Vector& angles, Vector& forward, Vector& right, Vector& up)
{
    float angle;
    static float sr, sp, sy, cr, cp, cy;
    
    angle = angles[1] * (M_PI * 2 / 360);
    sy = sin(angle);
    cy = cos(angle);
    
    angle = angles[0] * (M_PI * 2 / 360);
    sp = sin(angle);
    cp = cos(angle);
    
    angle = angles[2] * (M_PI * 2 / 360);
    sr = sin(angle);
    cr = cos(angle);
    
    if (!forward.IsZero())
    {
        forward.x = cp*cy;
        forward.y = cp*sy;
        forward.z = -sp;
    }
    
    if (!right.IsZero())
    {
        right.x = (-1 * sr*sp*cy + -1 * cr*-sy);
        right.y = (-1 * sr*sp*sy + -1 * cr*cy);
        right.z = -1 * sr*cp;
    }
    
    if (!up.IsZero())
    {
        up.x = (cr*sp*cy + -sr*-sy);
        up.y = (cr*sp*sy + -sr*cy);
        up.z = cr*cp;
    }
}

void vector_angles(const Vector& forward, QAngle &angles)
{
    float tmp, yaw, pitch;
    
    if (forward[1] == 0 && forward[0] == 0)
    {
        yaw = 0;
        if (forward[2] > 0)
            pitch = 270;
        else
            pitch = 90;
    }
    else
    {
        yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
        if (yaw < 0)
            yaw += 360;
        
        tmp     = sqrt (forward[0] * forward[0] + forward[1] * forward[1]);
        pitch   = (atan2(-forward[2], tmp) * 180 / M_PI);
        
        if (pitch < 0)
            pitch += 360;
    }
    
    angles[0] = pitch;
    angles[1] = yaw;
    angles[2] = 0;
}

void correct_movement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
    float deltaView, f1, f2;
    
    if (vOldAngles.y < 0.f)
        f1 = 360.0f + vOldAngles.y;
    else
        f1 = vOldAngles.y;
    
    if (pCmd->viewangles.y < 0.0f)
        f2 = 360.0f + pCmd->viewangles.y;
    else
        f2 = pCmd->viewangles.y;
    
    if (f2 < f1)
        deltaView = abs(f2 - f1);
    else
        deltaView = 360.0f - abs(f1 - f2);
    
    deltaView = 360.0f - deltaView;
    
    pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
    pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

bool get_box(C_BaseEntity* pEntity, box_t& str) // Credit's to dude719 & keybode.
{
    if (!pEntity)
        return false;
    
    Vector vOrigin = pEntity->GetVecOrigin(); // Not sure if this is the right one...
    Vector min = pEntity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = pEntity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] =
    {
        Vector(min.x, min.y, min.z), Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z), Vector(max.x, min.y, min.z),
        Vector(max.x, max.y, max.z), Vector(min.x, max.y, max.z),
        Vector(min.x, min.y, max.z), Vector(max.x, min.y, max.z)
    };
    
    Vector flb;
    Vector brt;
    Vector blb;
    Vector frt;
    Vector frb;
    Vector brb;
    Vector blt;
    Vector flt;
    
    
    if (!world_to_screen(points[3], flb) ||
        !world_to_screen(points[5], brt) ||
        !world_to_screen(points[0], blb) ||
        !world_to_screen(points[4], frt) ||
        !world_to_screen(points[2], frb) ||
        !world_to_screen(points[1], brb) ||
        !world_to_screen(points[6], blt) ||
        !world_to_screen(points[7], flt))
        return false;
    
    Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
    
    float left      = flb.x;    // left
    float top       = flb.y;    // top
    float right     = flb.x;    // right
    float bottom    = flb.y;    // bottom
    
    for (int i = 1; i < 8; i++)
    {
        if (left > arr[i].x)
            left = arr[i].x;
        if (bottom < arr[i].y)
            bottom = arr[i].y;
        if (right < arr[i].x)
            right = arr[i].x;
        if (top > arr[i].y)
            top = arr[i].y;
    }
    
    str.x = left;
    str.y = top;
    str.w = right - left;
    str.h = bottom - top;
    
    return true;
}

void vector_transform(Vector& in1, matrix3x4_t& in2, Vector& out)
{
    out.x = DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
    out.y = DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
    out.z = DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}

Vector get_hitbox_position(C_BasePlayer* pEntity, int Hitbox)
{
    if(!pEntity)
        return Vector(0,0,0);
    
    matrix3x4_t matrix[128];
    
    if (!pEntity->SetupBones(matrix, 128, 0x100, pGlobals->curtime))
        return Vector(0, 0, 0);
    
    studiohdr_t*        hdr = pModelInfo->GetStudioModel(pEntity->GetModel());
    mstudiohitboxset_t* set = hdr->pHitboxSet(0);
    mstudiobbox_t*      hitbox = set->pHitbox(Hitbox);
    
    if (!hitbox)
        return Vector(0, 0, 0);
    
    Vector vMin, vMax, vCenter, sCenter;
    vector_transform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    vector_transform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    
    float ptwoz = 0.f;
    float zval  = (ptwoz * vMin.z + 50.f * vMax.z) / 50.f;
    vCenter.z = zval;
    
    return vCenter;
}

void normalize_angles(QAngle& angle)
{
    while (angle.x > 89.0f)
        angle.x -= 180.f;
    
    while (angle.x < -89.0f)
        angle.x += 180.f;
    
    while (angle.y > 180.f)
        angle.y -= 360.f;
    
    while (angle.y < -180.f)
        angle.y += 360.f;
}

/*
 *  Only used in calculate_angle
 */
static void _vector_angles(const Vector& forward, QAngle& angles)
{
    if (forward[1] == 0.0f && forward[0] == 0.0f)
    {
        angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;   // pitch
        angles[1] = 0.0f;                                   // yaw
    }
    else
    {
        angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
        angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;
        
        if (angles[1] > 90)
            angles[1] -= 180;
        else if (angles[1] < 90)
            angles[1] += 180;
        else if (angles[1] == 90)
            angles[1] = 0;
    }
    
    angles[2] = 0.0f;
}

QAngle calculate_angle(Vector src, Vector dst)
{
    QAngle angles;
    Vector delta = src - dst;
    
    _vector_angles(delta, angles);
    delta.Normalize();
    
    return angles;
}

float get_fov(const QAngle& viewAngle, const QAngle& aimAngle)
{
    QAngle delta = aimAngle - viewAngle;
    normalize_angles(delta);
    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

/***************** Misc *****************/

char* C_BasePlayer::GetName()
{
    player_info_t info;
    pEngine->GetPlayerInfo(this->GetIndex(), &info);
    return info.name;
}
