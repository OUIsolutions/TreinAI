//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_move_item(cJSON *args, void *pointer){
    cJSON *src = cJSON_GetObjectItem(args, "src");
    cJSON *dest = cJSON_GetObjectItem(args, "dest");
    if(!cJSON_IsString(src) || !cJSON_IsString(dest)){
        return NULL;
    }
    printf("%s Move: '%s' to '%s'",YELLOW, src->valuestring, dest->valuestring, RESET);    
    bool move_item = ask_yes_or_no();
    if(!move_item){
        return (char*)"user canceled";
    }
    dtw.move_any(src->valuestring, dest->valuestring,false);
    return (char*)"item moved";
}

void configure_move_item_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_move_item, (void*)model, "move", "move a file or directory", false);
    OpenAiInterface_add_parameters_in_callback(callback, "src", "Pass the source path.", "string", true);
    OpenAiInterface_add_parameters_in_callback(callback, "dest", "Pass the destination path.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}