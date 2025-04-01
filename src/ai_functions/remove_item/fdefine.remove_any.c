//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_remove_file(cJSON *args, void *pointer){
    
    
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if(!cJSON_IsString(path)){
        return NULL;
    }
    printf("%s Remove: '%s'",YELLOW, path->valuestring, RESET);
    bool remove = ask_yes_or_no();
    if(!remove){
        return (char*)"user denied the modifications";
    }

    dtw.remove_any(path->valuestring);
    return (char*)"file or directory removed";
}

void configure_remove_file_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_remove_file, (void*)model, "remove", "remove a file or directory", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to remove.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}