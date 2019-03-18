/*      renderer.cpp
 *
 *
 *
 */

#include "main.h"
#include "renderer.h"

namespace Fonts
{
    HFONT esp;
}

/****************************** Drawings ******************************/

void C_Renderer::draw_box(int x, int y, int w, int h, Color col)
{
    pSurface->DrawSetColor(col);
    pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void C_Renderer::draw_box_filled(int x, int y, int w, int h, Color col)
{
    pSurface->DrawSetColor(col);
    pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void C_Renderer::draw_box_outlined(int x, int y, int w, int h, int thickness, Color col, Color border)
{
    this->draw_box_filled(x - thickness, y - thickness, w + thickness * 2, h + thickness * 2, border);
    this->draw_box_filled(x, y, w, h, col);
}

void C_Renderer::draw_box_gradient(int x, int y, int w, int h, Color col1, Color col2)
{
    /*
     *  Unused
     */
}

void C_Renderer::draw_box_3d(Vector origin, Vector min, Vector max, Color col)
{
    min += origin;
    max += origin;
    
    Vector points[] =
    {
        Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(min.x, min.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(max.x, max.y, max.z),
        Vector(max.x, min.y, max.z)
    };
    
    int edges[12][2] =
    {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
    };
    
    for (auto it : edges)
    {
        Vector p1, p2;
        if (!world_to_screen(points[it[0]], p1) || !world_to_screen(points[it[1]], p2))
            return;
        
        this->draw_line(p1.x, p1.y, p2.x, p2.y, col);
    }
}

void C_Renderer::draw_line(int x, int y, int xx, int yy, Color col)
{
    pSurface->DrawSetColor(col);
    pSurface->DrawLine(x, y, xx, yy);
}

void C_Renderer::draw_string(int x, int y, const char* str, HFONT font, Color col, bool center)
{
    wstring wstr = string_to_wstring(str);
    
    if(center)
    {
        int wide, tall;
        pSurface->GetTextSize(font, wstr.c_str(), wide, tall);
        x -= wide / 2;
        y -= tall / 2;
    }
    
    pSurface->DrawSetTextPos(x, y);
    pSurface->DrawSetTextFont(font);
    pSurface->DrawSetTextColor(col);
    pSurface->DrawPrintText(wstr.c_str(), (int)wcslen(wstr.c_str()));
}

void C_Renderer::draw_polygon(Vertex_t* verts, int num, Color col)
{
    static int texture_id = pSurface->CreateNewTextureID(true);
    static unsigned char buf[4] = { 255, 255, 255, 255 };
    pSurface->DrawSetTextureRGBA(texture_id, buf, 1, 1);
    pSurface->DrawSetColor(col);
    pSurface->DrawSetTexture(texture_id);
    pSurface->DrawTexturedPolygon(num, verts);
}

void C_Renderer::draw_circle(Vector2D center, float radius, Color col)
{
    const int points = 20;
    float step = (float)M_PI * 2.0f / points;
    for (float a = 0; a < (M_PI * 2.0f); a += step)
    {
        Vector2D start(radius * cosf(a) + center.x, radius * sinf(a) + center.y);
        Vector2D end(radius * cosf(a + step) + center.x, radius * sinf(a + step) + center.y);
        this->draw_line(start.x, start.y, end.x, end.y, col);
    }
}

void C_Renderer::draw_circle_filled(Vector2D center, float radius, Color col)
{
    static bool once = true;
    const int points = 20;
    
    static vector<float> temppointsx;
    static vector<float> temppointsy;
    
    if(once)
    {
        float step = (float)M_PI * 2.0f / points;
        for (float a = 0; a < ( M_PI * 2.0f ); a += step)
        {
            temppointsx.push_back(cosf(a));
            temppointsy.push_back(sinf(a));
        }
        once = false;
    }
    
    vector<Vertex_t> vertices;
    
    for (int i = 0; i < temppointsx.size(); i++)
    {
        float x = radius * temppointsx[i] + center.x;
        float y = radius * temppointsy[i] + center.y;
        
        vertices.push_back(Vertex_t(Vector2D(x, y)));
    }
    
    draw_polygon(vertices.data(), points, col);
}

/****************************** Util ******************************/

wstring C_Renderer::string_to_wstring(string str)
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    
    try
    {
        return converter.from_bytes(str);
    }
    catch (std::range_error)
    {
        wostringstream s;
        s << str.c_str();
        return s.str();
    }
}

Vector2D C_Renderer::get_text_size(const char* str, HFONT font)
{
    wstring wc = string_to_wstring(str);
    int x_res, y_res;
    pSurface->GetTextSize(font, wc.c_str(), x_res, y_res);
    
    return Vector2D(x_res, y_res);
}

HFONT C_Renderer::create_font(const char* font_name, int font_size, int flags)
{
    HFONT font = pSurface->create_font();
    pSurface->SetFontGlyphSet(font, font_name, font_size, 150, 0, 0, flags);
    return font;
}

void C_Renderer::init_fonts()
{
    Fonts::esp = create_font("Verdana Bold", 12, FONTFLAG_DROPSHADOW);
}
