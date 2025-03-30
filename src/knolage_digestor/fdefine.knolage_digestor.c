//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.globals.h"
//silver_chain_scope_end



KnolageDigestor *newKnolageDigestor(ModelProps *props, const char *question){
    
    OpenAiInterface *openAi = openai.openai_interface.newOpenAiInterface(props->url, props->key, props->model);
    if(!openAi){
        return NULL;
    }

    KnolageDigestor *self = (KnolageDigestor*)malloc(sizeof(KnolageDigestor));
    self->openAi = openAi;
    
    Asset * digestor_rules = get_asset("system_instructions/knolage_digestor.json");
    if(!digestor_rules){
      printf("%sError: %s%s\n", RED, "No system_instructions/knolage_digestor.json instructions found", RESET);
      KnolageDigestor_free(self);
      return NULL;
    }
    cJSON *rules = cJSON_Parse((char*)digestor_rules->data);
    if(!rules){
        printf("%sError: %s%s\n", RED, "System instructions system_instructions/knolage_digestor.json not a valid json", RESET);
        KnolageDigestor_free(self);  
      return NULL;
    }
    char *question_formmated = (char*)malloc(strlen(question)+100);
    snprintf(question_formmated,strlen(question)+100,"question: %s",question);
    openai.openai_interface.add_system_prompt(openAi,question);
    

    int size = cJSON_GetArraySize(rules);
    for(int i = 0; i <size;i++){
      cJSON *current_rule = cJSON_GetArrayItem(rules,i);
      openai.openai_interface.add_system_prompt(openAi,cJSON_GetStringValue(current_rule));
    }
    cJSON_Delete(rules);

    return self;
}

void KnolageDigestor_digest(KnolageDigestor *self);

void KnolageDigestor_digest_file(KnolageDigestor *self,const char *file_path,const char *content);

void KnolageDigestor_digest_url(KnolageDigestor *self,const char *url,const char *content);

void KnolageDigestor_free(KnolageDigestor *self);
