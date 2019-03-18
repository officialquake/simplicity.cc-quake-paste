/*      legit_util.cpp
 *
 *
 *
 */

#include "main.h"
#include "legit.h"

void C_Legit::smooth_angle(QAngle& angle)
{
    srand((unsigned int)(pGlobals->tickcount * clock()));
    
    QAngle delta = angle - Global::cmd->viewangles;
    normalize_angles(delta);
    
    float factor = ((float)set.legit.smooth_factor / 100.f);
    float smooth = powf(factor, 0.4f);
    smooth = min(0.959999f, smooth);

    /*
     *  Salting
     */
    float sine = sin(pGlobals->tickcount);
    float salt = sine * 0.042f;
    float oval = smooth + salt;
    smooth *= oval;
    
    
    QAngle to_change = QAngle();
    
    float coeff = (1.0f - smooth) / delta.Length() * 4.0f;
    coeff = min(1.0f, coeff);
    to_change = delta * coeff;
    
    angle = Global::cmd->viewangles + to_change;
}

void C_Legit::recoil_control()
{
    if(!set.legit.recoil_control || !set.legit.enabled)
        return;
    
    if(!Global::local || !Global::cmd)
        return;
    
    Vector punch = *Global::local->GetAimPunchAngle() * 2.f;
    
    float x_factor = set.legit.rcs_factor;
    float y_factor = x_factor;
    
    if(Global::cmd->buttons & IN_ATTACK)
    {
        Global::cmd->viewangles.x -= punch.x * (2.f / 100.f * (x_factor / 2));
        Global::cmd->viewangles.y -= punch.y * (2.f / 100.f * (y_factor / 2));
    }
}
