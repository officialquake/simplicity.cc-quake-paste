#include "thirdperson.hpp"


void ThirdPerson::OverrideView(CViewSetup *setup)
{
    if (!vars.misc.thirdperson) {
        pInput->m_fCameraInThirdPerson = false;
        return;
    }
    
    C_BasePlayer *localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer || !localplayer->GetAlive())
        return;
    
    QAngle *view = localplayer->GetViewPunchAngle();
    trace_t tr;
    Ray_t ray;
    
    Vector desiredCamOffset = Vector(cos(DEG2RAD(view->y)) * vars.misc.tpdistance,
                                     sin(DEG2RAD(view->y)) * vars.misc.tpdistance,
                                     sin(DEG2RAD(-view->x)) * vars.misc.tpdistance
                                     );
    
    ray.Init(localplayer->GetEyePosition(), (localplayer->GetEyePosition() - desiredCamOffset));
    CTraceFilter traceFilter;
    traceFilter.pSkip = localplayer;
    pEngineTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);
    
    Vector diff = localplayer->GetEyePosition() - tr.endpos;
    
    float distance2D = diff.Length2D();
    
    bool horOK = distance2D > (vars.misc.tpdistance - 2.0f);
    bool vertOK = (abs(diff.z) - abs(desiredCamOffset.z) < 3.0f);
    
    float cameraDistance;
    
    if( horOK && vertOK)
    {
        cameraDistance= vars.misc.tpdistance;
    }
    else
    {
        if(vertOK)
        {
            cameraDistance = distance2D * 0.95f;
        }
        else
        {
            cameraDistance = abs(diff.z) * 0.95f;
        }
        pInput->m_fCameraInThirdPerson = true;
        pInput->m_vecCameraOffset.z = cameraDistance;
        
        
    }
    
    
