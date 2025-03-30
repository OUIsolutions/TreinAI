//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_save_url_to_file(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *url = cJSON_GetObjectItem(args, "url");
    if(!cJSON_IsString(url)){
        return NULL;
    }
    cJSON *output = cJSON_GetObjectItem(args, "output");
    if(!cJSON_IsString(output)){
        return NULL;
    }
    BearHttpsRequest *request = bear.request.newBearHttpsRequest(url->valuestring);
    BearHttpsResponse *response = bear.request.fetch(request);
    if(bear.response.error(response)){
        char *error = strdup(bear.response.get_error_msg(response));
        bear.response.free(response);
        bear.request.free(request);
        return error;
    }
    const char *body = bear.response.read_body_str(response);
    if(bear.response.error(response)){
        char *error = strdup(bear.response.get_error_msg(response));
        bear.request.free(request);
        bear.response.free(response);
        return error;
    }

  long size;
    bool is_binary;
    char *temp_content = dtw.load_any_content(path->valuestring, &size, &is_binary);

    dtw.write_string_file_content(path->valuestring, content->valuestring);

   
    printf("%s %s APLY THE MODIFCATIONS OF '%s' IN: '%s'%s",YELLOW,model,url->valuestring, path->valuestring, PURPLE);
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
          bear.request.free(request);
        bear.response.free(response);
        return (char*)"user canceled";
    }

    bear.request.free(request);
    bear.response.free(response);
    return (char*)"file wrotted";
}

void configure_save_url_to_file(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_get_url,(void*)model, "save_url_to_file", "save the content of a url in a file", false);
    OpenAiInterface_add_parameters_in_callback(callback, "url", "Pass the url you want to save.", "string", false);
    OpenAiInterface_add_parameters_in_callback(callback, "output", "The file you want to save", "string", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}