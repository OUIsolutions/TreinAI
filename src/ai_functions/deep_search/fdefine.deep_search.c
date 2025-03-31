//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end


char *agent_set_text(cJSON *args, void *pointer){
    cJSON *status = cJSON_GetObjectItem(args, "status");
    if (!cJSON_IsString(status)) {
        return NULL;
    }
    int *status_pointer = (int*)pointer;
    if(strcmp(status->valuestring, "usefull") == 0){
        *status_pointer = true;
    }
    else if(strcmp(status->valuestring, "crap") == 0){
        *status_pointer = false;
    }
  
    
    return "rate setted";
}
char *agent_deep_search(cJSON *args, void *pointer) {
    ModelProps *props = (ModelProps*)pointer;

    cJSON *question = cJSON_GetObjectItem(args, "question");
    if (!cJSON_IsString(question)) {
        return NULL;
    }



    char *final_text = NULL;
    DtwStringArray *itens = dtw.list_files_recursively(".");

    OpenAiInterface *openAi = initialize_openai_interface(props);
    if(!openAi){
        return NULL;
    }
    openai.openai_interface.add_system_prompt(openAi, "");

    printf("%sSTARTING DEEP SEARCH FOR QUESTION: %s\n%s", YELLOW, question->valuestring, RESET);
    

    //return cJSON_Print(approved);
}

void configure_deep_search(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_deep_search,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the documents that has the response", false);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
