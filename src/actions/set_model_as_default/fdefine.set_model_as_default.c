//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end


int set_model_as_default(){
    const  char *model = args.get_flag(&args_obj, model_lags, model_size, 0);
    if(model == NULL){
        printf("%sError: No Model Provided %s\n", RED, RESET);
        return 1;
    }

  
    char *model_json_content =dtw.encryption.load_string_file_content_hex(encryption,config_path);
    if(model_json_content == NULL){
        printf("%sError: No models found%s\n", RED, RESET);
        return 1;
    }

    cJSON *parsed = get_parsed_json(model_json_content);
    free(model_json_content);
    if(parsed == NULL){
        return 1;
    }


    //delete all default flags
    int size = cJSON_GetArraySize(parsed);
    
    for(int i=0; i < size; i++){
        cJSON *obj = cJSON_GetArrayItem(parsed, i);
        cJSON_DeleteItemFromObject(obj, "default");
    }
    
    bool found = false;
    //test if model already exists
    for(int i = size-1; i >= 0; i--){
        cJSON *obj = cJSON_GetArrayItem(parsed, i);
        cJSON *model_obj = cJSON_GetObjectItem(obj, "model");
        
        if(strcmp(model_obj->valuestring, model) == 0){
            cJSON_AddTrueToObject(obj, "default");
            found = true;
        }
    }
    if(!found){
        cJSON_Delete(parsed);
        printf("%sError: Model not found%s\n", RED, RESET);
        return 1;
    }

    char *dumped = cJSON_Print(parsed);
    dtw.encryption.write_string_file_content_hex(encryption,config_path, dumped);
    cJSON_Delete(parsed);
    free(dumped);
    return 0;

    
}