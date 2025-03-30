//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end




char *agent_search_how_to(cJSON *args, void *pointer){
    cJSON *question = cJSON_GetObjectItem(args, "question");
    if(!cJSON_IsString(question)){
        return NULL;
    }

    /*
    cJSON *urls = cJSON_GetObjectItem(args, "urls");
    if(!cJSON_IsArray(urls)){
        return NULL;
    }
    for(int i = 0; i < cJSON_GetArraySize(urls); i++){
        cJSON *url = cJSON_GetArrayItem(urls, i);
        if(!cJSON_IsString(url)){
            return NULL;
        }
    }
    */
    printf("question %s\n", question->valuestring);
    //printf("urls %s\n", cJSON_Print(urls));

    return (char*)"not found";
}

void configure_search_how_to(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_search_how_to,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the answer", false);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
