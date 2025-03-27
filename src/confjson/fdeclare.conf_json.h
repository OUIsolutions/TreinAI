//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.consts.h"
//silver_chain_scope_end

bool get_user_config_models_path();

bool create_user_config_models_path(unsigned char *encryption_key, const char *path_model);

cJSON *create_model_obj(const char *model, const char *key, const char *url);

///ensure that the schema of json its correct
cJSON * get_parsed_json(const char *json);
