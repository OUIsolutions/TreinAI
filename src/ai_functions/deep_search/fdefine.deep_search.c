//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end




char *agent_deep_search(cJSON *args, void *pointer){
    cJSON *question = cJSON_GetObjectItem(args, "question");
    if(!cJSON_IsString(question)){
        return NULL;
    }
    ModelProps *props = (ModelProps*)pointer;

    
    printf("%sSTARTING DEEP SEARCH FOR QUESTION: %s\n%s",YELLOW, question->valuestring, RESET);
    cJSON *aproved  = cJSON_CreateArray();

    DtwStringArray *doc_dir = dtw.list_files_recursively("docs",DTW_CONCAT_PATH);
    for(int i = 0; i < doc_dir->size; i++){
        char *path = doc_dir->strings[i];
        char *content = dtw.load_string_file_content(path);

        OpenAiInterface *openAi =openai.openai_interface.newOpenAiInterface()

        free(content);
    }
    
    return knolage_digestor->actual_response;
}

void configure_deep_search(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_deep_search,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the answer", true);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
