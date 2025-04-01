//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../src/imports/imports.globals.h"
//silver_chain_scope_end


DtwStringArray *list_files_recursively_not_incluidng_ignorable_files(const char *listage_path){
    
    Asset *ignorable_files = get_asset("ignorable_files.json");
    if(!ignorable_files){
        printf("%sError: %s%s\n", RED, "File ignorable_files.json not found", RESET);
        return NULL;
    }
    cJSON *parsed_ignorable_files = cJSON_Parse(ignorable_files->data);
    if(!parsed_ignorable_files){
        printf("%sError: %s%s\n", RED, "Error parsing ignorable_files.json", RESET);
        return NULL;
    }
    int total_ignorable_files = cJSON_GetArraySize(parsed_ignorable_files);

    DtwStringArray *filtered = newDtwStringArray();
    DtwStringArray *all= dtw.list_files_recursively(listage_path,true);
    for (int i = 0; i < all->size; i++){
        bool ignore = false;
        char *file = all->strings[i];
        CTextStack *converted_file = newCTextStack_string(file);
        for(int j = 0; j < total_ignorable_files; j++){
            cJSON *ignorable_file = cJSON_GetArrayItem(parsed_ignorable_files, j);
            if(CTextStack_index_of(converted_file,ignorable_file->valuestring) != -1){
                ignore = true;
                break;
            }
        }

        if(ignore){
            CTextStack_free(converted_file);
            continue;
        }
        for(int i = 1; i < converted_file->size; i++){
            if(converted_file->rendered_text[i-1] == '\\' || converted_file->rendered_text[i-1] == '/'){
                if(converted_file->rendered_text[i] == '.'){
                    ignore = true;
                    break;
                }
            }
        }
        if(ignore){
            CTextStack_free(converted_file);
            continue;
        }
        DtwStringArray_append(filtered, file);
        CTextStack_free(converted_file);
    }
    
    DtwStringArray_free(all);
    return filtered;
}