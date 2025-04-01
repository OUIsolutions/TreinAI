//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_get_url(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *url = cJSON_GetObjectItem(args, "url");
    if(!cJSON_IsString(url)){
        return NULL;
    }
    printf("%s %s GETTING URL: %s\n",YELLOW,model,url->valuestring, RESET);
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
    char *bdy_copy = strdup(body);
    bear.request.free(request);
    bear.response.free(response);
    return bdy_copy;
}

void configure_get_url(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_get_url,(void*)model, "get_url", "fetch a url", true);
    OpenAiInterface_add_parameters_in_callback(callback, "url", "Pass the url you want to fetch.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}