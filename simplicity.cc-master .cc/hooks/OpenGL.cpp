/*      glHook.cpp
 *
 *
 *
 */

#include "main.h"
#include "menu.h"
#include "util_sdl.h"

#include "imgui.h"
#include "imgui_impl_sdl_gl2.h"

uintptr_t  oSwapWindow = NULL;
uintptr_t* pSwapWindow = nullptr;

void hkSwapWindow(SDL_Window* window)
{
    static SDL_GLContext context = NULL;
    static void (*oSDL_GL_SwapWindow)(SDL_Window*)= reinterpret_cast<void (*)(SDL_Window*)>(oSwapWindow);
    static SDL_GLContext original_context = SDL_GL_GetCurrentContext();
    
    if(!context)
    {
        context = SDL_GL_CreateContext(window);
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplSdlGL2_Init(window);
        
        menu->init();
        
        render->init_fonts();
    }
    
    SDL_GL_MakeCurrent(window, context);
    
    ImGui_ImplSdlGL2_NewFrame(window);    
    
    if(set.menu)
        menu->display();
    
    ImGui::GetIO().MouseDrawCursor = set.menu;
    
    ImGui::Render();
    ImGui_ImplSdlGL2_RenderDrawData(ImGui::GetDrawData());
            
    oSDL_GL_SwapWindow(window);
    SDL_GL_MakeCurrent(window, original_context);
    glFlush();
}

void hkOpenGL()
{
    GLHelper::module mod("libSDL2-2.0.0.dylib");
    
    uintptr_t SwapWindowFn  = reinterpret_cast<uintptr_t>(dlsym(RTLD_DEFAULT, "SDL_GL_SwapWindow"));
    uintptr_t sdl_lib       = reinterpret_cast<uintptr_t>(mod.start());
    pSwapWindow             = reinterpret_cast<uintptr_t*>(GLHelper::get_absolue_address(sdl_lib, SwapWindowFn, 0xF, 0x4));
    oSwapWindow             = *pSwapWindow;
    *pSwapWindow            = reinterpret_cast<uintptr_t>(&hkSwapWindow);
}
