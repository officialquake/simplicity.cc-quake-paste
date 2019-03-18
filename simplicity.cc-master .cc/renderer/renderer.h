/*
 *  renderer.h
 */
#pragma once

namespace Fonts
{
    extern HFONT esp;
}

class C_Renderer
{
private:
    
    wstring string_to_wstring(string str);
    HFONT create_font(const char* font_name, int font_size, int flags);
    
public:
    
    void draw_box(int x, int y, int w, int h, Color col);
    void draw_box_filled(int x, int y, int w, int h, Color col);
    void draw_box_outlined(int x, int y, int w, int h, int thickness, Color col, Color border);
    void draw_box_gradient(int x, int y, int w, int h, Color col1, Color col2);
    void draw_box_3d(Vector origin, Vector min, Vector max, Color col);
    
    void draw_line(int x, int y, int xx, int yy, Color col);
    void draw_string(int x, int y, const char* str, HFONT font, Color col, bool center = false);
    void draw_polygon(Vertex_t* verts, int num, Color col);
    void draw_circle(Vector2D center, float radius, Color col);
    void draw_circle_filled(Vector2D center, float radius, Color col);
    
    Vector2D get_text_size(const char* str, HFONT font);
    
    void init_fonts();    
};
