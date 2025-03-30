//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_list_recursively(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if(!cJSON_IsString(path)){
        return NULL;
    }
    DtwStringArray *all_itens = dtw.list_files_recursively(path->valuestring,false);
    cJSON *all_intens_cjson = cJSON_CreateArray();
    for(int i = 0; i < all_itens->size; i++){

        char *current_file = all_itens->strings[i]; 

        bool is_hidden = dtw_starts_with(current_file, ".");
        if(!is_hidden){
            char *joined = dtw_concat_path(path->valuestring, current_file);
            cJSON_AddItemToArray(all_intens_cjson, cJSON_CreateString(joined));
            free(joined);
        }

    }
    dtw.string_array.free(all_itens);
    char *all_intens_string = cJSON_PrintUnformatted(all_intens_cjson);
    cJSON_Delete(all_intens_cjson);
    printf("%s %s LISTED RECURSIVELY: %s\n",YELLOW,model, path->valuestring, RESET);
    return all_intens_string;    
}


void configure_list_recursively_callbacks(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_list_recursively,(void*)model, "list_recursively", "list all files recursively in a path", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to list recursively.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}