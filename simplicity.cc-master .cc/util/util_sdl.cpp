/*      util_sdl.cpp
 *
 *  Moved everything here so its cleaner
 *
 */

#include "main.h"
#include "util_sdl.h"

void SDLCALL SDL_GetWindowSize(SDL_Window* window, int* w, int* h)
{
    typedef void (*currFn)(SDL_Window*, int*, int*);
    static currFn SDL_GetWindowSizeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetWindowSize"));
    return SDL_GetWindowSizeFn(window, w, h);
}

void SDLCALL SDL_WarpMouseInWindow(SDL_Window* window, int x, int y)
{
    typedef void (*currFn)(SDL_Window*, int, int);
    static currFn SDL_WarpMouseInWindowFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_WarpMouseInWindow"));
    return SDL_WarpMouseInWindowFn(window, x, y);
}

char* SDLCALL SDL_GetClipboardText(void)
{
    typedef char* (*currFn)(void);
    static currFn SDL_GetClipboardTextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetClipboardText"));
    return SDL_GetClipboardTextFn();
}

void SDLCALL SDL_GL_GetDrawableSize(SDL_Window* window, int* w, int* h)
{
    typedef void (*currFn)(SDL_Window*, int*, int*);
    static currFn SDL_GL_GetDrawableSizeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_GetDrawableSize"));
    return SDL_GL_GetDrawableSizeFn(window, w, h);
}

Uint32 SDLCALL SDL_GetTicks(void)
{
    typedef Uint32 (*currFn)(void);
    static currFn SDL_GetTicksFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetTicks"));
    return SDL_GetTicksFn();
}

Uint32 SDLCALL SDL_GetWindowFlags(SDL_Window* window)
{
    typedef Uint32 (*currFn)(SDL_Window*);
    static currFn SDL_GetWindowFlagsFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetWindowFlags"));
    return SDL_GetWindowFlagsFn(window);
}

int SDLCALL SDL_ShowCursor(int toggle)
{
    typedef int (*currFn)(int);
    static currFn SDL_ShowCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_ShowCursor"));
    return SDL_ShowCursorFn(toggle);
}

int SDLCALL SDL_SetClipboardText(const char* text)
{
    typedef int (*currFn)(const char*);
    static currFn SDL_SetClipboardTextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetClipboardText"));
    return SDL_SetClipboardTextFn(text);
}

Uint32 SDLCALL SDL_GetMouseState(int* x, int* y)
{
    typedef Uint32 (*currFn)(int*, int*);
    static currFn SDL_GetMouseStateFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetMouseState"));
    return SDL_GetMouseStateFn(x, y);
}

SDL_Keymod SDLCALL SDL_GetModState(void)
{
    typedef SDL_Keymod (*currFn)(void);
    static currFn SDL_GetModStateFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetModState"));
    return SDL_GetModStateFn();
}

SDL_GLContext SDLCALL SDL_GL_GetCurrentContext(void)
{
    typedef SDL_GLContext (*currFn)(void);
    static currFn SDL_GL_GetCurrentContextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_GetCurrentContext"));
    return SDL_GL_GetCurrentContextFn();
}

SDL_GLContext SDLCALL SDL_GL_CreateContext(SDL_Window* window)
{
    typedef SDL_GLContext (*currFn)(SDL_Window*);
    static currFn SDL_GL_CreateContextFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_CreateContext"));
    return SDL_GL_CreateContextFn(window);
}

int SDLCALL SDL_GL_MakeCurrent(SDL_Window* window, SDL_GLContext context)
{
    typedef int (*currFn)(SDL_Window*, SDL_GLContext);
    static currFn SDL_GL_MakeCurrentFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_MakeCurrent"));
    return SDL_GL_MakeCurrentFn(window, context);
}

Uint64 SDLCALL SDL_GetPerformanceFrequency(void)
{
    typedef Uint64 (*currFn)(void);
    static currFn SDL_GetPerformanceFrequencyFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetPerformanceFrequency"));
    return SDL_GetPerformanceFrequencyFn();
}

Uint64 SDLCALL SDL_GetPerformanceCounter(void)
{
    typedef Uint64 (*currFn)(void);
    static currFn SDL_GetPerformanceCounterFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetPerformanceCounter"));
    return SDL_GetPerformanceCounterFn();
}

int SDLCALL SDL_CaptureMouse(SDL_bool enabled)
{
    typedef int (*currFn)(SDL_bool);
    static currFn SDL_CaptureMouseFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_CaptureMouse"));
    return SDL_CaptureMouseFn(enabled);
}

void SDLCALL SDL_SetCursor(SDL_Cursor* cursor)
{
    typedef void (*currFn)(SDL_Cursor*);
    static currFn SDL_SetCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetCursor"));
    SDL_SetCursorFn(cursor);
}

void SDLCALL SDL_FreeCursor(SDL_Cursor* cursor)
{
    typedef void (*currFn)(SDL_Cursor*);
    static currFn SDL_FreeCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_FreeCursor"));
    return SDL_FreeCursorFn(cursor);
}

SDL_Cursor* SDLCALL SDL_CreateSystemCursor(SDL_SystemCursor id)
{
    typedef SDL_Cursor* (*currFn)(SDL_SystemCursor);
    static currFn SDL_CreateSystemCursorFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_CreateSystemCursor"));
    return SDL_CreateSystemCursorFn(id);
}

int SDLCALL SDL_PollEvent(SDL_Event* event)
{
    typedef int (*currFn)(SDL_Event*);
    static currFn SDL_PollEventFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_PollEvent"));
    return SDL_PollEventFn(event);
}

int SDLCALL SDL_GL_SetAttribute(SDL_GLattr attr, int value)
{
    typedef int (*currFn)(SDL_GLattr, int);
    static currFn SDL_GL_SetAttributeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_SetAttribute"));
    return SDL_GL_SetAttributeFn(attr, value);
}

int SDLCALL SDL_SetRelativeMouseMode(SDL_bool enabled)
{
    typedef int (*currFn)(SDL_bool);
    static currFn SDL_SetRelativeMouseModeFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetRelativeMouseMode"));
    return SDL_SetRelativeMouseModeFn(enabled);
}

const Uint8* SDLCALL SDL_GetKeyboardState(int* numkeys)
{
    typedef Uint8* (*currFn)(int*);
    static currFn SDL_GetKeyboardStateFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GetKeyboardState"));
    return SDL_GetKeyboardStateFn(numkeys);
}

SDL_bool SDLCALL SDL_SetHint(const char* name, const char* value)
{
    typedef SDL_bool (*currFn)(const char*, const char*);
    static currFn SDL_SetHintFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_SetHint"));
    return SDL_SetHintFn(name, value);
}

int SDLCALL SDL_Init(Uint32 flags)
{
    typedef int (*currFn)(Uint32);
    static currFn SDL_InitFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_Init"));
    return SDL_InitFn(flags);
}

int SDLCALL SDL_GL_SetSwapInterval(int interval)
{
    typedef int (*currFn)(int);
    static currFn SDL_GL_SetSwapIntervalFn = reinterpret_cast<currFn>(dlsym(RTLD_DEFAULT, "SDL_GL_SetSwapInterval"));
    return SDL_GL_SetSwapIntervalFn(interval);
}
