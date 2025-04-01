//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_copy_item(cJSON *args, void *pointer){
    cJSON *src = cJSON_GetObjectItem(args, "src");
    cJSON *dest = cJSON_GetObjectItem(args, "dest");
    if(!cJSON_IsString(src) || !cJSON_IsString(dest)){
        return NULL;
    }
    printf("%s Copy: '%s' to '%s'",YELLOW, src->valuestring, dest->valuestring, RESET);    
    bool copy_item = ask_yes_or_no();
    if(!copy_item){
        return (char*)"user denied the modifications";
    }
    dtw.copy_any(src->valuestring, dest->valuestring, false);
    printf("%s AI COPIED: %s to %s\n",YELLOW, src->valuestring, dest->valuestring, RESET);
    return (char*)"item copied";
}

void configure_copy_item_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_copy_item, (void*)model, "copy", "copy a file or directory", false);
    OpenAiInterface_add_parameters_in_callback(callback, "src", "Pass the source path.", "string", true);
    OpenAiInterface_add_parameters_in_callback(callback, "dest", "Pass the destination path.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}