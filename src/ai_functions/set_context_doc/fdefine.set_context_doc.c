//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end
char *agent_set_context_doc(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *context_name = cJSON_GetObjectItem(args, "context_name");
    cJSON *content = cJSON_GetObjectItem(args, "content");
    if(!cJSON_IsString(context_name) || !cJSON_IsString(content)){
        return NULL;
    }
    char *full_path = dtw.concat_path(CONTEX_DIR, context_name->valuestring);
    long size;
    bool is_binary;
    char *temp_content = (char *)dtw.load_any_content(full_path, &size, &is_binary);

    dtw.write_string_file_content(full_path, content->valuestring);

    printf("%s %s APLY THE MODIFCATIONS IN: '%s'%s",YELLOW,model, full_path, PURPLE);
    bool aply = ask_yes_or_no();
    if(!aply){
        //means that file already exists
        if(temp_content){
            dtw.write_any_content(full_path, temp_content, size);
        }
        //means the file not existed before
        else{
           dtw.remove_any(full_path);
        }
        release_if_not_null(temp_content,free);
        release_if_not_null(full_path,free);
        return (char*)"user denied the modifications";
    }

    release_if_not_null(temp_content,free);
    release_if_not_null(full_path,free);
    return (char*)"file wrotted";
}

void configure_set_context_doc(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_set_context_doc, (void*)model, "set_context_doc", "set a context doc", false);
    OpenAiInterface_add_parameters_in_callback(callback, "context_name", "Pass the context name you want to set.", "string", true);
    OpenAiInterface_add_parameters_in_callback(callback, "content", "Pass the content you want to set.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}