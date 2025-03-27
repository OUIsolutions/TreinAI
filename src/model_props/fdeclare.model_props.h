//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.consts.h"
//silver_chain_scope_end

ModelProps *collect_model_props();

ModelProps * get_model_props_with_model_name(const char *model);

ModelProps * get_model_props_default();


ModelProps *newModelProps(const char *url, const char *key, const char *model);

void freeModelProps(ModelProps *modelProps);



