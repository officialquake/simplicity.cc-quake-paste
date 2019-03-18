/*      menu_items.cpp
 *
 *
 *
 */

#include "menu.h"

ImColor text_col= ImColor(225, 225, 225, 255);
ImColor green_1 = ImColor(153, 198,  85, 255);
ImColor green_2 = ImColor(119, 164,  53, 255);

void q_menu::render_section(int x, int y, int w, int h, const char* label)
{
    draw->draw_box(x, y, w, h, ImColor(48, 48, 48, 255));
    
    ImGui::PushFont(Fonts::section);
    
    auto text_size = draw->get_text_size(label);
    
    ImGui::PopFont();
    
    draw->draw_box_filled(x + 12, y - 1, text_size.x + 7, 3, ImColor(15, 15, 15, 255));
    draw->draw_string(x + 15, y - 6, label, Fonts::section,  ImColor(255, 255, 255, 255));
}

void q_menu::render_checkbox(int index, int side, const char* label, bool* value, bool cancel)
{
    const int size = 7;
    float x = this->x + (side == 1 ? 110 : 290);
    float y = this->y + 23 + (index * 15) + offset[side - 1];
    
    if(*value)
        draw->draw_box_gradient(x, y, size, size, green_1, green_2);
    else
        draw->draw_box_gradient(x, y, size, size, ImColor(75, 75, 75, 255), ImColor(50, 50, 50, 255));
    
    ImGui::PushFont(Fonts::verdana);
    auto text_size = draw->get_text_size(label);
    ImGui::PopFont();
    
    if (q_in_area(x, y, size + text_size.x + 15, size) && !cancel)
    {
        if(ImGui::GetIO().MouseClicked[0])
            *value = !*value;
    }
    
    draw->draw_box(x - 1, y - 1, size + 2, size + 2, ImColor(15, 15, 15, 255));
    draw->draw_string(x + 15, y - 3, label, Fonts::verdana, text_col);
}

inline int calculate_value(ImVec2 mouse, int x)
{
    const int real_x_start = ((1920 / 2) - (1920 / 2)) + x;
    return mouse.x - real_x_start;
}

void q_menu::render_slider_i(int index, int side, const char* label, int* value, ImVec2 bounds, bool cancel, bool checkbox, bool* check_val)
{
    const int h = 7;
    const int w = 100;
    float x = this->x + (side == 1 ? 110 : 290) + 15;
    float y = this->y + 23 + (index * 15) + offset[side - 1];
    
    if(checkbox && check_val)
        this->render_checkbox(index, side, label, check_val);
    else
        draw->draw_string(x, y, label, Fonts::verdana, text_col);
    
    y += 15;
    
    auto io = ImGui::GetIO();
    auto mouse = io.MousePos;
    bool m_down = io.MouseDown[0];
    static bool dragging_last[3][64];
    
    if((q_in_area(x, y, w, h ) || dragging_last[side][index]) && m_down && !cancel)
    {
        *value = calculate_value(mouse, x) / (w / bounds.y);
        dragging_last[side][index] = true;
    }
    
    if(!m_down && dragging_last[side][index])
        dragging_last[side][index] = false;
    
    if(*value < bounds.x)
        *value = bounds.x;
    
    if(*value > bounds.y)
        *value = bounds.y;
    
    int current_value = (*value) * (w / bounds.y);
    
    draw->draw_box_gradient(x, y, w, h, ImColor(50, 50, 50, 255), ImColor(70, 70, 70, 255));
    draw->draw_box_gradient(x, y, current_value, h, green_1, green_2, 2);
    draw->draw_string(x + current_value, y, std::to_string(*value).c_str(), Fonts::small, text_col);
    
    offset[side - 1] += 13;
}

