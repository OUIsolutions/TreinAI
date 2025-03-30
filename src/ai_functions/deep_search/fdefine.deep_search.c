//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end


char *agent_set_status(cJSON *args, void *pointer){
    cJSON *status = cJSON_GetObjectItem(args, "status");
    if (!cJSON_IsString(status)) {
        return NULL;
    }
    bool *status_pointer = (bool*)pointer;
    if(strcmp(status->valuestring, "usefull") == 0){
        *status_pointer = true;
    }else{
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

    printf("%sSTARTING DEEP SEARCH FOR QUESTION: %s\n%s", YELLOW, question->valuestring, RESET);
    
    // Estrutura para armazenar documentos e suas pontuações
    typedef struct {
        char *path;
        int rate;
    } RatedDocument;
    
    // Criar array de documentos aprovados
    cJSON *approved = cJSON_CreateArray();
    char *current_dir = dtw_get_current_dir();
    DtwStringArray *doc_dir = dtw.list_files_recursively(current_dir, false);
    
    // Alocar espaço para armazenar as classificações
    int valid_docs_count = 0;
    RatedDocument *rated_docs = malloc(sizeof(RatedDocument) * doc_dir->size);
    if (!rated_docs) {
        printf("%sMemory allocation failed%s\n", RED, RESET);
        return cJSON_Print(approved);
    }
    
    // Processar cada documento
    for (int i = 0; i < doc_dir->size; i++) {
        char *raw_path = doc_dir->strings[i];
        
        // Ignorar arquivos ocultos
        if (dtw_starts_with(raw_path, ".")) {
            continue;
        }
        
        // Construir caminho completo e carregar conteúdo
        char *path = dtw.concat_path(current_dir, raw_path);
        char *content = dtw.load_string_file_content(path);

        // Pular arquivos vazios ou nulos
        if (content == NULL) {
            free(path);
            continue;
        }

        // Verificar tamanho do arquivo
        size_t content_length = strlen(content);
        if (content_length > 10000 || content_length < 50) {  // Ignora arquivos muito grandes ou muito pequenos
            printf("%sSkipping %s (size: %zu)%s\n", YELLOW, path, content_length, RESET);
            free(path);
            free(content);
            continue;
        }
        
        // Classificar o documento
        bool aproved = false;
          
        OpenAiInterface *openAi = openai.openai_interface.newOpenAiInterface(props->url, props->key, props->model);
        openai.openai_interface.set_cache(openAi, ".cache_dir", true);
        
        // Configurar callback
        OpenAiCallback *callback = new_OpenAiCallback(agent_set_status, &aproved, "set_status", 
                                                        "determine if a content its usefull or crap", false);
        OpenAiInterface_add_parameters_in_callback(callback, "status", "set usefull if the element its usefull to solve the question or crap if its usless", "string", true);
        OpenAiInterface_add_callback_function_by_tools(openAi, callback);

        // Configurar prompts
        openai.openai_interface.add_system_prompt(openAi, "Your task is to determine if the document is useful to answer the question.");
        openai.openai_interface.add_system_prompt(openAi, "YOU MUST CALL THE FUNCTION set_status WITH THE STATUS OF THE DOCUMENT");
        
        char *question_str = malloc(strlen(question->valuestring) + 100);
        sprintf(question_str, "Question: %s", question->valuestring);
        openai.openai_interface.add_system_prompt(openAi, question_str);
      
        char *content_prompt = malloc(strlen(content) + 100);
        sprintf(content_prompt, "Content: %s",content);
        openai.openai_interface.add_system_prompt(openAi, content_prompt);
    

        // Fazer a classificação
        OpenAiResponse *response = OpenAiInterface_make_question_finish_reason_treated(openAi);
        openai.openai_interface.free(openAi);
        if(openai.response.error(response)){
            printf("%sError: %s%s\n", RED, openai.response.get_error_message(response), RESET);
            continue;
        }

        if(aproved){
            printf("%sDocument %s is approved%s\n", GREEN, path, RESET);
           cJSON_AddItemToArray(approved, cJSON_CreateString(path));
        }
        
    }
   
   
    return cJSON_Print(approved);
}

void configure_deep_search(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_deep_search,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the documents that has the response", false);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
