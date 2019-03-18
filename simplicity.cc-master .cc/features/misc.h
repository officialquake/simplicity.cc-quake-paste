/*
 *  misc.h
 */
#pragma once

class C_Misc
{
private:
    
public:
    
    void show_ranks();
    void clan_tag();
    void fake_lag();
    void change_view_model(float& fov);
    
    void remove_flash(ClientFrameStage_t stage);
    void remove_smoke(ClientFrameStage_t stage);
    
    void bhop();
    void auto_strafe();
    
};

extern C_Misc* misc;
