//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_read_file(cJSON *args, void *pointer){
    ModelProps *props = (ModelProps*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if(!cJSON_IsString(path)){
        return NULL;
    }
    char *content =dtw.load_string_file_content(path->valuestring);
    printf("%s %s READDED: %s\n",YELLOW,props->model, path->valuestring, RESET);
    return content;
}

void configure_read_file_callbacks(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_read_file, (void*)model, "read_file", "read a file content", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to read.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}