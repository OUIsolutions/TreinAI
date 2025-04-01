//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_get_context_doc(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *context_name = cJSON_GetObjectItem(args, "context_name");
    if(!cJSON_IsString(context_name)){
        return NULL;
    }
    char *full_path = dtw.concat_path(CONTEX_DIR, context_name->valuestring);
    char *content =dtw.load_string_file_content(full_path);
    if(content == NULL){
        printf("%s %s CONTEXT INFORMATION NOT FOUND: %s\n",RED,model, context_name->valuestring, RESET);
        free(full_path);
        return strdup("not found");
    }
    printf("%s %s LOADED CONTEXT INFORMATION: %s\n",YELLOW,model, context_name->valuestring, RESET);
    free(full_path);
    return content;
}

void configure_get_context_doc_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_get_context_doc, (void*)model, "get_context_doc", "get context doc", true);
    OpenAiInterface_add_parameters_in_callback(callback, "context_name", "Pass the context name you want to get.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}