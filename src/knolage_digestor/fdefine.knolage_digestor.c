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
    *self = (KnolageDigestor){0};
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

void KnolageDigestor_digest(KnolageDigestor *self,const char *current_item){
    
   char *formmated_current_response = malloc(self->actual_response_size +100);
   snprintf(formmated_current_response,self->actual_response_size+100,"response: %s",self->actual_response);
   openai.openai_interface.add_temp_system_prompt(self->openAi,formmated_current_response);
   free(formmated_current_response);
   char *formmated_current_item  = malloc(strlen(current_item)+100);
   snprintf(formmated_current_item,strlen(current_item)+100,"current_item: %s\n",current_item);
   openai.openai_interface.add_temp_system_prompt(self->openAi,formmated_current_item);
    free(formmated_current_item);
}

void KnolageDigestor_digest_file(KnolageDigestor *self,const char *file_path,const char *current_item){
  int required_size = strlen(current_item)+strlen(file_path)+100;
  char* formmated_current_item = malloc(required_size);
  snprintf(formmated_current_item,required_size,"\tfile_path: %s\ncontent:%s",file_path,current_item);
  KnolageDigestor_digest(self,formmated_current_item);
  free(formmated_current_item);
}

void KnolageDigestor_digest_url(KnolageDigestor *self,const char *url,const char *current_item){
  int required_size = strlen(current_item)+strlen(url)+100;
  char* formmated_current_item = malloc(required_size);
  snprintf(formmated_current_item,required_size,"\turl: %s\ncontent:%s",url,current_item);
  KnolageDigestor_digest(self,formmated_current_item);
  free(formmated_current_item);
}

void KnolageDigestor_free(KnolageDigestor *self){
    openai.openai_interface.free(self->openAi);
    free(self);
}
