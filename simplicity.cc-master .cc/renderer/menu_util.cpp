/*      menu_util.cpp
 *
 *
 *
 */

#include "imgui.h"
#include "menu.h"

/*
 *  in_area
 *  Returns true if the mouse is in the given area
 */
bool q_menu::q_in_area(int x, int y, int w, int h)
{
    auto io = ImGui::GetIO();
    auto mouse = io.MousePos;
    return (mouse.x > x && mouse.y > y) && (mouse.x < x + w && mouse.y < y + h);
}

/*
 *  impl_combo
 *  Implements a combo which will be drawn later
 */
void q_menu::impl_combo(int side, bool up)
{
    offset[side - 1] += up ? 15 : -15;
}

/*
 *  move
 *  Moves the menu when clicking in the moveable height
 */
void q_menu::move()
{
    auto io = ImGui::GetIO();
    auto mouse = io.MousePos;
    auto delta = io.MouseDelta;
    bool clicked = io.MouseDown[0];
    static bool moving_last_tick = false;
    
    
    const int move_height = this->move_height + 4;
    
    bool hovering = (mouse.x > x && x + w > mouse.x) && (mouse.y > (y - 4) && (y - 4) + move_height > mouse.y);
    
    if((hovering || moving_last_tick) && clicked)
    {
        x += delta.x;
        y += delta.y;
        
        moving_last_tick = true;
    }
    else
    {
        moving_last_tick = false;
    }
}
