/*
 *  renderer.h
 */
#pragma once

#include "imgui.h"

namespace Fonts
{
    extern ImFont* big;
    extern ImFont* small;
    extern ImFont* impact;
    extern ImFont* verdana;
    extern ImFont* section;
}

class C_ImRenderer
{
private:
    
    ImDrawList* draw;
    
private:
    
    ImFont* create_font(const char* font_path, float font_size);
    
public:
    
    void start();
    void finish();
    
    
    void draw_box(int x, int y, int w, int h, ImColor col);
    void draw_box_filled(int x, int y, int w, int h, ImColor col);
    void draw_box_outlined(int x, int y, int w, int h, int thickness, ImColor col, ImColor border);
    void draw_box_gradient(int x, int y, int w, int h, ImColor col1, ImColor col2, int direction = 0);
    void draw_box_3d(Vector origin, Vector min, Vector max, ImColor col);
    
    void draw_line(int x, int y, int xx, int yy, ImColor col);
    void draw_string(int x, int y, const char* str, ImFont* font, ImColor col, bool center_x = false, bool center_y = false);
    void draw_polygon(ImVec2* verts, int num, ImColor col);
    void draw_circle(ImVec2 center, float radius, ImColor col);
    void draw_circle_filled(ImVec2 center, float radius, ImColor col);
    
    
    ImVec2 get_text_size(const char* str);
    
    void init_fonts();
    
};

