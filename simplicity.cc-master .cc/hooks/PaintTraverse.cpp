/*      PaintTraverse.cpp
 *
 *
 *
 */
#include "main.h"
#include "visuals.h"

void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce)
{
    static VPANEL last = 0;
    
    paintVMT->GetOriginalMethod<oPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);

    if(!last)
    {
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel"))
            last = panel;
    }

    if(panel == last)
    {
        if(Global::local)
        {
            visuals->draw_esp();
            
            visuals->draw_recoil_crosshair();
        }
        
        if(pEngine->IsInGame())
        {
            /*
             *  Debugging
             */
            if(Global::cmd)
            {
                QAngle eyes = Global::cmd->viewangles;
                if(eyes.x > 89 || eyes.x < -89)
                    render->draw_string(10, 140, "PITCH", Fonts::esp, Color::Red());
                if(eyes.y > 180 || eyes.y < -180)
                    render->draw_string(10, 160, "YAW",   Fonts::esp, Color::Red());
                if(eyes.z > 50 || eyes.z < -50)
                    render->draw_string(10, 180, "ROLL",  Fonts::esp, Color::Red());
            }
        }
        
        render->draw_string(10, 20, "simplicity.cc", Fonts::esp, Color::quake());
    }
}
