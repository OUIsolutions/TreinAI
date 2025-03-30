//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_write_file(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    cJSON *content = cJSON_GetObjectItem(args, "content");
    if(!cJSON_IsString(path) || !cJSON_IsString(content)){
        return NULL;
    }
    long size;
    bool is_binary;
    char *temp_content = dtw.load_any_content(path->valuestring, &size, &is_binary);

    dtw.write_string_file_content(path->valuestring, content->valuestring);

   
    printf("%s %s APLY THE MODIFCATIONS IN: '%s'%s",YELLOW,model, path->valuestring, PURPLE);
    bool aply = ask_yes_or_no();
    if(!aply){
        //means that file already exists
        if(is_binary){
            dtw.write_any_content(path->valuestring, temp_content, size);
        }
        else
        {
           dtw.remove_any(path->valuestring);
        }
        release_if_not_null(temp_content,free);
        return (char*)"user canceled";
    }

    release_if_not_null(temp_content,free);
    return (char*)"file wrotted";
}

void configure_write_file_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_write_file, (void*)model, "write_file", "write a file content", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to write.", "string", true);
    OpenAiInterface_add_parameters_in_callback(callback, "content", "Pass the content you want to write.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
