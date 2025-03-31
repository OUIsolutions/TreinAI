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
   
    char *text_question = malloc(strlen(question->valuestring)+100);
    snprintf(text_question,strlen(question->valuestring)+100,"your mission its to improve the final text to solve the question: %s",question->valuestring);

    char *final_text = NULL;
    DtwStringArray *itens = dtw.list_files_recursively("docs",true);

    for(int i = 0; i < itens->size;i++){
            OpenAiInterface *openAi = initialize_openai_interface(props);
            openai.openai_interface.add_system_prompt(openAi, "your mission its to improve the final text to solve the question");
            openai.openai_interface.add_system_prompt(openAi, "NEVER WRITE UNECESSARY INFORMATION");
            openai.openai_interface.add_system_prompt(openAi, "ONLY CALL SET TEXT IF YOU HAVE A USEFULL INFORMATION");
            openai.openai_interface.add_system_prompt(openAi, "FOCCUS ON THE QUESTION, THE INFORMATION MUST SOLVES THE QUESTION");

        



            printf("%sSTARTING DEEP SEARCH FOR QUESTION: %s\n%s", YELLOW, question->valuestring, RESET);
            
        
    }
    dtw.string_array.free(itens);


    //return cJSON_Print(approved);
}

void configure_deep_search(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_deep_search,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the documents that has the response", false);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
