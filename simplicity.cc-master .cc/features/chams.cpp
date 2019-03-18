/*      chams.cpp
 *
 *
 *
 */

#include "main.h"
#include "visuals.h"

/*
 *  local namespace
 */
namespace
{
    bool mats_created = false;
    IMaterial* chams_tex_vis;
    IMaterial* chams_tex_ign;
    IMaterial* chams_lit_vis;
    IMaterial* chams_lit_ign;
}

static inline bool does_file_exist(const string& path)
{
    fstream f(path);
    return  f.good();
}

/*
 *  create_material
 *  Creates a material file
 */
static IMaterial* create_material(string name, string type, bool ignorez, bool wireframe)
{
    string fileName = "quake_chams_" + name + (ignorez ? "_ignorez" : "");
    string pwd      = getenv("PWD");
    string path     = pwd + "/csgo/materials/" + fileName  + ".vmt";
    
    if(!does_file_exist(path))
    {
        stringstream ss;
        ss << "\"" + type + "\""                                << endl;
        ss << "{"                                               << endl;
        ss << "    \"$basetexture\" \"VGUI/white_additive\""    << endl << endl;
        ss << "    \"$nofog\" \"1\""                            << endl << endl;
        ss << "    \"$ignorez\" \""   + to_string(ignorez)   + "\"" << endl << endl;
        ss << "    \"$wireframe\" \"" + to_string(wireframe) + "\"" << endl << endl;
        ss << "    \"$halflambert\" \"1\""                      << endl;
        ss << "}"                                               << endl;
        ofstream(path.c_str()) << ss.str();
    }
    
    IMaterial* mat = pMatSystem->FindMaterial(fileName.c_str(), TEXTURE_GROUP_MODEL);
    mat->IncrementReferenceCount();
    
    return mat;
}

/*
 *  create_materials
 *  Initliases all materials used for chams
 */
static void create_materials()
{
    chams_tex_vis = create_material("textured",  "VertexLitGeneric", false, false);  // Textured
    chams_tex_ign = create_material("textured",  "VertexLitGeneric", true,  false);  // Textured
    chams_lit_vis = create_material("flat",      "UnlitGeneric",     false, false);  // Flat
    chams_lit_ign = create_material("flat",      "UnlitGeneric",     true,  false);  // Flat
    
    mats_created = true;
}

void C_Visuals::render_chams(void* thisptr, void* context, void* state, ModelRenderInfo_t& model_info, matrix3x4_t* pCustomBoneToWorld)
{
    if(!mats_created)
        create_materials();
    
    if(!set.visuals.chams)
        return;
    
    C_BasePlayer* player = (C_BasePlayer*)pEntList->GetClientEntity(model_info.entity_index);
    
    if(!player || !Global::local)
        return;
    
    if(!player->IsPlayer())
        return;
    
    if(!player->IsAlive())
        return;
    
    if(set.visuals.enemy_only && player->GetTeam() == Global::local->GetTeam())
        return;
    
    
    Color col_vis = imvec_to_color(set.colors.chams_vis);
    Color col_ign = imvec_to_color(set.colors.chams_ign);
    
    col_vis.setA(255);
    col_ign.setA(255);
    
    IMaterial* vis_mat = [&]()
    {
        switch(set.visuals.chams_type)
        {
            case 0: return chams_tex_vis;
            case 1: return chams_lit_vis;
            default:return chams_tex_vis;
        }
    }();
    
    IMaterial* ign_mat = [&]()
    {
        switch(set.visuals.chams_type)
        {
            case 0: return chams_tex_ign;
            case 1: return chams_lit_ign;
            default:return chams_tex_ign;
        }
    }();
    
    
    if(player == Global::local)
    {
        // Todo : set alpha to .7
        modelVMT->GetOriginalMethod<oDrawModelExecute>(21)(thisptr, context, state, model_info, pCustomBoneToWorld);
    }
    else
    {
        float alpha = 1.f;
        
        if(!set.visuals.visible_only)
        {
            ign_mat->ColorModulate(col_ign);
            ign_mat->AlphaModulate(alpha);
            pModelRender->ForcedMaterialOverride(ign_mat);
            modelVMT->GetOriginalMethod<oDrawModelExecute>(21)(thisptr, context, state, model_info, pCustomBoneToWorld);
        }
        
        vis_mat->ColorModulate(col_vis);
        vis_mat->AlphaModulate(alpha);
        pModelRender->ForcedMaterialOverride(vis_mat);
        modelVMT->GetOriginalMethod<oDrawModelExecute>(21)(thisptr, context, state, model_info, pCustomBoneToWorld);
    }
    
    modelVMT->GetOriginalMethod<oDrawModelExecute>(21)(thisptr, context, state, model_info, pCustomBoneToWorld);
}
