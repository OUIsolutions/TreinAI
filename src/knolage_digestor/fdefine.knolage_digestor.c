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

    KnolageDigestor *knolageDigestor = (KnolageDigestor*)malloc(sizeof(KnolageDigestor));
    knolageDigestor->openAi = openAi;
    

    return knolageDigestor;
}

void KnolageDigestor_digest(KnolageDigestor *self);

void KnolageDigestor_digest_file(KnolageDigestor *self,const char *file_path,const char *content);

void KnolageDigestor_digest_url(KnolageDigestor *self,const char *url,const char *content);

void KnolageDigestor_free(KnolageDigestor *self);
