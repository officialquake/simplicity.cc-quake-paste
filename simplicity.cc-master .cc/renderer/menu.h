/*
 *  menu.h
 */
#pragma once

#include "main.h"
#include "imgui.h"
#include "imrenderer.h"

struct opened_combo
{
    bool chams  = false;
    bool config = false;
    bool yaw    = false;
    bool pitch  = false;
    bool fake   = false;
};

class q_menu
{
private:
    
    int x, y;
    const int w  = 450, h = 368;
    int move_height;
    
    int tab;
    
    opened_combo opened;
    C_ImRenderer* draw;
    
    vector<int> offset;
    
private:

    void render_checkbox(int index, int side, const char* label, bool* value, bool cancel = false);
    void render_slider_i(int index, int side, const char* label, int*  value, ImVec2 bounds, bool cancel = 0, bool checkbox = false, bool* check_val = nullptr);
    void render_slider_f(int index, int side, const char* label, float*value, ImVec2 bounds, bool cancel = 0, bool checkbox = false, bool* check_val = nullptr);
    void render_combo   (int index, int side, const char* label, vector<const char*> items, int* value, bool* opened,
                         bool cancel = false, bool checkbox = false, bool* check_val = nullptr);
    void render_button  (int index, int side, const char* label, bool* value, bool cancel = false);
    bool render_button_2(int index, int side, const char* label, bool cancel = false);
    void render_section (int x, int y, int w, int h, const char* label);
    
    void render_slider_c(int index, int side, float* value, ImVec2 bounds, bool cancel, ImVec4 col, int col_index);
    void render_color_picker(int index, int side, const char* label, ImVec4* col, bool cancel = false);
    
    void render_legit();
    void render_visuals();
    void render_misc();
    void render_players();
    
    void render_tabs();
    
    void move();
    void impl_combo(int side, bool up);
    bool q_in_area(int x, int y, int w, int h);
    
public:
    
    q_menu() {};
    ~q_menu();
    
    void init();
    void display();
    
};

extern q_menu* menu;
