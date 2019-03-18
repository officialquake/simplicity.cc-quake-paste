/*      DrawModelExecute.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"

void hkDrawModelExecute(void* thisptr, void* context, void* state, ModelRenderInfo_t& model_info, matrix3x4_t* pCustomBoneToWorld)
{
    IMPL_HOOK("DrawModelExecute");
    
    if(set.visuals.enabled)
    {
        if(model_info.pModel)
        {
            string model_name = pModelInfo->GetModelName(model_info.pModel);
            
            if(model_name.find("models/player") != string::npos)
                visuals->render_chams(thisptr, context, state, model_info, pCustomBoneToWorld);
        }
    }
    
    
    modelVMT->GetOriginalMethod<oDrawModelExecute>(21)(thisptr, context, state, model_info, pCustomBoneToWorld);
    pModelRender->ForcedMaterialOverride(NULL);
}
