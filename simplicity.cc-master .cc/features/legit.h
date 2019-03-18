/*
 *  aim.h
 */
#pragma once

class C_Legit
{
private:
    
private:
    
    void find_target();
    int  get_best_hitbox();
    
    void smooth_angle(QAngle& angle);
    
public:
    
    void aimbot();
    
    void recoil_control();
    
public:
    
    C_BasePlayer* target;
    
};

extern C_Legit* legit;
