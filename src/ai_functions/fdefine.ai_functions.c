//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_get_ai_chosen_asset(cJSON *args, void *pointer){
  const char *model = (const char*)pointer;
  cJSON *asset = cJSON_GetObjectItem(args, "doc");
  if(!cJSON_IsString(asset)){
        return NULL;
  }
  printf("%s %s READDED DOCS: %s\n",YELLOW,model, asset->valuestring, RESET);

  Asset *current_aset = get_asset(asset->valuestring);

  if(!current_aset){
    return NULL;
  }

  return (char*)current_aset->data;
}


void configure_read_asset_callbacks(OpenAiInterface *openAi,const char *model){
    cJSON *assets_json = cJSON_CreateArray();
    DtwStringArray *all_assets = list_assets_recursively("docs");
    for(int i = 0; i < all_assets->size; i++){
        cJSON_AddItemToArray(assets_json, cJSON_CreateString(all_assets->strings[i]));
    }
    char *assets_printed = cJSON_PrintUnformatted(assets_json);
    char *message = (char*)malloc(strlen(assets_printed) + 100);
    sprintf(message, "The following docs are available: %s", assets_printed);
            
    openai.openai_interface.add_system_prompt(openAi,message);
    OpenAiCallback *callback = new_OpenAiCallback(agent_get_ai_chosen_asset, (void*)model, "get_doc", "get a documentation text", false);
    OpenAiInterface_add_parameters_in_callback(callback, "doc", "Pass the name of doc you want to read.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);

    free(message);
    dtw.string_array.free(all_assets);
    free(assets_printed);
    cJSON_Delete(assets_json);
}


char *agent_list_recursively(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if(!cJSON_IsString(path)){
        return NULL;
    }
    DtwStringArray *all_itens = dtw.list_files_recursively(path->valuestring,false);
    cJSON *all_intens_cjson = cJSON_CreateArray();
    for(int i = 0; i < all_itens->size; i++){

        char *current_file = all_itens->strings[i]; 

        bool is_hidden = dtw_starts_with(current_file, ".");
        if(!is_hidden){
            char *joined = dtw_concat_path(path->valuestring, current_file);
            cJSON_AddItemToArray(all_intens_cjson, cJSON_CreateString(joined));
            free(joined);
        }

    }
    dtw.string_array.free(all_itens);
    char *all_intens_string = cJSON_PrintUnformatted(all_intens_cjson);
    cJSON_Delete(all_intens_cjson);
    printf("%s %s LISTED RECURSIVELY: %s\n",YELLOW,model, path->valuestring, RESET);
    return all_intens_string;    
}



void configure_list_recursively_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_list_recursively,(void*)model, "list_recursively", "list all files recursively in a path", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to list recursively.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}

char *agent_read_file(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if(!cJSON_IsString(path)){
        return NULL;
    }
    char *content =dtw.load_string_file_content(path->valuestring);
    printf("%s %s READDED: %s\n",YELLOW,model, path->valuestring, RESET);
    return content;
}

void configure_read_file_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_read_file, (void*)model, "read_file", "read a file content", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to read.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}


char *agent_write_file(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    cJSON *content = cJSON_GetObjectItem(args, "content");
    if(!cJSON_IsString(path) || !cJSON_IsString(content)){
        return NULL;
    }
    dtw.write_string_file_content(path->valuestring, content->valuestring);
    printf("%s %s WRITE: %s\n",YELLOW,model, path->valuestring, RESET);
    return (char*)"file wrotted";
}

void configure_write_file_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_write_file, (void*)model, "write_file", "write a file content", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to write.", "string", true);
    OpenAiInterface_add_parameters_in_callback(callback, "content", "Pass the content you want to write.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}

char *agent_execute_command(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *command = cJSON_GetObjectItem(args, "command");
    if(!cJSON_IsString(command)){
        return NULL;
    }
    int result = system(command->valuestring);
    printf("%s %s EXECUTED COMMAND: %s\n",YELLOW,model, command->valuestring, RESET);
    char *result_str = (char*)malloc(20);
    sprintf(result_str, "%d", result);
    return result_str;
}

void configure_execute_command_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_execute_command, (void*)model, "execute_command", "execute a command", false);
    OpenAiInterface_add_parameters_in_callback(callback, "command", "Pass the command you want to execute.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}

char *agent_remove_file(cJSON *args, void *pointer){
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if(!cJSON_IsString(path)){
        return NULL;
    }
    dtw.remove_any(path->valuestring);
    printf("%s AI REMOVED: %s\n",YELLOW, path->valuestring, RESET);
    return (char*)"file or directory removed";
}

void configure_remove_file_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_remove_file, (void*)model, "remove_file", "remove a file or directory", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to remove.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}

char *agent_terminate(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    printf("%s %s TERMINATED CONVERSATION\n",YELLOW,model, RESET);
    exit(0);
    return NULL;
}

void configure_terminate_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_terminate, (void*)model, "terminate", "terminate the conversation", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}

char *agent_clear(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("%s %s CLEARED SCREEN\n",YELLOW,model, RESET);
    return (char*)"cleared";
}
void configure_clear_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_clear, (void*)model, "clear", "clear the screen", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
