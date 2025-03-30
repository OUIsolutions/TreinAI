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

    
    printf("question %s\n", question->valuestring);
    
    KnolageDigestor *knolage_digestor = newKnolageDigestor((ModelProps*)pointer, question->valuestring);
    if(!knolage_digestor){
        return (char*)"error";
    }
    DtwStringArray *doc_dir = dtw.list_files_recursively("docs",DTW_CONCAT_PATH);
    for(int i = 0; i < doc_dir->size; i++){
        char *path = doc_dir->strings[i];
        char *content = dtw.load_string_file_content(path);
        KnolageDigestor_digest_file(knolage_digestor,path, content);
        free(content);
    }
    printf("%s FINAL DIGEST %s %s",YELLOW, knolage_digestor->actual_response, RESET);
    KnolageDigestor_free(knolage_digestor);
    return knolage_digestor->actual_response;
}

void configure_deep_search(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_deep_search,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the answer", true);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
