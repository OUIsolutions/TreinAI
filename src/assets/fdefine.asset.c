//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.globals.h"
//silver_chain_scope_end



Asset *get_asset(const char *path){
    for(int i = 0; i< assets_size;i++){
        if(strcmp(assets[i].path, path) == 0){
            return &assets[i];
        }
    }
    return NULL;
}

DtwStringArray * list_assets_recursively(const char *path){
    DtwStringArray *list = dtw.string_array.newStringArray();
    for(int i = 0; i< assets_size;i++){
        
        if(!path){
            dtw.string_array.append(list, assets[i].path);
        }
        if(path){
            if (dtw_starts_with(assets[i].path, path)){
                dtw.string_array.append(list, assets[i].path);
            }
        }

    }
    return list;
}

DtwStringArray * list_assets(const char *path){
    DtwStringArray *list = dtw.string_array.newStringArray();
    for(int i = 0; i< assets_size;i++){
        DtwPath *asset_path = dtw.path.newPath(assets[i].path);
        char *dir = dtw.path.get_dir(asset_path);
        if (strcmp(dir, path) == 0){
            dtw.string_array.append(list, assets[i].path);
        }
        dtw.path.free(asset_path);
        
    }
    return list;
}