void q_menu::render_slider_f(int index, int side, const char* label, float* value, ImVec2 bounds, bool cancel, bool checkbox, bool* check_val)
{
    const int h = 7;
    const int w = 100;
    float x = this->x + (side == 1 ? 110 : 290) + 15;
    float y = this->y + 23 + (index * 15) + offset[side - 1];
    
    if(checkbox && check_val)
        this->render_checkbox(index, side, label, check_val);
    else
        draw->draw_string(x, y, label, Fonts::verdana, text_col);
    
    y += 15;
    
    auto io = ImGui::GetIO();
    auto mouse = io.MousePos;
    bool m_down = io.MouseDown[0];
    static bool dragging_last[64];
    
    if((q_in_area(x, y, w, h ) || dragging_last[index]) && m_down && !cancel)
    {
        *value = calculate_value(mouse, x) / (w / bounds.y);
        dragging_last[index] = true;
    }
    
    if(!m_down && dragging_last[index])
        dragging_last[index] = false;
    
    if(*value < bounds.x)
        *value = bounds.x;
    
    if(*value > bounds.y)
        *value = bounds.y;
    
    int current_value = (*value) * (w / bounds.y);
    
    char buffer[16];
    
    if(bounds.y > 5)
        sprintf(buffer, "%0.f", *value);
    else
        sprintf(buffer, "%.2f", *value);
    
    draw->draw_box_gradient(x, y, w, h, ImColor(50, 50, 50, 255), ImColor(70, 70, 70, 255));
    draw->draw_box_gradient(x, y, current_value, h, green_1, green_2, 2);
    draw->draw_string(x + current_value, y, buffer, Fonts::small, text_col);
    
    offset[side - 1] += 15;
}

void q_menu::render_combo(int index, int side, const char* label, std::vector<const char*> items, int* value, bool* opened, bool c, bool checkbox, bool* check_val)
{
    impl_combo(side, false);
    
    const int w = 100;
    const int h = 13;
    float x = this->x + (side == 1 ? 110 : 290) + 15;
    float y = this->y + 20 + (index * 15) + offset[side - 1];
    
    bool clicked = ImGui::GetIO().MouseClicked[0];
    bool value_changed = false;
    static bool clicked_last[64];
    
    if(checkbox && check_val)
        this->render_checkbox(index, side, label, check_val);
    else
        draw->draw_string(x, y, label, Fonts::verdana, text_col);
    
    y += 15;
    
    if(q_in_area(x, y, w, h) && clicked && !clicked_last[index] && !c)
        *opened = !*opened;
    
    if(*opened)
    {
        for(int i = 0; i < items.size(); i++)
        {
            bool hovering = false;
            
            if(q_in_area(x, y + ((i + 1) * h), w, h))
            {
                if(clicked && !clicked_last[index] && !c)
                {
                    *value = i;
                    value_changed = true;
                }
                
                hovering = true;
            }
            
            if(!q_in_area(x, y, w, h * (int)items.size()) && clicked && !clicked_last[index])
                *opened = false;
            
            draw->draw_box_filled(x, y + ((i + 1) * h), w, h, hovering ? ImColor(50, 50, 50) : ImColor(35, 35, 35));
            draw->draw_string(x + 10, y + ((i + 1) * h), items.at(i), Fonts::verdana, text_col);
        }
    }
    
    clicked_last[index] = clicked;
    
    draw->draw_box_filled(x, y, w, h, ImColor(35, 35, 35));
    draw->draw_string(x + 10, y, items.at(*value), Fonts::verdana, text_col);
    
    if(*opened)
    {
        draw->draw_line(x + w - 15, y + 1 + h / 2, x + w - 10, y + 1 + h / 2, IM_COL32_WHITE);
        draw->draw_line(x + w - 14, y + 0 + h / 2, x + w - 11, y + 0 + h / 2, IM_COL32_WHITE);
        draw->draw_line(x + w - 13, y - 1 + h / 2, x + w - 12, y - 1 + h / 2, IM_COL32_WHITE);
    }
    else
    {
        draw->draw_line(x + w - 15, y - 1 + h / 2, x + w - 10, y - 1 + h / 2, IM_COL32_WHITE);
        draw->draw_line(x + w - 14, y + 0 + h / 2, x + w - 11, y + 0 + h / 2, IM_COL32_WHITE);
        draw->draw_line(x + w - 13, y + 1 + h / 2, x + w - 12, y + 1 + h / 2, IM_COL32_WHITE);
    }
    
    if(value_changed)
        *opened = false;
}

