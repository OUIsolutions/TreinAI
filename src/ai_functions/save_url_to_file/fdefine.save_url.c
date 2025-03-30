//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_save_url_to_file(cJSON *args, void *pointer){
ModelProps *props = (ModelProps*)pointer;
    cJSON *url = cJSON_GetObjectItem(args, "url");
    if(!cJSON_IsString(url)){
        return NULL;
    }
    cJSON *output = cJSON_GetObjectItem(args, "output");
    if(!cJSON_IsString(output)){
        return NULL;
    }

      
    printf("%s %s DOWNLOAD THE URL '%s' IN: '%s'%s",YELLOW,props->model,url->valuestring, output->valuestring, PURPLE);
    bool aply = ask_yes_or_no();
    if(!aply){
        return (char*)"user canceled";
    }

    BearHttpsRequest *request = bear.request.newBearHttpsRequest(url->valuestring);
    BearHttpsResponse *response = bear.request.fetch(request);
    if(bear.response.error(response)){
        char *error = strdup(bear.response.get_error_msg(response));
        bear.response.free(response);
        bear.request.free(request);
        return error;
    }


    unsigned char *body = bear.response.read_body(response);
    if(bear.response.error(response)){
        char *error = strdup(bear.response.get_error_msg(response));
        bear.request.free(request);
        bear.response.free(response);
        return error;
    }

    long body_size = bear.response.get_body_size(response);
    printf("size of the body: %ld\n", body_size);
    dtw.write_any_content(output->valuestring, (char*)body,body_size);

    bear.request.free(request);
    bear.response.free(response);
    return (char*)"file wrotted";
}

void configure_save_url_to_file(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_save_url_to_file,(void*)model, "save_url_to_file", "save the content of a url in a file", false);
    OpenAiInterface_add_parameters_in_callback(callback, "url", "Pass the url you want to save.", "string", false);
    OpenAiInterface_add_parameters_in_callback(callback, "output", "The file you want to save", "string", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}