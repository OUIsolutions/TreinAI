//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.globals.h"
//silver_chain_scope_end


ModelProps *newModelProps(const char *url, const char *key, const char *model){
    ModelProps *model_props = (ModelProps *)malloc(sizeof(ModelProps));
    model_props->url = strdup(url);
    model_props->key = strdup(key);
    model_props->model =   strdup(model);
    return model_props;
}

void freeModelProps(ModelProps *modelProps){
    free(modelProps->url);
    free(modelProps->key);
    free(modelProps->model);
    free(modelProps);
}

ModelProps * get_model_props_with_model_name(const char *model){

    char *content =dtw.encryption.load_string_file_content_hex(encryption,config_path);
    if(content == NULL){
        printf("%sError: No models found%s\n", RED, RESET);
        return NULL;
    }
    cJSON *parsed = get_parsed_json(content);
    if(parsed == NULL){
        return NULL;
    }
    int size = cJSON_GetArraySize(parsed);
    for(int i = 0; i < size; i++){
        cJSON *obj = cJSON_GetArrayItem(parsed, i);
        cJSON *model_obj = cJSON_GetObjectItem(obj, "model");
        if(strcmp(model_obj->valuestring, model) == 0){
            cJSON *url = cJSON_GetObjectItem(obj, "url");
            cJSON *key = cJSON_GetObjectItem(obj, "key");
            ModelProps * model_obj = newModelProps(url->valuestring, key->valuestring, model);
            cJSON_Delete(parsed);
            free(content);
            return model_obj;
        }
    }
    
    printf("%sError: %s%s\n", RED, "No model provided", RESET);

    return NULL;
}

ModelProps * get_model_props_default(){

    //trys to get the default model


    char *content = dtw.encryption.load_string_file_content_hex(encryption,config_path);
    if(content == NULL){
        printf("%sError: No models found%s\n", RED, RESET);
        return NULL;
    }
    cJSON *parsed = get_parsed_json(content);
    if(parsed == NULL){
        return NULL;
    }
    int size = cJSON_GetArraySize(parsed);
    if(size == 0){
        printf("%sError: %s%s\n", RED, "No models found", RESET);
        cJSON_Delete(parsed);
        free(content);
        return NULL;   
    }



    for(int i = 0; i < size; i++){
        cJSON *obj = cJSON_GetArrayItem(parsed, i);
        cJSON *is_default = cJSON_GetObjectItem(obj, "default");
        if(cJSON_IsTrue(is_default)){
            cJSON *url = cJSON_GetObjectItem(obj, "url");
            cJSON *key = cJSON_GetObjectItem(obj, "key");
            cJSON *model = cJSON_GetObjectItem(obj, "model");
            ModelProps * model_obj = newModelProps(url->valuestring, key->valuestring, model->valuestring);
            cJSON_Delete(parsed);
            free(content);
            return model_obj;
        }
    }

    //get first model
    cJSON *obj = cJSON_GetArrayItem(parsed, 0);
    cJSON *url = cJSON_GetObjectItem(obj, "url");
    cJSON *key = cJSON_GetObjectItem(obj, "key");
    cJSON *model = cJSON_GetObjectItem(obj, "model");
    ModelProps * model_obj = newModelProps(url->valuestring, key->valuestring, model->valuestring);
    cJSON_Delete(parsed);
    free(content);
    return model_obj;
}

ModelProps *collect_model_props(){
    const char *model =args.get_flag(&args_obj, model_lags, model_size,0);
    ModelProps *model_props = NULL;

    if(model == NULL){
        return  get_model_props_default();
      
    }
    const char *key =args.get_flag(&args_obj, key_flags, key_size,0);
    const char *url =args.get_flag(&args_obj, url_flags, url_size,0);
    if(!key || !url){
        return get_model_props_with_model_name(model);
    }

    return newModelProps(url, key, model);

}