void q_menu::render_button(int index, int side, const char* label, bool* value, bool cancel)
{
    const int w = 100, h = 20;
    float x = this->x + (side == 1 ? 110 : 290) + 15;
    float y = this->y + 23 + (index * 15) + offset[side - 1];
    
    bool hover = q_in_area(x, y, w, h);
    
    draw->draw_box(x, y, w, h, ImColor(50, 50, 50));
    
    if(hover && !cancel)
    {
        if(ImGui::GetIO().MouseDown[0])
        {
            draw->draw_box_gradient(x + 1, y + 1, w - 2, h - 2, ImColor(45, 45, 45), ImColor(35, 35, 35));
            *value = true;
        }
        else
        {
            draw->draw_box_gradient(x + 1, y + 1, w - 2, h - 2, ImColor(40, 40, 40), ImColor(30, 30, 30));
            *value = false;
        }
    }
    else
    {
        draw->draw_box_gradient(x + 1, y + 1, w - 2, h - 2, ImColor(35, 35, 35), ImColor(25, 25, 25));
    }
    
    
    draw->draw_string(x + w / 2, y + h / 2, label, Fonts::section, text_col, true, true);
    
    offset[side - 1] += 8;
}

bool q_menu::render_button_2(int index, int side, const char* label, bool cancel)
{
    const int w = 100, h = 20;
    float x = this->x + (side == 1 ? 110 : 290) + 15;
    float y = this->y + 23 + (index * 15) + offset[side - 1];
    
    bool ret   = false;
    bool hover = q_in_area(x, y, w, h);
    static bool true_last;

    draw->draw_box(x, y, w, h, ImColor(50, 50, 50));

    if(hover && !cancel)
    {

        if(ImGui::GetIO().MouseDown[0] && !true_last)
        {
            draw->draw_box_gradient(x + 1, y + 1, w - 2, h - 2, ImColor(45, 45, 45), ImColor(35, 35, 35));
            ret = true;
        }
        else
        {
            draw->draw_box_gradient(x + 1, y + 1, w - 2, h - 2, ImColor(40, 40, 40), ImColor(30, 30, 30));
            ret = false;
        }
    }
    else
    {
        draw->draw_box_gradient(x + 1, y + 1, w - 2, h - 2, ImColor(35, 35, 35), ImColor(25, 25, 25));
    }
    
    true_last = ret;
    
    draw->draw_string(x + w / 2, y + h / 2, label, Fonts::section, text_col, true, true);
    
    offset[side - 1] += 8;
    
    return ret;
}

void q_menu::render_slider_c(int index, int side, float* value, ImVec2 bounds, bool cancel, ImVec4 col, int col_index)
{
    const int h = 7;
    const int w = 100;
    float x = this->x + (side == 1 ? 110 : 290) + 15;
    float y = this->y + 23 + (index * 15) + offset[side - 1];
    
    
    auto io = ImGui::GetIO();
    auto mouse = io.MousePos;
    bool m_down = io.MouseDown[0];
    static bool dragging_last[64][3][5];
    
    float tmp_value = *value * 255;
    
    if((q_in_area(x, y, w, h ) || dragging_last[index][side][col_index]) && m_down && !cancel)
    {
        tmp_value = calculate_value(mouse, x) / (w / bounds.y);
        dragging_last[index][side][col_index] = true;
    }
    
    if(!m_down && dragging_last[index][side][col_index])
        dragging_last[index][side][col_index] = false;
    
    if(tmp_value < bounds.x)
        tmp_value = bounds.x;
    
    if(tmp_value > bounds.y)
        tmp_value = bounds.y;
    
    int current_value = (tmp_value) * (w / bounds.y);
    
    char buffer[16];
    
    sprintf(buffer, "%0.f", tmp_value);
    
    draw->draw_box_gradient(x, y, w, h, ImColor(50, 50, 50, 255), ImColor(70, 70, 70, 255));
    draw->draw_box_filled(x, y, current_value, h, ImColor(col));
    draw->draw_string(x + current_value, y, buffer, Fonts::small, text_col);
    
    *value = tmp_value / 255;
    
    offset[side - 1] += 15;
}

void q_menu::render_color_picker(int index, int side, const char* label, ImVec4* col, bool cancel)
{
    float x = this->x + (side == 1 ? 110 : 290) + 15;
    float y = this->y + 23 + (index * 15) + offset[side - 1];
    
    draw->draw_string(x, y, label, Fonts::verdana, text_col);
    
    offset[side - 1] += 15;
    
    ImVec4 color = *col;
    color.w = 1.f;
    render_slider_c(index, side, &col->x, {0, 255}, cancel, color, 1);
    render_slider_c(index, side, &col->y, {0, 255}, cancel, color, 2);
    render_slider_c(index, side, &col->z, {0, 255}, cancel, color, 3);
    
    offset[side - 1] -= 13;
}








