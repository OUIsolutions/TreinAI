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
        int rate = 0;
        int max_attempts = 3;  // Reduzido para 3 tentativas em vez de 10
        bool classification_success = false;
        
        for (int attempt = 0; attempt < max_attempts && !classification_success; attempt++) {
            OpenAiInterface *openAi = openai.openai_interface.newOpenAiInterface(props->url, props->key, props->model);
            openai.openai_interface.set_cache(openAi, ".cache_dir", true);
            
            // Configurar callback
            OpenAiCallback *callback = new_OpenAiCallback(agent_set_rate, &rate, "set_level_of_helpfulness", 
                                                          "Set how helpful this content is for answering the question", false);
            OpenAiInterface_add_parameters_in_callback(callback, "rate", "The rate you want to set", "number", true);
            OpenAiInterface_add_callback_function_by_tools(openAi, callback);

            // Configurar prompts
            openai.openai_interface.add_system_prompt(openAi, "Your task is to classify how useful this content is for answering the given question.");
            openai.openai_interface.add_system_prompt(openAi, "YOU MUST CALL THE FUNCTION set_level_of_helpfulness WITH A RATING FROM 1 TO 10000.");
            openai.openai_interface.add_system_prompt(openAi, "Rate 1-999: Not helpful, 1000-4999: Somewhat helpful, 5000-10000: Very helpful");
            
            char question_str[strlen(question->valuestring) + 100];
            sprintf(question_str, "Question: %s", question->valuestring);
            openai.openai_interface.add_system_prompt(openAi, question_str);
            
            // Limitar tamanho do conteúdo enviado (somente primeiros 8000 caracteres)
            size_t content_to_send = content_length > 8000 ? 8000 : content_length;
            char *truncated_content = malloc(content_to_send + 100);
            if (!truncated_content) {
                openai.openai_interface.free(openAi);
                continue;
            }
            strncpy(truncated_content, content, content_to_send);
            truncated_content[content_to_send] = '\0';
            
            char content_prompt[strlen(truncated_content) + 100];
            sprintf(content_prompt, "Content: %s", truncated_content);
            openai.openai_interface.add_system_prompt(openAi, content_prompt);
            free(truncated_content);
            
            // Fazer a classificação
            OpenAiResponse *response = OpenAiInterface_make_question_finish_reason_treated(openAi);
            if (!openai.openai_interface.error(response)) {
                if (rate > 0) {
                    classification_success = true;
                }
            } else {
                printf("%sError: %s%s\n", RED, openai.openai_interface.get_error_message(response), RESET);
            }
            
            openai.openai_interface.free(openAi);
        }
        
        // Mostrar resultado da classificação
        printf("Document: %s -> Rate: %d\n", path, rate);
        
        // Armazenar documentos relevantes
        if (rate >= 1000) {  // Guardar documentos com alguma relevância, não apenas os muito relevantes
            rated_docs[valid_docs_count].path = strdup(path);
            rated_docs[valid_docs_count].rate = rate;
            valid_docs_count++;
            
            if (rate >= 5000) {
                printf("%sHighly relevant: %s%s\n", GREEN, path, RESET);
            }
        }
        
        // Liberar memória
        free(path);
        free(content);
    }
    
    // Ordenar documentos por relevância (ordem decrescente)
    for (int i = 0; i < valid_docs_count - 1; i++) {
        for (int j = 0; j < valid_docs_count - i - 1; j++) {
            if (rated_docs[j].rate < rated_docs[j + 1].rate) {
                // Trocar posições
                RatedDocument temp = rated_docs[j];
                rated_docs[j] = rated_docs[j + 1];
                rated_docs[j + 1] = temp;
            }
        }
    }
    
    // Adicionar documentos ordenados ao array JSON
    for (int i = 0; i < valid_docs_count; i++) {
        if (rated_docs[i].rate >= 5000) {  // Adicionar apenas os realmente relevantes
            cJSON_AddItemToArray(approved, cJSON_CreateString(rated_docs[i].path));
        }
        free(rated_docs[i].path);  // Liberar memória dos caminhos
    }
    
    // Liberar memória
    free(rated_docs);
    free(current_dir);
    // Suponho que doc_dir seja liberado em outro lugar ou use uma função específica
    
    // Retornar o resultado
    char *result = cJSON_Print(approved);
    cJSON_Delete(approved);
    
    return result;
}

void configure_deep_search(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_deep_search,(void*)model, "make_a_deep_search", "will make a deep search into the project to find the documents that has the response", false);
    OpenAiInterface_add_parameters_in_callback(callback, "question", "The question you want to ask", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
