/*      renderer.cpp
 *
 *
 *
 */

#include "main.h"
#include "imrenderer.h"

/****************************** Window ******************************/

/*
 *  start
 *  Creates the window that everything is rendered to
 */
void C_ImRenderer::start()
{
    auto& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.f;
    
    static int w, h;
    pEngine->GetScreenSize(w, h);
    
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({w, h});
    ImGui::SetNextWindowBgAlpha(0.f);
    
    bool opened = true;
    int flags = ImGuiWindowFlags_NoTitleBar      | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoScrollbar     | ImGuiWindowFlags_NoInputs |
                ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                ImGuiWindowFlags_NoBringToFrontOnFocus;
    
    
    ImGui::Begin("drawings window", &opened, flags);
    
    this->draw = ImGui::GetWindowDrawList();
}

/*
 *  finish
 *
 */
void C_ImRenderer::finish()
{
    ImGui::End();
}

/****************************** Drawings ******************************/

/*
 *  draw_box
 *  Draws a hollow box
 */
void C_ImRenderer::draw_box(int x, int y, int w, int h, ImColor col)
{
    draw->AddRect({x, y}, {x + w, y + h}, col);
}

/*
 *  draw_box_filled
 *  Draws a filled box
 */
void C_ImRenderer::draw_box_filled(int x, int y, int w, int h, ImColor col)
{
    draw->AddRectFilled({x, y}, {x + w, y + h}, col);
}

/*
 *  draw_box_outlined
 *  Draws a box with an outline
 */
void C_ImRenderer::draw_box_outlined(int x, int y, int w, int h, int thickness, ImColor col, ImColor border)
{
    draw->AddRectFilled({x - thickness, y - thickness}, {x + w + thickness, y + h + thickness}, border);
    draw->AddRectFilled({x, y}, {x + w, y + h}, col);
}

/*
 *  draw_box_gradient
 *  Draws a box that gradients from one coloue to another, top to bottom
 */
void C_ImRenderer::draw_box_gradient(int x, int y, int w, int h, ImColor col1, ImColor col2, int direction)
{
    if(direction == 0)
    {
        draw->AddRectFilledMultiColor({x, y}, {x + w, y + h}, col1, col1, col2, col2);
    }
    else
    {
        draw->AddRectFilledMultiColor({x, y}, {x + w, y + h}, col1, col2, col2, col1);
    }
}

/*
 *  draw_box_3d
 *  Draws a 3d box around a point
 */
void C_ImRenderer::draw_box_3d(Vector origin, Vector min, Vector max, ImColor col)
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

/*
 *  draw_line
 *  Draws a line between 2 points
 */
void C_ImRenderer::draw_line(int x, int y, int xx, int yy, ImColor col)
{
    draw->AddLine({x, y}, {xx, yy}, col);
}

/*
 *  draw_string
 *  Draws a string
 */
void C_ImRenderer::draw_string(int x, int y, const char* str, ImFont* font, ImColor col, bool center_x, bool center_y)
{
    bool drop = false;
    
    if(center_x || center_y)
    {
        auto text_size = get_text_size(str);
        
        if(center_x)
            x -= (text_size.x / 2);
        
        if(center_y)
            y -= (text_size.y / 2);
    }
    
    if(drop)
        draw->AddText(font, font->FontSize, {x + 2, y + 2}, IM_COL32_BLACK, str);
    
    draw->AddText(font, font->FontSize, {x, y}, col, str);
}

/*
 *  draw_polygon
 *  Draws a shape with given verticies
 */
void C_ImRenderer::draw_polygon(ImVec2* verts, int num, ImColor col)
{
    draw->AddConvexPolyFilled(verts, num, col);
}

/*
 *  draw_cicle
 *  Draws a hollow circle
 */
void C_ImRenderer::draw_circle(ImVec2 center, float radius, ImColor col)
{
    draw->AddCircle(center, radius, col);
}

/*
 *  draw_circle_filled
 *  Draws a filled circle
 */
void C_ImRenderer::draw_circle_filled(ImVec2 center, float radius, ImColor col)
{
    draw->AddCircleFilled(center, radius, col);
}

/****************************** Utils ******************************/

/*
 *  get_text_size
 *  Returns the text width and height
 */
ImVec2 C_ImRenderer::get_text_size(const char* str)
{
    return ImGui::CalcTextSize(str);
}

/****************************** Fonts ******************************/

/*
 *  Fonts namespace
 */
namespace Fonts
{
    ImFont* big;
    ImFont* small;
    ImFont* impact;
    ImFont* verdana;
    ImFont* section;
}

/*
 *  create_font
 *  Loads a font and returns it
 */
ImFont* C_ImRenderer::create_font(const char* font_path, float font_size)
{
    auto io = ImGui::GetIO();
    ImFontConfig* font_conf = new ImFontConfig;
    font_conf->OversampleH = font_conf->OversampleV = 1;
    font_conf->PixelSnapH = true;
    
    return io.Fonts->AddFontFromFileTTF(font_path, font_size, font_conf);
}

/*
 *  init_fonts
 *  Initialises fonts
 */
void C_ImRenderer::init_fonts()
{
    Fonts::big      = create_font("/Library/Fonts/ProggyClean.ttf", 13.f);
    Fonts::small    = create_font("/Library/Fonts/ProggyTiny.ttf",  10.f);
    Fonts::impact   = create_font("/Library/Fonts/Impact.ttf",      25.f);
    Fonts::verdana  = create_font("/Library/Fonts/Verdana.ttf",     11.f);
    Fonts::section  = create_font("/Library/Fonts/Verdana Bold.ttf",12.f);
}

