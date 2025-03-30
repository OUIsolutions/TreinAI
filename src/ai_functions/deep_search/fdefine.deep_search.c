//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end


char *agent_set_rate(cJSON *args, void *pointer){
    cJSON *rate = cJSON_GetObjectItem(args, "rate");
    if(!cJSON_IsNumber(rate)){
        return NULL;
    }
    int *rate_pointer = (int*)pointer;
    *rate_pointer = rate->valueint;
    return "rate setted";
}

char *agent_deep_search(cJSON *args, void *pointer){
    ModelProps *props = (ModelProps*)pointer;

    cJSON *question = cJSON_GetObjectItem(args, "question");
    if(!cJSON_IsString(question)){
        return NULL;
    }

    
    printf("%sSTARTING DEEP SEARCH FOR QUESTION: %s\n%s",YELLOW, question->valuestring, RESET);
    cJSON *aproved  = cJSON_CreateArray();

    DtwStringArray *doc_dir = dtw.list_files_recursively("docs",DTW_CONCAT_PATH);
    for(int i = 0; i < doc_dir->size; i++){
        int rate = 0;

        char *path = doc_dir->strings[i];
        char *content = dtw.load_string_file_content(path);


        for(int j=0; j < 10;j++){
                OpenAiInterface *openAi =openai.openai_interface.newOpenAiInterface(props->url, props->key,props->model);
                openai.openai_interface.set_cache(openAi, "cache_dir",true);
                OpenAiCallback *callback = new_OpenAiCallback(agent_set_rate, &rate, "set_rate", "set the rate of the model", false);
                OpenAiInterface_add_parameters_in_callback(callback, "rate", "The rate you want to set", "number", true);
                OpenAiInterface_add_callback_function_by_tools(openAi, callback);

                openai.openai_interface.add_system_prompt(openAi,"your function its to clasify how useful is the document for the question");
                openai.openai_interface.add_system_prompt(openAi,"YOU MUST CALL THE FUNCTION set_rate WITH THE RATE OF THE DOCUMENT");
                openai.openai_interface.add_system_prompt(openAi,"make rate between 1 and 1000");
                char *question_str = malloc(strlen(question->valuestring) + 100);
                sprintf(question_str,"question: %s",question->valuestring);
                openai.openai_interface.add_system_prompt(openAi,question_str);

                char *str_content_frase = malloc(strlen(content) + 100);
                sprintf(str_content_frase,"content: %s",content);

                openai.openai_interface.add_system_prompt(openAi,str_content_frase);

                OpenAiResponse *response =  OpenAiInterface_make_question_finish_reason_treated(openAi);
                if(openai.openai_interface.error(response)){
                    printf("%sError aqui: %s%s\n", RED, openai.openai_interface.get_error_message(response), RESET);
                    return strdup("error");
                }
                openai.openai_interface.free(openAi);

                if(rate > 0){
                    if(j >0 ){
                        printf("document fail %s %d times\n",path,j);
                    }
                    break;
                }
        }
        if(rate > 800){
            cJSON_AddItemToArray(aproved,cJSON_CreateString(path));
        }
        printf("docment:%s -> %d\n",path, rate);
    }
    

    return cJSON_Print(aproved);
}

void configure_deep_search(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_deep_search,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the documents that has the response", false);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
